#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/ingame/rpc/RpcProcedure.h>
#include <strix/client/core/NotificationEventArgs.h>
#include <strix/client/core/util/Delegates.h>

#include <map>
#include <memory>

namespace strix { namespace client { namespace ingame { namespace object {
class NetworkObjectManager;
typedef std::shared_ptr<NetworkObjectManager> NetworkObjectManagerPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace rpc { namespace permission {
class RpcPermissionValidator;
typedef std::shared_ptr<RpcPermissionValidator> RpcPermissionValidatorPtr;
} } } } }

namespace strix {namespace client {namespace match {
class MatchRoomClient;
typedef std::shared_ptr<MatchRoomClient> MatchRoomClientPtr;
} } }

namespace strix {namespace client {namespace room { namespace message {
class RoomDirectRelayNotification;
class RoomRelayNotification;
typedef std::shared_ptr<RoomDirectRelayNotification> RoomDirectRelayNotificationPtr;
typedef std::shared_ptr<RoomRelayNotification> RoomRelayNotificationPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace rpc { namespace message {
class RpcMessage;
typedef std::shared_ptr<RpcMessage> RpcMessagePtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace rpc {

/**
 *  Controller for RPC operations. Registers, invokes and sends RPCs
 */
class RpcManager {
public:

	RpcManager(match::MatchRoomClientPtr roomClient);

	/**
	 *  Construct the RPC manager with a room client and a permissions validator. The validator will prevent forbidden calls
	 *  @param	roomClient	The room client
	 *  @param	permissionValidator	The validator to use
	 */
	RpcManager(match::MatchRoomClientPtr roomClient, rpc::permission::RpcPermissionValidatorPtr permissionValidator);

	RpcManager(match::MatchRoomClientPtr roomClient, ingame::object::NetworkObjectManagerPtr networkObjectManager);

	~RpcManager();

	/**
	 *  Send an RPC
	 *  @param	to	The destination client
	 *  @param	networkObjectId	The ID of the network object to call on
	 *  @param	procedureHash	The hash of the procedure to call
	 *  @param	args	Arguments to the call
	 */
	void SendRpc(client::core::UIDPtr to, long long networkObjectId, int procedureHash, strix::net::object::ObjectVector args);

	/**
	 *  Send an RPC to the current room owner
	 *  @param	networkObjectId	The ID of the network object to call on
	 *  @param	procedureHash	The hash of the procedure to call
	 *  @param	args	Arguments to the call
	 */
	void SendRpcToRoomOwner(long long networkObjectId, int procedureHash, strix::net::object::ObjectVector args);

	/**
	 *  Send an RPC to all the other members in the room
	 *  @param	networkObjectId	The ID of the network object to call on
	 *  @param	procedureHash	The hash of the procedure to call
	 *  @param	args	Arguments to the call
	 */
	void SendRpcToOtherMembers(long long networkObjectId, int procedureHash, strix::net::object::ObjectVector args);

	/**
	 *  Send an RPC to all members in the room
	 *  @param	networkObjectId	The ID of the network object to call on
	 *  @param	procedureHash	The hash of the procedure to call
	 *  @param	args	Arguments to the call
	 */
	void SendRpcToAll(long long networkObjectId, int procedureHash, strix::net::object::ObjectVector args);

	/**
	 *  Call an RPC on this client
	 *  @param	networkObjectId	The ID of the network object to call on
	 *  @param	procedureHash	The hash of the procedure to call
	 *  @param	args	Arguments to the call
	 *  @param	from	The UID of the client this RPC is from
	 */
	void InvokeRpc(long long networkObjectId, int procedureHash, strix::net::object::ObjectVector args, client::core::UIDPtr from);

	/**
	 *  Register an RPC
	 *  @param	networkObjectId	The ID of the network object this procedure will call on
	 *  @param	procedure 	The RPC procedure
	 */
	void RegisterRpc(long long networkObjectId, RpcProcedurePtr procedure);

	/**
	 *  Deregister all RPCs belonging to a network object
	 *  @param	networkObjectId	The ID of the network object to erase the objects of
	 */
	void DeregisterRpc(long long networkObjectId);

	/**
	 *  Find an RPC procedure
	 *  @param	networkObjectId	The ID of the network object that owns this RPC
	 *  @param	procedureHash	The hash of the RPC
	 */
	RpcProcedurePtr FindRpcProcedure(long long networkObjectId, int procedureHash);

protected:

	/**
	 *  Register this managers relay notification handlers to the match room client
	 */
	void RegisterRoomClientNotificationEventHandlers();

	/**
	 *  Deregister this managers relay notification handlers from the match room client
	 */
	void DeregisterRoomClientNotificationEventHandlers();

	/**
	 *  Called when a relay notification is received by the match room client. Will attempt to handle the relay message
	 *  @param	notification	The notification event information
	 */
	void OnRoomRelayNotification(core::NotificationEventArgs<room::message::RoomRelayNotificationPtr> notification);

	/**
	 *  Called when a direct relay notification is received by the match room client. Will attempt to handle the relay message
	 *  @param	notification	The notification event information
	 */
	void OnRoomDirectRelayNotification(core::NotificationEventArgs<room::message::RoomDirectRelayNotificationPtr> notification);

	/**
	 *  Attempt to handle an RPC message
	 *  @param	message	The message
	 *  @param	fromUid	The UID of the client that sent the message
	 */
	void TryHandleRpcMessage(strix::net::object::ObjectPtr message, core::UIDPtr fromUid);

private:
	match::MatchRoomClientPtr TryGetValidRoomClient();
	bool CheckNetworkObjectStateForRpc(long long instanceId);
	rpc::message::RpcMessagePtr PrepareRpcMessage(long long networkObjectId, int procedureHash, strix::net::object::ObjectVector args);

	std::map<long long, std::map<int, RpcProcedurePtr> > m_registeredFunctions;
	std::weak_ptr<match::MatchRoomClient> m_roomClient;
	rpc::permission::RpcPermissionValidatorPtr m_permissionValidator;

	core::util::DelegateList<>::Handle m_roomRelayDelegateHandle;
	core::util::DelegateList<>::Handle m_roomDirectRelayDelegateHandle;
};

typedef std::shared_ptr<RpcManager> RpcManagerPtr;

} } } }
