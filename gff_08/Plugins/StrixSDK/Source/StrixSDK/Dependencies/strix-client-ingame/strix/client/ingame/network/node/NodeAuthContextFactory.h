#pragma once

#include <memory>

namespace strix { namespace client { namespace match { namespace node { namespace model {
class CustomizableMatchServerNode;
typedef std::shared_ptr<CustomizableMatchServerNode> CustomizableMatchServerNodePtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace auth {
class AuthContext;
typedef std::shared_ptr<AuthContext> AuthContextPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace network { namespace node {

/**
 *  Factory that produces authentication contexts for server connections
 */
class NodeAuthContextFactory
{
public:
	virtual ~NodeAuthContextFactory() = default;

	/**
	 *  Construct a new AuthContext for the given node
	 *  @param	node	The node
	 *  @returns	A new AuthContext
	 */
	virtual auth::AuthContextPtr BuildAuthContext(match::node::model::CustomizableMatchServerNodePtr node) = 0;
};
typedef std::shared_ptr<NodeAuthContextFactory> NodeAuthContextFactoryPtr;

} } } } } 
