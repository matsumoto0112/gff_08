#pragma once

#include <strix/client/ingame/rpc/permission/RpcPermissionValidator.h>

namespace strix { namespace client { namespace ingame { namespace object {
class NetworkObjectManager;
typedef std::shared_ptr<NetworkObjectManager> NetworkObjectManagerPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace rpc { namespace permission {
	
class DefaultRpcPermissionValidator : public ingame::rpc::permission::RpcPermissionValidator
{
public:
	DefaultRpcPermissionValidator(ingame::object::NetworkObjectManagerPtr networkObjectManager) : m_networkObjectManager(networkObjectManager) {}

	/**
	 *  Check if a direct relay is permissible
	 *  @param	instanceId	The ID of the calling object
	 *  @param	matchRoomData	Data about the current room
	 *  @param	rpcProcedure	The RPC procedure
	 *  @param	destination	The ID of the callee object
	 *  @returns	If the RPC procedure's permissions are sufficient
	 */
	bool CheckDirectRelayPermission(long long instanceId, client::match::MatchRoomDataPtr matchRoomData, ingame::rpc::RpcProcedurePtr rpcProcedure, client::core::UIDPtr destination) override;

	/**
	 *  Check if a broadcast is permissible
	 *  @param	instanceId	The ID of the calling object
	 *  @param	matchRoomData	Data about the current room
	 *  @param	rpcProcedure	The RPC procedure
	 *  @returns	If the RPC procedure's permissions are sufficient
	 */
	bool CheckBroadcastPermission(long long instanceId, client::match::MatchRoomDataPtr matchRoomData, ingame::rpc::RpcProcedurePtr rpcProcedure) override;

	/**
	 *  Check if a received RPC is permissible
	 *  @param	instanceId	The ID of the calling object
	 *  @param	matchRoomData	Data about the current room
	 *  @param	rpcProcedure	The RPC procedure
	 *  @returns	If the RPC procedure's permissions are sufficient
	 */
	bool CheckReceivePermission(long long instanceId, client::match::MatchRoomDataPtr matchRoomData, ingame::rpc::RpcProcedurePtr rpcProcedure, client::core::UIDPtr source) override;

private:
	bool CheckNetworkObjectOwnership(long long instanceId, client::core::UIDPtr uid);

	ingame::object::NetworkObjectManagerPtr m_networkObjectManager;
};

typedef std::shared_ptr<DefaultRpcPermissionValidator> DefaultRpcPermissionValidatorPtr;

} } } } }
