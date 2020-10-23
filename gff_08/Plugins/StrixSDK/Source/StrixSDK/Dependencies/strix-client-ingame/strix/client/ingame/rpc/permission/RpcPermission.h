#pragma once

namespace strix { namespace client { namespace ingame { namespace rpc { namespace permission {
	
enum class RpcPermission
{
	AllowAll,
	SendToRoomOwnerOnly,
	InvokeFromRoomOwnerOnly,
	SendToObjectOwnerOnly,
	InvokeFromObjectOwnerOnly
};

} } } } }
