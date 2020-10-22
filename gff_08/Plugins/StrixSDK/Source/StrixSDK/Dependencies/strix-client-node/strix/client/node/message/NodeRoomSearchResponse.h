#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace node { namespace message {

/**
 *  Response to a successful node room search request
 *  
 *  Strix response type - Received from server after request made
 */
class NodeRoomSearchResponse : public strix::client::core::message::ParameterResponseMessage
{
public:
	STRIX_CLASS(NodeRoomSearchResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.node.message.NodeRoomSearchResponse")
		STRIX_PROPERTY(m_nodes)
		STRIX_PROPERTY(m_nodeRooms)
	)

	typedef strix::net::object::MetaClass MetaClass;

	NodeRoomSearchResponse() : ParameterResponseMessage(2) {}

	NodeRoomSearchResponse(const MetaClass &nodeClass, const MetaClass &nodeRoomClass)
		: ParameterResponseMessage(2)
	{
		SetNodeClass(nodeClass);
		SetNodeRoomClass(nodeRoomClass);
	}

	virtual ~NodeRoomSearchResponse() {}

	/**
	 *  Return the node's meta class
	 *  @returns	The meta class of the node
	 */
	const MetaClass &GetNodeClass() const {
        return GetParameterClass(0);
    }

	/**
	 *  Set the node's meta class
	 *  @param	nodeClass	The meta class to set
	 */
    void SetNodeClass(const MetaClass &nodeClass) {
		SetParameterClass(0, nodeClass);
    }

	/**
	 *  Return the node room's meta class
	 *  @returns	The meta class of the node
	 */
	const strix::net::object::MetaClass &GetNodeRoomClass() const {
		return GetParameterClass(1);
    }

	/**
	 *  Set the node room's meta class
	 *  @param	nodeClass	The meta class to set
	 */
    void SetNodeRoomClass(const MetaClass &nodeRoomClass) {
		SetParameterClass(1, nodeRoomClass);
    }

	/**
	 *  Return the list of nodes found
	 *  @returns	The list of nodes as strix objects
	 */
	strix::net::object::ObjectList &GetNodes() {
		return m_nodes;
	}

	/**
	 *  Set the nodes found
	 *  @param	nodes	A list of nodes as strix objects
	 */
	void SetNodes(const strix::net::object::ObjectList &nodes) {
		m_nodes = nodes;
	}

	/**
	 *  Return the list of node rooms found
	 *  @returns	The list of node rooms as strix objects
	 */
	strix::net::object::ObjectList &GetNodeRooms() {
		return m_nodeRooms;
	}

	/**
	 *  Set the node rooms found
	 *  @param	nodeRooms	A list of node rooms as strix objects
	 */
	void SetNodeRooms(const strix::net::object::ObjectList &nodeRooms) {
		m_nodeRooms = nodeRooms;
	}

private:
	strix::net::object::ObjectList m_nodes;
	strix::net::object::ObjectList m_nodeRooms;
};

typedef std::shared_ptr<NodeRoomSearchResponse> NodeRoomSearchResponsePtr;

} } } }
