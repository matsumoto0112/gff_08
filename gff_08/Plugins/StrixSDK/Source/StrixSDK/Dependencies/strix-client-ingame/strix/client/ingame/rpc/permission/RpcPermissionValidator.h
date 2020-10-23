#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/ingame/rpc/RpcProcedure.h>

namespace strix { namespace client { namespace match {
class MatchRoomData;
typedef std::shared_ptr<MatchRoomData> MatchRoomDataPtr;
} } }

namespace strix { namespace client { namespace ingame { namespace rpc { namespace permission {
	
/**
 *  Utilities for checking if an RPC procedure is permissible for it's caller and callee
 */
class RpcPermissionValidator
{
public:
	RpcPermissionValidator() {}

	virtual ~RpcPermissionValidator() {}

	/**
	 *  Check if a direct relay is permissible
	 *  @param	instanceId	The ID of the calling object
	 *  @param	matchRoomData	Data about the current room
	 *  @param	rpcProcedure	The RPC procedure
	 *  @param	destination	The ID of the callee object
	 *  @returns	If the RPC procedure's permissions are sufficient
	 */
	virtual bool CheckDirectRelayPermission(long long instanceId, client::match::MatchRoomDataPtr matchRoomData, ingame::rpc::RpcProcedurePtr rpcProcedure, client::core::UIDPtr destination) = 0;

	/**
	 *  Check if a broadcast is permissible
	 *  @param	instanceId	The ID of the calling object
	 *  @param	matchRoomData	Data about the current room
	 *  @param	rpcProcedure	The RPC procedure
	 *  @returns	If the RPC procedure's permissions are sufficient
	 */
	virtual bool CheckBroadcastPermission(long long instanceId, client::match::MatchRoomDataPtr matchRoomData, ingame::rpc::RpcProcedurePtr rpcProcedure) = 0;

	/**
	 *  Check if a received RPC is permissible
	 *  @param	instanceId	The ID of the calling object
	 *  @param	matchRoomData	Data about the current room
	 *  @param	rpcProcedure	The RPC procedure
	 *  @returns	If the RPC procedure's permissions are sufficient
	 */
	virtual bool CheckReceivePermission(long long instanceId, client::match::MatchRoomDataPtr matchRoomData, ingame::rpc::RpcProcedurePtr rpcProcedure, client::core::UIDPtr source) = 0;
};

typedef std::shared_ptr<RpcPermissionValidator> RpcPermissionValidatorPtr;

} } } } }
