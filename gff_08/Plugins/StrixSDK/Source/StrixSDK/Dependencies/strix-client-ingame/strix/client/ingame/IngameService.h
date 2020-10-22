#pragma once

namespace strix { namespace client { namespace ingame {

/**
 *  Represents the ingame service. Must be initialized at start for ingame functionality to work
 */
class IngameService
{
public:

	/**
	 *  Initialize the ingame service. Starts the match and replica services and registers the RPC message class for serialization
	 */
	static void Init();
};

} } }
