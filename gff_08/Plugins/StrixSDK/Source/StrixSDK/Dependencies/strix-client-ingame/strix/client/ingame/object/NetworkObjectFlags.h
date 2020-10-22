#pragma once

namespace strix { namespace client { namespace ingame { namespace object {
	
enum InstantiableBy: int
{
	RoomOwner = 8,
	Anyone = 4
};

enum ConnectionClosedBehaviour: int
{
	ChangeOwnership = 2,
	Delete = 1
};

} } } }
