#pragma once

namespace strix { namespace client { namespace node {

/**
 *  The node service. Must be initialized at start for node functionality to work
 */
class NodeService
{
public:
	/**
	 *  Initialize the node service. Starts the core service, registers NodeRoomSearchResponse, adds node error formatter
	 */
	static void Init();
};

} } }
