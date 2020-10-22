#pragma once

namespace strix { namespace client { namespace room {

/**
 *  Represents the room service. Must be initialized at start for room functionality to work
 */
class RoomService
{
public:
	/**
	 *  Initialize the Room Service. Starts the core service, and registers room classes and relay message serializers. Adds room error formatter
	 */
	static void Init();
};

} } }
