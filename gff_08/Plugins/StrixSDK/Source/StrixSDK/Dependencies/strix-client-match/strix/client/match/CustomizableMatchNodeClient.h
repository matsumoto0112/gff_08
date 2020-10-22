#pragma once

#include <strix/client/match/MatchNodeClient.h>
#include <strix/client/match/node/model/CustomizableMatchServerNode.h>
#include <strix/client/match/node/model/CustomizableMatchServerNodeRoom.h>

namespace strix { namespace client { namespace match {

/**
 *  An implementation of a MatchNodeClient that uses the CustomizableMatchNode and CustomizableMatchNodeRoom as the models
 */
class CustomizableMatchNodeClient : public MatchNodeClient
{
public:
	CustomizableMatchNodeClient() : MatchNodeClient(node::model::CustomizableMatchServerNode::s_GetMetaClass(),
	                                                node::model::CustomizableMatchServerNodeRoom::s_GetMetaClass())
	{
	}

	virtual ~CustomizableMatchNodeClient() = default;
};

typedef std::shared_ptr<CustomizableMatchNodeClient> CustomizableMatchNodeClientPtr;

}}}
