/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "StrixNetworkFacade.h"
#include "Components/ActorComponent.h"
#include "Sync/UENotifiableSyncGroup.h"

#include <strix/client/ingame/network/RoomContext.h>
#include <strix/client/ingame/object/NetworkObjectFlags.h>

#include <memory>
#include <vector>

#include "StrixReplicatorComponent.generated.h"

namespace strix { namespace client { namespace ingame { namespace network {
class RoomContext;
typedef std::shared_ptr<RoomContext> RoomContextPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace object {
class NetworkObjectSpawner;
typedef std::shared_ptr<NetworkObjectSpawner> NetworkObjectSpawnerPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace sync {
class SyncGroup;
class SyncProperty;
class ScheduledSyncGroup;
typedef std::shared_ptr<SyncProperty> SyncPropertyPtr;
typedef std::shared_ptr<SyncGroup> SyncGroupPtr;
typedef std::shared_ptr<ScheduledSyncGroup> ScheduledSyncGroupPtr;
} } } }

class UEClassNetworkObjectSpawner;
class UENetworkObject;
typedef std::shared_ptr<UENetworkObject> UENetworkObjectPtr;

// Todo: Move enums to their own file?

UENUM(BlueprintType)
enum class EInstantiableBy : uint8
{
	RoomOwner = strix::client::ingame::object::InstantiableBy::RoomOwner UMETA(DisplayName="RoomOwner"),
	Anyone = strix::client::ingame::object::InstantiableBy::Anyone UMETA(DisplayName="Anyone"),

	Unknown = 0  UMETA(Hidden, DisplayName = "Unknown"), // to avoid warning for UE 4.24 or above
};

UENUM(BlueprintType)
enum class EConnectionClosedBehaviour : uint8
{
	ChangeOwnership = strix::client::ingame::object::ConnectionClosedBehaviour::ChangeOwnership UMETA(DisplayName="ChangeOwnership"),
	Delete = strix::client::ingame::object::ConnectionClosedBehaviour::Delete UMETA(DisplayName="Delete"),

	Unknown = 0  UMETA(Hidden, DisplayName = "Unknown"), // to avoid warning for UE 4.24 or above
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStrixReplicatorInitDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStrixReplicatorDestroyDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStrixReplicatorSyncDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStrixReplicatorDesyncDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStrixReplicatorChangeOwnerDelegate);

/** Main component used for synchronization.
 *  Required on every actor that will be synchronized.
 *  Provides automatic TypeId assignment when added to blueprint actors.
 *  When used in C++ classes TypeId needs to be specified.
 */
 /// \cond
UCLASS( ClassGroup=(Strix), meta=(BlueprintSpawnableComponent))
/// \endcond
class STRIXSDK_API UStrixReplicatorComponent : public UActorComponent
{
    GENERATED_BODY()
public:
	static const FName StrixRemoteObjectActorTag;

	UStrixReplicatorComponent();

	/** Custom EndPlay function that cleans up the network instance,
	 *  removes RPCs from it etc.
	 */
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Get the network object associated with this replicator
	 *  @returns	The stored network object
	 */
	strix::client::ingame::object::NetworkObjectPtr GetNetworkObject() const;

	/**
	 *  Update ticks per second for this actor
	 */
	UPROPERTY(EditAnywhere, BlueprintSetter=SetTicksPerSecond, BlueprintGetter=GetTicksPerSecond, Category="Strix Replicator")
	int TicksPerSecond;

	/**
	 *  Specifies who can instantiate this object on the server (everyone/room owner)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Strix Replicator")
	EInstantiableBy InstantiableBy;

	/**
	 *  Behaviour on connection closed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Strix Replicator")
	EConnectionClosedBehaviour ConnectionClosedBehaviour;

	/**
	 *  Should the destroy events received from the server be processed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Strix Replicator")
	bool ShouldReceiveDestroyEvents;

	/**
	 *  Internal type ID for this actor class
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, AdvancedDisplay, Category="Strix Replicator")
	int TypeId;

	/**
	 *  The channel this actor is replicated within
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category="Strix Replicator")
	int ChannelId;

	/**
	 *  Should the properties marked for replication be registered automatically
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Strix Replicator")
	bool AutoRegisterProperties;

	/**
	 *  Getter property for checking whether this object belongs to this game instance
	 */
	UPROPERTY(BlueprintGetter=GetIsOwner, Category="Strix Replicator")
	bool IsOwner;

	/**
	 *  Getter property for checking whether this replicator is being synchronized
	 */
	UPROPERTY(BlueprintGetter=GetIsReplicating, Category="Strix Replicator")
	bool IsReplicating;

	/**
	 *  Getter property for checking whether this replicator is being synchronized
	 *  and belongs to this game instance
	 */
	UPROPERTY(BlueprintGetter=GetIsOwnerAndReplicating, Category="Strix Replicator")
	bool IsOwnerAndReplicating;

	/**
	 *  Callback used when replicator was initialized
	 */
	UPROPERTY(BlueprintAssignable, Category="Strix Replicator")
	FStrixReplicatorInitDelegate OnInit;

