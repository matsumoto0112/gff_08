#pragma once

#include <strix/client/core/node/NodeInfo.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace node { namespace model {

/**
 *  An implementation of NodeInfo with customizable properties
 */
class CustomizableNodeInfo : public core::node::NodeInfo
{
public:
	STRIX_CLASS(CustomizableNodeInfo, NodeInfo)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.node.model.CustomizableNodeInfo")
		STRIX_PROPERTY(m_properties)
		STRIX_PROPERTY(m_internalProperties)
	)

	CustomizableNodeInfo() {}

	virtual ~CustomizableNodeInfo() {}

	/**
	 *  Get the customizable properties of this node info
	 *  @returns	A map of strings (property names) and objects (values)
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() const {
		return m_properties;
	}

	/**
	 *  Set the customizable properties of this node info
	 *  @param	properties	A map of strings (property names) and objects (values)
	 */
	void SetProperties(std::map<std::string, strix::net::object::ObjectPtr> properties) {
		m_properties = std::move(properties);
	}

	/**
	 *  Get the internal server properties of this node info
	 *  @returns	A map of strings (property names) and objects (values)
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetInternalProperties() const {
		return m_internalProperties;
	}

	/**
	 *  Set the internal server properties of this node info
	 *  @param	internalProperties	A map of strings (property names) and objects (values)
	 */
	void SetInternalProperties(std::map<std::string, strix::net::object::ObjectPtr> internalProperties) {
		m_internalProperties = std::move(internalProperties);
	}

private:
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
	std::map<std::string, strix::net::object::ObjectPtr> m_internalProperties;
};

} } } } }
