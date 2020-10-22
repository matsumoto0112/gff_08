#pragma once

#include <strix/client/core/model/Model.h>
#include <strix/client/core/node/NodeInfo.h>

namespace strix { namespace client { namespace node { namespace model {

/**
 *  Abstract model of a Node (a single strix server such as a master or room server)
 */
class Node : public strix::client::core::node::NodeInfo
{
public:
	STRIX_BASE_ABSTRACT_CLASS(Node)
	(
		STRIX_CLASS_SUPER(NodeInfo)
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.node.model.Node")
	)

	Node() {}

	virtual ~Node() {}

};

} } } }
