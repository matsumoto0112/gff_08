/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "StrixErrors.h"

#include "Adapter/StrixCondition.h"
#include "Adapter/StrixNode.h"
#include "Adapter/StrixNodeRoom.h"
#include "Adapter/StrixNodeRoomInfo.h"
#include "Adapter/StrixOrder.h"
#include "Adapter/StrixRelayArg.h"
#include "Adapter/StrixRoom.h"
#include "Adapter/StrixRoomMember.h"
#include "Containers/Ticker.h"
#include "Engine/GameInstance.h"
#include "Sync/UETypeRegistry.h"
#include "Engine/World.h"

#include <strix/client/core/util/Delegates.h>
#include "strix/client/ingame/network/node/NodeAuthContextFactory.h"
#include "strix/client/ingame/network/node/NodeSelectionStrategy.h"

#include <memory>
#include <map>

#include "StrixNetworkFacade.generated.h"

namespace strix { namespace net { namespace channel {
enum class Protocol;
} } }

namespace strix { namespace client { namespace core {
class UID;
typedef std::shared_ptr<UID> UIDPtr;
} } }

namespace strix { namespace client { namespace ingame { namespace network {
class StrixClient;
typedef std::shared_ptr<StrixClient> StrixClientPtr;
class RoomContext;
typedef std::shared_ptr<RoomContext> RoomContextPtr;

class MasterServerConnection;
class RoomServerConnection;
typedef std::shared_ptr<MasterServerConnection> MasterServerConnectionPtr;
typedef std::shared_ptr<RoomServerConnection> RoomServerConnectionPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace rpc {
class RpcProcedure;
typedef std::shared_ptr<RpcProcedure> RpcProcedurePtr;
} } } }

// General use delegates
DECLARE_DYNAMIC_DELEGATE_TwoParams(FStrixErrorCodeFailureDelegate, int32, ErrorCode, EStrixErrorCategory, ErrorCategory);

// Master server delegates
DECLARE_DYNAMIC_DELEGATE(FStrixMasterServerConnectedDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixNodeSearchDelegate, const TArray<FStrixNode>&, Nodes);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixNodeRoomSearchDelegate, const TArray<FStrixNodeRoomInfo>&, NodeRooms);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixNodeGetCountDelegate, int32, Count);

// Room server delegates
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomServerConnectedDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomSearchDelegate, const TArray<FStrixRoom>&, Rooms);

// Room context delegates
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomContextOpenDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomLeaveDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomDeleteDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomSetDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomMemberSetDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomMemberKickDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomRelayDelegate, int32, ChannelId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStrixRoomDirectRelayDelegate, int32, ChannelId);

// Internal event handlers
typedef std::function<void(int, strix::client::ingame::network::RoomContextPtr)> RoomContextOpenHandler;

UCLASS()
class STRIXSDK_API UStrixNetworkFacade : public UObject
{
	GENERATED_BODY()
	
public:
	/** Initialize the Strix network
	 *  @param	gameInstance	Game instance to store 
	 *  @param	applicationId	The unique application ID
	 */
	void Init(UGameInstance* gameInstance, const FString &applicationId);

	/** Initialize the Strix network using HTTP token
	 *  @param	gameInstance	Game instance to store 
	 *  @param	applicationId	The unique application ID
	 *  @param	accessToken	The access token
	 */
	void InitWithHttpAccessToken(UGameInstance* gameInstance, const FString &applicationId, const FString &accessToken);

	void BeginDestroy() override;

	/** Stop the Strix network
	 */
	void Stop(UGameInstance* gameInstance);

	/** Check whether the Strix network is initialized or not
	 *  @returns	Whether the Strix network is initialized or not
	 */
	bool IsInitialized();

	/** Check whether the network object manager is paused on the given channel
	 *  @param	channelId	The channel ID
	 *  @returns	True if paused, False if unpaused or uninitialized
	 */
	bool IsNetworkObjectManagerPaused(int channelId);

	/** Get a room context by channel Id
	 *  @param	channelId	The channel Id associated with the requested room context
	 *  @returns	Found room context or nullptr if it does not exist
	 */
	strix::client::ingame::network::RoomContextPtr GetRoomContextByChannelId(int channelId);

	/** Get the stored Strix client object, used for direct access to advanced features.
	 *  @returns	Stored Strix client
	 */
	strix::client::ingame::network::StrixClientPtr GetStrixClientPtr()
	{
		return m_strixClient;
	}

