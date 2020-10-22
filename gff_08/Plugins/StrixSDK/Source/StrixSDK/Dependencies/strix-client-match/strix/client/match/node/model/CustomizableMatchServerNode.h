#pragma once

#include <strix/client/match/node/model/MatchServerNode.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace node { namespace model {

/**
 *  An implementation of a MatchServerNode with customizable properties
 */
class CustomizableMatchServerNode : public MatchServerNode
{
public:
	STRIX_CLASS(CustomizableMatchServerNode, MatchServerNode)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.node.model.CustomizableMatchServerNode")
		STRIX_PROPERTY(m_properties)
		STRIX_PROPERTY(m_internalProperties)
	)

	CustomizableMatchServerNode() {}

	virtual ~CustomizableMatchServerNode() {}

	/**
	 *  Get the customizable properties of this server node
	 *  @returns	A map of strings (property names) to objects (values)
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() const {
		return m_properties;
	}

	/**
	 *  Set the customizable properties of this server node
	 *  @param	properties	A map of strings (property names) to objects (values)
	 */
	void SetProperties(std::map<std::string, strix::net::object::ObjectPtr> properties) {
		m_properties = std::move(properties);
	}

	/**
	 *  Get the internal server properties of this server node
	 *  @returns	A map of strings (property names) to objects (values)
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetInternalProperties() const {
		return m_internalProperties;
	}

	/**
	 *  Set the internal server properties of this server node
	 *  @param	internalProperties	A map of strings (property names) to objects (values)
	 */
	void SetInternalProperties(std::map<std::string, strix::net::object::ObjectPtr> internalProperties) {
		m_internalProperties = std::move(internalProperties);
	}

private:
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
	std::map<std::string, strix::net::object::ObjectPtr> m_internalProperties;
};

typedef std::shared_ptr<CustomizableMatchServerNode> CustomizableMatchServerNodePtr;

} } } } }