	/**
	 *  Callback used when replicator was destroyed
	 */
	UPROPERTY(BlueprintAssignable, Category="Strix Replicator")
	FStrixReplicatorDestroyDelegate OnDestroy;

	/**
	 *  Callback used when replicator started the synchronization.
	 *  This is the best place to register any RPCs.
	 */
	UPROPERTY(BlueprintAssignable, Category="Strix Replicator")
	FStrixReplicatorSyncDelegate OnSyncBegin;

	/**
	 *  Callback used when replicator stopped the synchronization.
	 */
	UPROPERTY(BlueprintAssignable, Category="Strix Replicator")
	FStrixReplicatorDesyncDelegate OnSyncEnd;

	/**
	 *  Callback used when the owner of this replicator was changed
	 *  to the current game instance
	 */
	UPROPERTY(BlueprintAssignable, Category="Strix Replicator")
	FStrixReplicatorChangeOwnerDelegate OnOwnershipReceived;

	/** Get the TicksPerSecond property of this replicator
	 *  @returns	The TicksPerSecond property value
	 */
	UFUNCTION(BlueprintPure)
	int GetTicksPerSecond() const;

	/** Set the TicksPerSecond property of this replicator
	 *  @param	newTicksPerSecond	The value to set
	 */
	UFUNCTION(BlueprintCallable)
	void SetTicksPerSecond(int newTicksPerSecond);

	/** Getter function for checking whether this replicator belongs to this game instance
	 *  @returns	Whether this game instance is the owner of this replicator
	 */
	UFUNCTION(BlueprintPure)
	bool GetIsOwner() const;

	/** Getter function for checking whether this replicator is being synchronized
	 *  @returns	Whether this replicator belongs to this game instance
	 */
	UFUNCTION(BlueprintPure)
	bool GetIsReplicating() const;

	/** Getter function for checking whether this replicator is being synchronized
	 *  and belongs to this game instance
	 *  @returns	Whether this replicator is being synchronized and belongs to this game instance
	 */
	UFUNCTION(BlueprintPure)
	bool GetIsOwnerAndReplicating() const;

	/** Add a new property to be synchronized to the default sync group
	 *  @param	syncProperty	The property to add
	 */
	void AddSyncProperty(strix::client::ingame::sync::SyncPropertyPtr syncProperty);

	/** Add a new sync group (set of synchronized properties).
	 *  This enables synchronization on every property stored on this sync group,
	 *  based on the settings of it.
	 *  @param	syncGroup	The sync group to add
	 */
	void AddSyncGroup(strix::client::ingame::sync::SyncGroupPtr syncGroup);

	/** Removes a sync group, disabling the synchronization of the properties contained within it.
	 *  @param	syncGroup	The sync group to remove
	 */
	void RemoveSyncGroup(strix::client::ingame::sync::SyncGroupPtr syncGroup);

	/** Get the default sync group used by this replicator
	 *  @returns	The default sync group
	 */
	strix::client::ingame::sync::SyncGroupPtr GetDefaultSyncGroup();

	/** Create a default UE-specific network object and register
	 *  the stored sync groups and properties on it.
	 *  Will make this replicator use the created network object for all future operations.
	 */
	void InitializeRemoteInstance();

	/** Register the stored sync groups and properties on the provided network object.
	 *  Will make this replicator use this network object for all future operations.
	 *  @param	networkObject	The network object to use
	 */
	void InitializeRemoteInstance(UENetworkObjectPtr networkObject);

	/** Internal callback called when the room context is opened.
	 *  Used to determine whether this object should continue the initialization or not
	 *  (this mostly applies to objects that can be initialized only by the room owner
	 *  placed in a static world).
	 */
	void OnRoomContextOpen(int roomContextChannelId, strix::client::ingame::network::RoomContextPtr roomContext);

protected:
	/** Custom BeginPlay function that registers the necessary callbacks,
	 *  adds replicated properties etc.
	 */
	void BeginPlay() override;

	/** Custom OnRegister function that tries to assign the TypeId
	 *  (and store it in the config file if necessary).
	 */
	void OnRegister() override;

	/** Adds the sync groups stored pre-synchronization
	 *  to the associated network object.
	 */
	void RegisterPreparedSyncGroups();

	/** Iterates the property tree of the owner actor and
	 *  adds the one marked for replication to the default sync group.
	 *  @remark	Not used when 'AutoRegisterProperties' is set to false
	 */
	void AddReplicatedBlueprintProperties();

	/** Checks whether the owner actor is a static world object
	 *  (currently not supported for replication).
	 */
	bool IsStaticWorldObject();

	/** Creates a network object spawner based on the UClass of the owner actor.
	 *  @returns	The created spawner
	 */
	std::shared_ptr<UEClassNetworkObjectSpawner> BuildClassNetworkObjectSpawner();

	strix::client::core::util::DelegateList<>::Handle m_roomContextOpenDelegateHandle;
	UENetworkObjectPtr m_networkObject;
	UENotifiableSyncGroupPtr m_defaultSyncGroup;
	std::vector<strix::client::ingame::sync::SyncGroupPtr> m_syncGroups;
};