	/** Get the PIE instance Id of this Strix network.
	 *  Should only be necessary (and used) when running in Unreal Editor context.
	 *  @returns	PIE instance Id
	 */
	int32 GetPIEInstanceId()
	{
		return m_PIEInstanceId;
	}

	/** Set the PIE instance Id of this Strix network.
	 *  Should only be necessary (and used) when running in Unreal Editor context.
	 *  @param	PIEInstanceId	PIE instance Id to set
	 */
	void SetPIEInstanceId(int32 PIEInstanceId)
	{
		m_PIEInstanceId = PIEInstanceId;
	}

	/** Get the Type Id registry used by this Strix network.
	 */
	std::shared_ptr<UETypeRegistry> GetTypeRegistry()
	{
		return m_typeRegistry;
	}

	/** Connect to master server
	 *  @param	host	The host url
	 *  @param	port	The port number to connect to
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 */
	void ConnectToMasterServer(const FString &host, int32 port, const FStrixMasterServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Check if there is an open master server connection
	 *	@returns Whether the master server is connected or not
	 */
	bool IsMasterServerConnected();

	/** Check if there is an established master server connection.
	 *	Master server connection uses a reconnection mechanism and disconnects itself
	 *	after a certain period of time to reduce the load on the server.
	 *	This checks if the connection can be used to send a message - the internal mechanism
	 *	should reconnect and send the message, even if the connection was closed.
	 *	The message will not be sent if the DisconnectMasterServer() function was used.
	 *	@returns Whether the master server connection exists or not.
	 */
	bool IsMasterServerConnectionValid();

	/** Close the master server connection
	 *
	 */
	void DisconnectMasterServer();

	/** Search for a room server based on given conditions
	 *	@param	limit	The number of values to return
	 *	@param	offset	The offset into the results from which we will return
	 *	@param	condition	The conditions to match to
	 *	@param	order	The order we return results in
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void SearchNode(int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixNodeSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Search for a room based on given conditions (using the master server connection).
	 *  Returns both room server info and room info.
	 *	@param	limit	The number of values to return
	 *	@param	offset	The offset into the results from which we will return
	 *	@param	condition	The conditions to match to
	 *	@param	order	The order we return results in
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void SearchNodeRoom(int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Search for a joinable room based on given conditions (using the master server connection).
	 *  Returns both room server and room info.
	 *	@param	limit	The number of values to return
	 *	@param	offset	The offset into the results from which we will return
	 *	@param	condition	The conditions to match to
	 *	@param	order	The order we return results in
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void SearchJoinableNodeRoom(int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Join a random room server and room
	 *	@param	channelId	The channel to connect with
	 *	@param	condition	The condition to match results against
	 *	@param	memberProperties	The property map of this member
	 *	@param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void JoinRandomNodeRoom(int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties, bool pauseNetworkObjects,
		const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Connect to a room server and join the specified room
	 *  @param	channelId	The channel to connect with
	 *  @param	roomInfo	Structure containing information about the room to join (always use one received from other Strix functions)
	 *  @param	memberProperties	The map of this member's properties
	 *  @param	password	The password to use
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void JoinNodeRoom(int channelId, const FStrixNodeRoomInfo &roomInfo, const FStrixPropertyMap& memberProperties, const FString &password, 
		bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/*	Create a room on a random room server (requires master server connection)
	 *	@param	channelId	The channel to connect with
	 *	@param	roomProperties	The map of properties to assign the new room
	 *	@param	memberProperties	The map of this member's properties
	 *	@param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void CreateNodeRoom(int channelId, const FStrixPropertyMap& roomProperties, const FStrixPropertyMap& memberProperties,
		bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Connect to a room server
	 *	@param	host	The room server hostname
	 *	@param	port	The port number
	 *	@param	protocol	The protocol name to use (ex. TCP)
	 *	@param	channelId	The channel to connect
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void ConnectToRoomServer(const FString &host, int32 port, const FString &protocol, int channelId, const FStrixRoomServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Check if there is an open room server connection
	 *	@param	channelId	The channel to check
	 *	@returns Whether the room server is connected or not
	 */
	bool IsRoomServerConnected(int32 channelId = 0);

	/** Close the master server connection
	 *	@param	channelId	The channel to disconnect
	 */
	void DisconnectRoomServer(int channelId);

	/** Join a room on the current room server
	 *  @param	channelId	The channel to use
	 *  @param	roomId	The Id of the room to connect to on the current room server
	 *  @param	memberProperties	The map of this member's properties
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *  @param	password	The password to use
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void JoinRoom(int32 channelId, int32 roomId, const FStrixPropertyMap& memberProperties, const FString &password,
		bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/*	Create a room on the currently connected room server
	 *	@param	channelId	The channel to use
	 *	@param	roomProperties	The map of properties to assign the new room
	 *	@param	memberProperties	The map of this member's properties
	 *	@param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void CreateRoom(int32 channelId, const FStrixPropertyMap& roomProperties, const FStrixPropertyMap& memberProperties,
		bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Search for a room on the currently connected room server
	 *	@param	channelId	The channel to use
	 *	@param	limit	The number of search results to return
	 *	@param	offset	The offset into the results from which we return
	 *	@param	condition	The conditions of the search
	 *	@param	order	The order in which to return results
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void SearchRoom(int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/*	Search for a joinable room based on given conditions.
	 *	@param	channelId	The channel to use
	 *	@param	limit	The number of search results to return
	 *	@param	offset	The offset into the results from which we return
	 *	@param	condition	The conditions of the search
	 *	@param	order	The order in which to return results
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void SearchJoinableRoom(int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Join a random room on the currently connected room server
	 *  @param	channelId	The channel to use
	 *  @param	condition	The condition to match results against
	 *  @param	memberProperties	The map of properties for this member
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void JoinRandomRoom(int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties,
		bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Leave a room
	 *  @param	channelId	The channel to leave
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void LeaveRoom(int32 channelId, const FStrixRoomLeaveDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Delete a room
	 *  @param	channelId	The channel to use
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void DeleteRoom(int32 channelId, const FStrixRoomDeleteDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Set room information
	 *  @param	channelId	The channel to use
	 *  @param	roomProperties	Map of room properties
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void SetRoom(int32 channelId, const FStrixPropertyMap& roomProperties, const FStrixRoomSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Set room member information
	 *  @param	channelId	The channel to use
	 *  @param	memberProperties	Map of member properties
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void SetRoomMember(int32 channelId, const FStrixPropertyMap& memberProperties, const FStrixRoomMemberSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Kick room member
	 *  @param	channelId	The channel to use
	 *  @param	member	The room member to kick
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void KickRoomMember(int32 channelId, const FStrixRoomMember& member, const FStrixRoomMemberKickDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Relay message to room
	 *  @param	channelId	The channel to use
	 *  @param	message	The message to send
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void Relay(int32 channelId, const FStrixRelayArg& message, const FStrixRoomRelayDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Relay message to member
	 *  @param	channelId	The channel to use
	 *  @param	message	The message to send
	 *  @param	to	The member to send to
	 *	@param	successCallback	Called on success
	 *	@param	failureCallback	Called on failure
	 */
	void DirectRelay(int32 channelId, const FStrixRelayArg& message, const FStrixRoomMember& to, const FStrixRoomDirectRelayDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Register an RPC on an actor
	 *  @param	channelId	The channel to use
	 *  @param	networkInstanceId The network instance Id used by the object
	 *  @param	rpcProcedure The RPC structure to register
	 */
	void RegisterRpcProcedure(int32 channelId, long long networkInstanceId, strix::client::ingame::rpc::RpcProcedurePtr rpcProcedure);

	/** Removes registered RPCs associated with a specific network instance
	 *  @param	channelId	The channel to use
	 *  @param	networkInstanceId	The network instance Id to remove the RPCs from
	 */
	void DeregisterRpcProcedures(int32 channelId, long long networkInstanceId);

	/** Send RPC to the specified client
	 *  @param	channelId	The channel to use
	 *	@param	to	The UID of the member to send this RPC to
	 *	@param	networkObjectId	Network object Id that the RPC is called on
	 *	@param	procedureHash	Hash of the requested RPC
	 *	@param	args The arguments to call with
	 */
	void SendRpc(int32 channelId, strix::client::core::UIDPtr to, long long networkObjectId, int procedureHash, const TArray<FStrixRelayArg>& args);

	/** Send an RPC to the current room owner to be called on the target
	 *	@param	channelId	The channel to use
	 *	@param	networkObjectId	Network object Id that the RPC is called on
	 *	@param	procedureHash	Hash of the requested RPC
	 *	@param	args	The arguments to call with
	 */
	void SendRpcToRoomOwner(int32 channelId, long long networkObjectId, int procedureHash, const TArray<FStrixRelayArg>& args);

	/** Send an RPC to all other members in the room
	 *  @param	channelId	The channel to use
	 *	@param	networkObjectId	Network object Id that the RPC is called on
	 *	@param	procedureHash	Hash of the requested RPC
	 *  @param	args	The arguments to call with
	 */
	void SendRpcToOtherMembers(int32 channelId, long long networkObjectId, int procedureHash, const TArray<FStrixRelayArg>& args);

	/** Send an RPC to all members in the room
	 *  @param	channelId	The channel to use
	 *	@param	networkObjectId	Network object Id that the RPC is called on
	 *	@param	procedureHash	Hash of the requested RPC
	 *  @param	args	The arguments to call with
	 */
	void SendRpcToAll(int32 channelId, long long networkObjectId, int procedureHash, const TArray<FStrixRelayArg>& args);

	/** Pause the network object manager on specified channel, disabling the replication of remote objects
	 *  @param	channelId	The channel to use
	 *  @remark Does not stop the replication of local objects
	 */
	void PauseNetworkObjectManager(int32 channelId);

	/** Unpause the network object manager on specified channel, enabling the replication of remote objects
	 *  @param	channelId	The channel to use
	 *  @remark Respawns previously stored remote objects
	 */
	void UnpauseNetworkObjectManager(int32 channelId);

	/** Check if this client is the owner of the current active room
	 *  @param	channelId	The channel to use
	 *	@returns	Whether or not this client is the room owner
	 */
	bool IsRoomOwner(int channelId);

	/** Get the information about the current room.
	 *  Returns an empty structure if there is no active room on this channel.
	 *  @param	channelId	The channel to use
	 *	@returns	The StrixRoom structure containing information about the current room
	 */
	FStrixRoom GetCurrentRoom(int channelId);

	/** Get the information about the current room member (self).
	 *  Returns an empty structure if there is no active room on this channel.
	 *  @param	channelId	The channel to use
	 *	@returns	The StrixRoomMember structure containing information about the current room member
	 */
	FStrixRoomMember GetCurrentRoomMember(int channelId);

	/** Get the room member with the given ID
	 *  @param	channelId	The channel to use
	 *  @param	memberId	The ID of the member to return.
	 *  @returns	A StrixRoomMember structure containing information about the given member, or an empty member if not found.
	 */
	FStrixRoomMember GetCurrentRoomMemberById(int channelId, int32 memberId);

	/** Get the information about the current room members.
	 *  Returns an empty array.
	 *  @param	channelId	The channel to use
	 *	@returns	An array of StrixRoomMember structure containing information about the current room members
	 */
	TArray<FStrixRoomMember> GetCurrentRoomMembers(int channelId);

	/** Get the number of nodes of the connected master server.
	 *  @param  successCallback Called on a successful get node count response
	 *  @param  failureCallback Called on a failed get node count response
	 */
	void GetNodeCount(const FStrixNodeGetCountDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Add a new handler to the room context opened delegate
	 *  @param	handler	The handler to add
	 *  @returns	The key of the added handle
	 */
	strix::client::core::util::DelegateList<>::Handle AddRoomContextOpenHandler(RoomContextOpenHandler handler);

	/**
	 *  Remove a handler from the room context open delegate
	 *  @param	handle	The handler to add
	 */
	void RemoveRoomContextOpenHandler(strix::client::core::util::DelegateList<>::Handle handle);

	/**
	 *  Get an instance of the Strix Network using any world context object
	 *  @param	worldContextObject	The handler to add
	 *  @returns	Found Strix network reference or nullptr if it does not exist
	 */
	static UStrixNetworkFacade* GetInstance(const UObject* worldContextObject);

	/**
	 *  Remove the stored Strix Network from game instance, making it possible to garbage collect it
	 *  @param	instance	The instance to remove
	 */
	static void RemoveInstance(UStrixNetworkFacade* instance);

	/**
	 *  Gets the actor of the given network ID.
	 *  @param	networkId	The id of the network object whose actor will be returned
	 *  @param	channel	The channel ID to search on
	 *  @returns	The actor reference
	 */
	AActor* GetObjectFromNetworkId(int64 networkId, int channel);

	void SetTicker(UWorld* world);
	
private:
	/** Internal function used for the initialization of the Strix Network.
	 *  Registers the message channel processing on the Unreal Engine Ticker,
	 *  initializes the Strix logs, stores the Strix Network on the game instance
	 *  (to avoid garbage collection), initializes the serializers and the type registry.
	 *  @param	gameInstance	The game instance to store the Strix Network on 
	 */
	void InitBase(UGameInstance* gameInstance);

	/** Store the Strix Network on game instance to avoid garbage collection
	 *  @param	gameInstance	The game instance to store the Strix Network on 
	 */
	void SetInstance(UGameInstance* gameInstance);

	/** Tick function used by Strix Network, used for processing message channels
	 *  @param	deltaTime	The time since last tick
	 */
	void OnTick(float deltaTime);

	/** Cleanup resources and stop ticking.
	 *  This will close every established connection.
	 */
	void StopBase();

	/** Clear the store master server connection.
	 */
	void RemoveMasterServerConnection();

	/** Try to store a room server connection with the specified channel.
	 *  Fails if a room server connection with the specified channel already exists.
	 *  @param	channelId	The channel to use
	 *  @param	roomConnection	The room server connection to store
	 *  @returns	Whether the room server connection was stored successfully or not
	 */
	bool TryAddRoomConnection(int32 channelId, strix::client::ingame::network::RoomServerConnectionPtr roomConnection);

	/** Get the room server connection by channel.
	 *  @param	channelId	The channel to use
	 *  @returns	Room server connection using specified channel or nullptr if not found
	 */
	strix::client::ingame::network::RoomServerConnectionPtr GetRoomServerConnectionByChannelId(int channelId);

	/** Removed a stored room server connection by channel.
	 *  @param	channelId	The channel to use
	 */
	void RemoveRoomServerConnection(int channelId);

	/** Try to store a room context with the specified channel.
	 *  Fails if a room with the specified channel already exists.
	 *  @param	channelId	The channel to use
	 *  @param	roomContext	The room context to store
	 *  @returns	Whether the room context was stored successfully or not
	 */
	bool TryAddRoomContext(int32 channelId, strix::client::ingame::network::RoomContextPtr roomContext);

	/** Removed a stored context by channel.
	 *  @param	channelId	The channel to use
	 */
	void RemoveRoomContext(int32 channelId);

	/** Propagate the data from the type registry to Network Object Manager
	 *  used by the specified room context.
	 *  @param	roomContext	The room context to propagate the type information to
	 */
	void RegisterObjectTypesOnRoomContext(strix::client::ingame::network::RoomContextPtr roomContext);

	/** Compare the provided room connection with the properties used to make a new one.
	 *  @param	roomConnection	The room connection to compare
	 *  @param	host	The host to compare to
	 *  @param	port	The port to compare to
	 *  @param	protocol	The protocol to compare to
	 *  @returns	Whether the provided room connection has the same properties as provided
	 */
	bool CompareRoomConnections(strix::client::ingame::network::RoomServerConnectionPtr roomConnection, const std::string& host, int32 port, const strix::net::channel::Protocol &protocol);

	void OnActorsInitialized(const UWorld::FActorsInitializedParams &params);

	strix::client::ingame::network::StrixClientPtr m_strixClient;
	strix::client::ingame::network::MasterServerConnectionPtr m_masterServerConnection;
	std::map<int, strix::client::ingame::network::RoomServerConnectionPtr> m_roomConnectionsByChannelId;
	std::map<int, strix::client::ingame::network::RoomContextPtr> m_roomContextsByChannelId;
	strix::client::core::util::DelegateList<int, strix::client::ingame::network::RoomContextPtr> m_roomContextOpenDelegate;

	strix::client::core::util::DelegateList<>::Handle m_masterServerConnectionClosedHandle;
	std::map<int, strix::client::core::util::DelegateList<>::Handle> m_roomServerConnectionClosedHandles;
	std::map<int, strix::client::core::util::DelegateList<>::Handle> m_roomContextInvalidateHandles;

	std::shared_ptr<UETypeRegistry> m_typeRegistry;

	FDelegateHandle m_actorsInitializedDelegate;
	int32 m_PIEInstanceId;

	FString TypeIdConfigFilename;

	UPROPERTY()
	TArray<UClass*> m_spawnerClasses;

	static UStrixNetworkFacade* SingleInstance;
	static std::map<int32, UStrixNetworkFacade*> PIEInstances;
};
