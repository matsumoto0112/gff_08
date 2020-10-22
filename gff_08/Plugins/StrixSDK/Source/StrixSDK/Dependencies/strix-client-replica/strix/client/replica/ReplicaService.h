#pragma once

namespace strix { namespace client { namespace replica {

/**
 *  Represents the replica service. Must be initialized at start for replica functionality to work
 */
class ReplicaService
{
public:
	/**
	 *  Initialize the core service, registers replica, replica message, and notification classes, 
	 *  and adds the replica error formatter
	 */
	static void Init();
};

} } }
