#pragma once

#include <strix/client/ingame/network/node/NodeSelectionStrategy.h>

namespace strix { namespace client { namespace ingame { namespace network { namespace node {

/**
 *  A node selection strategy with a random selection method
 */
class RandomNodeSelectionStrategy : public NodeSelectionStrategy
{
	/**
	 *  Select a random node from the list given
	 *  @param	nodes	The list of nodes
	 *  @returns	A random node from the list
	 */
	match::node::model::CustomizableMatchServerNodePtr SelectNode(
		const std::vector<match::node::model::CustomizableMatchServerNodePtr> &nodes) override;
};

} } } } }
