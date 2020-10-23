#pragma once

namespace strix { namespace client { namespace match {

/**
 *  Represents the match service. Must be initialized at start for match functionality to work
 */
class MatchService
{
public:
	/**
	 *  Initialize the match service. Starts the core, node and room services, and registers Match classes
	 */
	static void Init();
};

} } }
