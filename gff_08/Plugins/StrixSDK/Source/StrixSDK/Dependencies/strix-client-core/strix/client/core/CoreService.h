#pragma once

#include <strix/client/core/CoreMessages.h>

namespace strix { namespace client { namespace core {

/**
 *  Represents the core service. Must be initialized at start for strix functionality to work
 */
class CoreService
{
public:

	/**
	 *  Initialize the core service. Registers core meta classes and adds auth and session error formatters
	 */
	static void Init();
};

} } }
