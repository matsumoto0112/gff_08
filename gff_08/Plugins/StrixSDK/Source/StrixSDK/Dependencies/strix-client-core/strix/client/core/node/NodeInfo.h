#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace node {

/**
 *  Information about a Strix server node
 */
class NodeInfo : public strix::net::object::Object {
public:
	STRIX_CLASS(NodeInfo, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.node.NodeInfo")
		STRIX_PROPERTY(m_uid)
		STRIX_PROPERTY(m_host)
		STRIX_PROPERTY(m_port)
		STRIX_PROPERTY(m_protocol)
		STRIX_PROPERTY(m_type)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	NodeInfo() {}

	virtual ~NodeInfo() {}

	/**
	 *  Get the UID of the node
	 *  @returns	The UID
	 */
	const UIDPtr &GetUid() const {
		return m_uid;
	}

	/**
	 *  Set the UID information
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) {
		m_uid = uid;
	}

	/**
	 *  Get the hostname of the node
	 *  @returns	The hostname string
	 */
	std::string &GetHost() {
		return m_host;
	}

	/**
	 *  Set the hostname information
	 *  @param	host	The hostname
	 */
	void SetHost(const std::string &host) {
		m_host = host;
	}

	/**
	 *  Get the port number of this node
	 *  @returns	The port number
	 */
	int GetPortNumber() {
		return m_port;
	}

	/**
	 *  Set the port number information
	 *  @param	port	The port
	 */
	void SetPortNumber(int port) {
		m_port = port;
	}

	/**
	 *  Get the internet protocol this node is communicating with
	 *  @returns	The protocol string
	 */
	std::string &GetProtocol() {
		return m_protocol;
	}

	/**
	 *  Set the protocol information
	 *  @param	protocol	The protocol string
	 */
	void SetProtocol(const std::string &protocol) {
		m_protocol = protocol;
	}

	/**
	 *  Get the type of the node. User defined
	 *  @returns	The type value
	 */
	int GetType() {
		return m_type;
	}

	/**
	 *  Set the type information. User defined
	 *  @param	type	The type value
	 */
	void SetType(int type) {
		m_type = type;
	}

private:
	UIDPtr m_uid;
	std::string m_host;
	int m_port;
	std::string m_protocol;
	int m_type;
};

} } } }
