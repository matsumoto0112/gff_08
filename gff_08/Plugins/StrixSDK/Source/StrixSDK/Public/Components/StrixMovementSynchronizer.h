/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StrixReplicatorComponent.h"
#include "Movement/StrixMovementController.h"

#include <strix/client/ingame/object/NetworkObject.h>

#include <chrono>

#include "StrixMovementSynchronizer.generated.h"

class StrixMovementSyncGroup;
typedef std::shared_ptr<StrixMovementSyncGroup> StrixMovementSyncGroupPtr;

UENUM(BlueprintType)
enum class EMovementSyncType : uint8
{
	RPC UMETA(DisplayName = "RPCs"),
	SyncProperties UMETA(DisplayName = "Replica sync properties")
};

class ACharacter;

/** Component used for synchronization of the movement of an actor.
 *  In principle has two modes of work - local and remote.
 *  Local is used for the objects owned by this game instance and will
 *  send update messages to the server. Those messages are sent
 *  in an interval between minimum/maximum property of this component
 *  (depending on the change of the position and rotation).
 *  Remote is used to process the messages received from the server
 *  and update the properties on the actor.
 *  If the actor is a pawn the movement component of this pawn will be used
 *  to interpolate the received data, making movement smooth.
 *
 *  Requires the StrixReplicatorComponent on the owner actor.
 */
 /// \cond
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/// \endcond
class STRIXSDK_API UStrixMovementSynchronizer : public UActorComponent
{
	GENERATED_BODY()

public:
	UStrixMovementSynchronizer();

	/**
	 * Minimum distance between two distinct points on the interpolation path
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strix")
	float NearDistance;

	/**
	 * Max speed allowed by interpolation algorithm
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strix")
	float MaxSpeed;

	/**
	 * Max acceleration allowed by interpolation algorithm
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strix")
	float Acceleration;

	/**
	 * Damping value applied for smoothing of movement
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strix")
	float Damping;

	/**
	 * Minimum period between sync update messages (ms)
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSyncPeriodMin, Category = "Strix")
	int SyncPeriodMin;

	/**
	 * Maximum period before sync update messages (ms)
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSyncPeriodMax, Category = "Strix")
	int SyncPeriodMax;

	/**
	 * The maximum reachable distance from current location in one step before we teleport
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strix")
	float ReachableDistance;

	/**
	 * Type of sync: Remote procedure calls (not stored), or replica properties (stored on server)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strix")
	EMovementSyncType MovementSyncType;

	/**
	 * Check if this component should listen to room join events
	 * and send the updated position (simple 'spawn' message) when a new player joins
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strix")
	bool SendRPCSpawn;

	/**
	 * Whether to synchronize character jump commands
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSyncJump, Category = "Strix")
	bool SyncJump;

	/**
	 * Whether to synchronize velocity on the x-axis
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSyncXVelocity, Category = "Strix")
	bool SyncXVelocity;

	/**
	 * Whether to synchronize velocity on the y-axis
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSyncYVelocity, Category = "Strix")
	bool SyncYVelocity;

	/**
	 * Whether to synchronize velocity on the z-axis
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetSyncZVelocity, Category = "Strix")
	bool SyncZVelocity;

	/**
	 * Whether to smoothly interpolate rotation with Slerp
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter = SetInterpolateRotation, Category = "Strix")
	bool InterpolateRotation;

	/** Delegate function assigned to the MovementModeChangedDelegate of a character
	 *  to detect and send Jump RPC commands if necessary.
	 *	@param	character	Character to check
	 *	@param	mode	Previous movement mode (walking, falling etc.)
	 *	@param	v	Previous custom mode (unused)
	 *	@remark	This will only work with classes derived from ACharacter
	 */
	UFUNCTION()
	void SendJumpRpcIfNecessary(ACharacter* character, EMovementMode mode, uint8 v);

	/** Internal function used for the registration of necessary callbacks etc.
	 */
	UFUNCTION()
	void StartSync();

	/** Custom BeginPlay function that registers the properties to synchronize
	 */
	void BeginPlay() override;

	/** Custom EndPlay function that clean up the resources (callbacks etc.)
	 */
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Setter of the PeriodMin property
	 *	@param	periodMin	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetSyncPeriodMin(int periodMin);

