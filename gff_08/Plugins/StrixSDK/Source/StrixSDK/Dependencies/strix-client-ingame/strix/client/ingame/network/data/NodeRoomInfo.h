#pragma once

#include <strix/net/channel/Protocol.h>
#include <strix/net/object/WrapperObject.h>

#include <strix/client/match/node/model/CustomizableMatchServerNode.h>
#include <strix/client/match/node/model/CustomizableMatchServerNodeRoom.h>

#include <memory>
#include <string>

namespace strix { namespace net { namespace channel {
enum class Protocol;
} } }

namespace strix { namespace client { namespace core {
class UID;
typedef std::shared_ptr<UID> UIDPtr;
}}}


namespace strix { namespace client { namespace ingame { namespace network { namespace data {

/**
 *  A container for node and node room information
 */
class NodeRoomInfo
{
public:
	NodeRoomInfo() {}

	NodeRoomInfo(match::node::model::CustomizableMatchServerNodePtr node, match::node::model::CustomizableMatchServerNodeRoomPtr room) : m_node(node), m_room(room) {}

	/**
	 *  Get the node
	 *  @returns	The node
	 */
	match::node::model::CustomizableMatchServerNodePtr GetNode()
	{
		return m_node;
	}

	/**
	 *  Set the node
	 *  @param	node	The node to set
	 */
	void SetNode(match::node::model::CustomizableMatchServerNodePtr node)
	{
		m_node = node;
	}

	/**
	 *  Get the room
	 *  @returns	The room
	 */
	match::node::model::CustomizableMatchServerNodeRoomPtr GetRoom()
	{
		return m_room;
	}

	/**
	 *  Set the room
	 *  @param	room	The room to set
	 */
	void SetRoom(match::node::model::CustomizableMatchServerNodeRoomPtr room)
	{
		m_room = room;
	}

private:
	match::node::model::CustomizableMatchServerNodePtr m_node;
	match::node::model::CustomizableMatchServerNodeRoomPtr m_room;
};

typedef std::shared_ptr<NodeRoomInfo> NodeRoomInfoPtr;

} } } } }
