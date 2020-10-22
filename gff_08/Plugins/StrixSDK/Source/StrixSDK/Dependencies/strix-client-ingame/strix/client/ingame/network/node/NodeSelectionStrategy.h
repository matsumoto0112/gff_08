#pragma once

#include <strix/client/ingame/network/StrixNetworkEvents.h>

#include <functional>
#include <memory>
#include <vector>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {
class Condition;
typedef std::shared_ptr<Condition> ConditionPtr;
} } } } } }

namespace strix { namespace client { namespace match {
class CustomizableMatchNodeClient;
typedef std::shared_ptr<CustomizableMatchNodeClient> CustomizableMatchNodeClientPtr;
} } }

namespace strix { namespace client { namespace match { namespace node { namespace model {
class CustomizableMatchServerNode;
typedef std::shared_ptr<CustomizableMatchServerNode> CustomizableMatchServerNodePtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace network { namespace node {

/**
 *  Base class for searching and selecting nodes based on a selection strategy. Can be
 *  extended to provide functionality for different search algorithms
 */
class NodeSelectionStrategy : public std::enable_shared_from_this<NodeSelectionStrategy>
{
public:
	NodeSelectionStrategy();
	virtual ~NodeSelectionStrategy() = default;

	/**
	 *  Selects a node from a list of nodes according to the strategy
	 *  @param	nodes	A list of nodes to select from
	 *  @returns	The node selected
	 */
	virtual match::node::model::CustomizableMatchServerNodePtr SelectNode(
		const std::vector<match::node::model::CustomizableMatchServerNodePtr> &nodes) = 0;

	/**
	 *  Requests a Search from a client to find nodes matching the current search condition, and selects
	 *  one node from that list with the SelectNode method of this strategy. Callbacks are called on successful
	 *  selection or failure
	 *  @param	nodeClient	The client to use for the search request
	 *  @param	successHandler	The handler to call on success. Takes the selected node as it's argument. This node will be null if no nodes were found
	 *  @param	failureHandler	The handler to call on a failed search request
	 */
	virtual void FindNode(match::CustomizableMatchNodeClientPtr nodeClient,
	                      std::function<void(match::node::model::CustomizableMatchServerNodePtr)> successHandler,
	                      std::function<void(RequestFailedEventArgs)> failureHandler);

	/**
	 *  Get the limit to the number of nodes to search. This is the maximum number of nodes
	 *  to get from the server
	 *  @returns	The limit
	 */
	int GetNodeSearchLimit() const;

	/**
	 *  Set the limit to the number of nodes to search. This is the maximum number of nodes
	 *  to get from the server
	 *  @param	nodeSearchLimit	The limit
	 */
	void SetNodeSearchLimit(int nodeSearchLimit);

	/**
	 *  Get the node search condition used when requesting a list of nodes from the server
	 *  @returns	The condition
	 */
	core::model::manager::filter::ConditionPtr GetNodeSearchCondition() const;

	/**
	 *  Set the node search condition used when requesting a list of nodes from the server
	 *  @param	nodeSearchCondition	The condition
	 */
	void SetNodeSearchCondition(core::model::manager::filter::ConditionPtr nodeSearchCondition);

private:
	int m_nodeSearchLimit;
	core::model::manager::filter::ConditionPtr m_nodeSearchCondition;
};

typedef std::shared_ptr<NodeSelectionStrategy> NodeSelectionStrategyPtr;

} } } } }