	/** Setter of the PeriodMax property
	 *	@param	periodMax	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetSyncPeriodMax(int periodMax);

	/** Setter of the SyncJump property
	 *	@param	sync	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetSyncJump(bool sync);

	/** Setter of the SyncXVelocity property
	 *	@param	sync	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetSyncXVelocity(bool sync);

	/** Setter of the SyncYVelocity property
	 *	@param	sync	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetSyncYVelocity(bool sync);

	/** Setter of the SyncZVelocity property
	 *	@param	sync	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetSyncZVelocity(bool sync);

	/** Setter of the InterpolateRotation property
	 *	@param	interpolate	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetInterpolateRotation(bool interpolate);

protected:
	/** Create the SyncGroup used by this component
	 */
	void CreatePropertiesSyncGroup();

	/** React to the received RPC 'Jump' command
	 */
	void OnRpcJump();

	/** React to the received RPC 'Move' command
	 */
	void OnRpcMove(FVector position, FVector velocity, FQuat rotation);

	/** React to the received RPC 'Move' command. Sets actor location directly. Used for initial placement
	 */
	void OnRpcMoveDirect(FVector position, FVector velocity, FQuat rotation);

	/** Used by synchronization properties to notify the movement controller about the update
	 */
	void OnPropertiesSyncFinished();

public:
	/** Custom tick function used for updating/sending the movement information
	 *	@param	DeltaTime	The time since the last tick
	 *	@param	TickType	unused
	 *	@param	ThisTickFunction	unused
	 */
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 *  Recreates the internal synchronizer according to the current replica state.
	 *  This is necessary after changing ownership.
	 */
	void ResetSynchronizer();

#if WITH_EDITOR

	bool CanEditChange(const UProperty* InProperty) const override;

#endif

private:
	/** Custom internal (local or remote) movement controller
	 */
	std::unique_ptr<movement::StrixMovementController> CreateMovementController();

	/** Send the RPC 'Move' command
	 */
	void SendMoveRpcMessage();

	/** Send the RPC direct 'Move' command. Used for initial Actor placement
	 */
	void SendDirectMoveRpcMessage();

	/** Used for requesting the SendMoveRpcMessage
	 */
	void RequestDirectMoveMessage();

	/** Set the used SyncGroup to propagate the changes
	 */
	void PropagateSyncPropertyChanges();

	/** Callback executed when room join notification is received.
	 *  Used for sending updated positions with RPCs if the SendRPCSpawn property is set.
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomJoinNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomJoinNotificationPtr> args);

	/**
	 *  Remove the registered RoomJoinNotification handler.
	 */
	void RemoveRoomJoinNotificationHandler(strix::client::ingame::network::RoomContextPtr context);

	/**
	 *  Remove the registered RoomContextInvalidate handler.
	 */
	void RemoveRoomContextInvalidateHandler();

	/**
	 *  Fill the array of relay arguments with the movement data.
	 *  @param	args	The array to fill
	 */
	void FillMoveRelayArguments(TArray<FStrixRelayArg>& args);

	UStrixReplicatorComponent* m_replicator;
	std::unique_ptr<movement::StrixMovementController> m_pMovementController;
	std::chrono::steady_clock::time_point m_lastTime;
	StrixMovementSyncGroupPtr m_syncGroup;

	strix::client::core::util::DelegateList<>::Handle m_roomJoinNotificationHandle;
	strix::client::core::util::DelegateList<>::Handle m_roomContextInvalidateHandle;

	static const std::string PositionXPropertyName;
	static const std::string PositionYPropertyName;
	static const std::string PositionZPropertyName;
	static const std::string VelocityXPropertyName;
	static const std::string VelocityYPropertyName;
	static const std::string VelocityZPropertyName;
	static const std::string RotationXPropertyName;
	static const std::string RotationYPropertyName;
	static const std::string RotationZPropertyName;
	static const std::string RotationWPropertyName;

	static const std::string MoveRPCName;
	static const std::string MoveRPCDirectName;
	static const std::string JumpRPCName;
	static const std::string RequestDirectMoveRPCName;

};
