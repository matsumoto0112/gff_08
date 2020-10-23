#pragma once

#include <strix/client/core/error/ErrorCategory.h>

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace strix { namespace client { namespace ingame { namespace network { namespace data {
class NodeRoomInfo;
class RoomInfo;
typedef std::shared_ptr<RoomInfo> RoomInfoPtr;
typedef std::shared_ptr<NodeRoomInfo> NodeRoomInfoPtr;
} } } } }

namespace strix { namespace client { namespace match { namespace node { namespace model {
class CustomizableMatchServerNode;
typedef std::shared_ptr<CustomizableMatchServerNode> CustomizableMatchServerNodePtr;
} } } } }

namespace strix { namespace client { namespace match { namespace room { namespace model {
class CustomizableMatchRoom;
typedef std::shared_ptr<CustomizableMatchRoom> CustomizableMatchRoomPtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace network {

class RoomServerConnection;
typedef std::shared_ptr<RoomServerConnection> RoomServerConnectionPtr;
typedef std::weak_ptr<RoomServerConnection> RoomServerConnectionWeakPtr;
class MasterServerConnection;
typedef std::shared_ptr<MasterServerConnection> MasterServerConnectionPtr;
typedef std::weak_ptr<MasterServerConnection> MasterServerConnectionWeakPtr;
class RoomContext;
typedef std::shared_ptr<RoomContext> RoomContextPtr;
typedef std::weak_ptr<RoomContext> RoomContextWeakPtr;

class RoomServerConnectEventArgs
{
public:
	RoomServerConnectEventArgs(RoomServerConnectionPtr connection) : m_connection(std::move(connection)) {}
	RoomServerConnectionPtr GetConnection() const {return m_connection;}
private:
	RoomServerConnectionPtr m_connection;
};

class MasterServerConnectEventArgs
{
public:
	MasterServerConnectEventArgs(MasterServerConnectionPtr connection) : m_connection(std::move(connection)) {}
	MasterServerConnectionPtr GetConnection() const {return m_connection;}
private:
	MasterServerConnectionPtr m_connection;
};

class ServerConnectFailedEventArgs
{
public:
	ServerConnectFailedEventArgs(int errorCode, core::error::ErrorCategory errorCategory = core::error::ErrorCategory::StrixClient)
		: m_errorCode(errorCode), m_errorCategory(std::move(errorCategory)) {}

	int GetErrorCode() const {return m_errorCode;}
	core::error::ErrorCategory GetErrorCategory() const {return m_errorCategory;}
private:
	int m_errorCode;
	core::error::ErrorCategory m_errorCategory;
};

class RequestFailedEventArgs
{
public:
	RequestFailedEventArgs(int errorCode, core::error::ErrorCategory errorCategory = core::error::ErrorCategory::StrixClient)
		: m_errorCode(errorCode), m_errorCategory(std::move(errorCategory)) {}
	int GetErrorCode() const {return m_errorCode;}
	core::error::ErrorCategory GetErrorCategory() const {return m_errorCategory;}
private:
	int m_errorCode;
	core::error::ErrorCategory m_errorCategory;
};

class MasterServerConnectionClosedEventArgs
{
public:
	MasterServerConnectionClosedEventArgs(MasterServerConnectionWeakPtr masterServerConnection) : m_masterServerConnection(std::move(masterServerConnection)) {}
	MasterServerConnectionWeakPtr GetMasterServerConnection() const { return m_masterServerConnection; }
private:
	MasterServerConnectionWeakPtr m_masterServerConnection;
};

class RoomServerConnectionClosedEventArgs
{
public:
	RoomServerConnectionClosedEventArgs(RoomServerConnectionWeakPtr roomServerConnection) : m_roomServerConnection(std::move(roomServerConnection)) {}
	RoomServerConnectionWeakPtr GetRoomServerConnection() const { return m_roomServerConnection; }
private:
	RoomServerConnectionWeakPtr m_roomServerConnection;
};

class RoomContextOpenEventArgs
{
public:
	RoomContextOpenEventArgs(RoomContextPtr roomContext) : m_roomContext(std::move(roomContext)) {}
	RoomContextPtr GetRoomContext() const {return m_roomContext;}
private:
	RoomContextPtr m_roomContext;
};

class RoomContextInvalidateEventArgs
{
public:
	RoomContextInvalidateEventArgs(RoomContextWeakPtr roomContext) : m_roomContext(std::move(roomContext)) {}
	RoomContextWeakPtr GetRoomContext() const {return m_roomContext;}
private:
	RoomContextWeakPtr m_roomContext;
};

class NodeSearchEventArgs
{
public:
	NodeSearchEventArgs(std::vector<client::match::node::model::CustomizableMatchServerNodePtr> nodeCollection)
		: m_nodeCollection(std::move(nodeCollection)) {}

	virtual ~NodeSearchEventArgs() = default;

	const std::vector<client::match::node::model::CustomizableMatchServerNodePtr> &GetNodeInfoCollection() const
	{
		return m_nodeCollection;
	}

private:
	std::vector<client::match::node::model::CustomizableMatchServerNodePtr> m_nodeCollection;
};

class NodeRoomSearchEventArgs
{
public:
	NodeRoomSearchEventArgs(std::vector<data::NodeRoomInfoPtr> roomInfoCollection)
		: m_roomInfoCollection(std::move(roomInfoCollection)) {}

	virtual ~NodeRoomSearchEventArgs() = default;

	const std::vector<data::NodeRoomInfoPtr> &GetRoomInfoCollection() const
	{
		return m_roomInfoCollection;
	}

private:
	std::vector<data::NodeRoomInfoPtr> m_roomInfoCollection;
};

class RoomSearchEventArgs
{
public:
	RoomSearchEventArgs(std::vector<client::match::room::model::CustomizableMatchRoomPtr> roomInfoCollection)
		: m_roomInfoCollection(std::move(roomInfoCollection)) {}

	virtual ~RoomSearchEventArgs() = default;

	const std::vector<client::match::room::model::CustomizableMatchRoomPtr> &GetRoomInfoCollection() const
	{
		return m_roomInfoCollection;
	}

private:
	std::vector<client::match::room::model::CustomizableMatchRoomPtr> m_roomInfoCollection;
};

class RoomCreateEventArgs
{
public:
	RoomCreateEventArgs() = default;
	virtual ~RoomCreateEventArgs() = default;
};

class RoomSetEventArgs
{
public:
	RoomSetEventArgs() = default;
	virtual ~RoomSetEventArgs() = default;
};

class RoomDeleteEventArgs
{
public:
	RoomDeleteEventArgs() = default;
	virtual ~RoomDeleteEventArgs() = default;
};

class RoomLeaveEventArgs
{
public:
	RoomLeaveEventArgs() = default;
	virtual ~RoomLeaveEventArgs() = default;
};

class RoomMemberGetEventArgs
{
public:
	RoomMemberGetEventArgs() = default;
	virtual ~RoomMemberGetEventArgs() = default;
};

class RoomMemberSetEventArgs
{
public:
	RoomMemberSetEventArgs() = default;
	virtual ~RoomMemberSetEventArgs() = default;
};

class RoomRelayEventArgs
{
public:
	RoomRelayEventArgs() = default;
	virtual ~RoomRelayEventArgs() = default;
};

class RoomDirectRelayEventArgs
{
public:
	RoomDirectRelayEventArgs() = default;
	virtual ~RoomDirectRelayEventArgs() = default;
};

class RoomMemberKickEventArgs
{
public:
	RoomMemberKickEventArgs() = default;
	virtual ~RoomMemberKickEventArgs() = default;
};

template <typename T>
class ContextualFailureEventArgs
{
public:
	ContextualFailureEventArgs(std::shared_ptr<T> contextPtr, int errorCode, core::error::ErrorCategory errorCategory = core::error::ErrorCategory::StrixClient)
		: m_context(contextPtr), m_errorCode(errorCode), m_errorCategory(std::move(errorCategory)) {}

	ContextualFailureEventArgs(std::weak_ptr<T> contextPtr, int errorCode, core::error::ErrorCategory errorCategory = core::error::ErrorCategory::StrixClient)
		: m_context(contextPtr), m_errorCode(errorCode), m_errorCategory(std::move(errorCategory)) {}

	virtual ~ContextualFailureEventArgs() = default;

	std::weak_ptr<T> GetContext() const
	{
		return m_context.lock();
	}

	int GetErrorCode() const
	{
		return m_errorCode;
	}

	core::error::ErrorCategory GetErrorCategory() const
	{
		return m_errorCategory;
	}

private:
	std::weak_ptr<T> m_context;
	int m_errorCode;
	core::error::ErrorCategory m_errorCategory;
};

typedef ContextualFailureEventArgs<MasterServerConnection> MasterServerConnectionFailureEventArgs;

typedef ContextualFailureEventArgs<RoomServerConnection> RoomServerConnectionFailureEventArgs;

typedef ContextualFailureEventArgs<RoomContext> RoomContextFailureEventArgs;

typedef std::function<void(ServerConnectFailedEventArgs)> ServerConnectFailedEventHandler;

typedef std::function<void(NodeSearchEventArgs)> NodeSearchEventHandler;

typedef std::function<void(NodeRoomSearchEventArgs)> NodeRoomSearchEventHandler;

typedef std::function<void(RoomSearchEventArgs)> RoomSearchEventHandler;

typedef std::function<void(RoomCreateEventArgs)> RoomCreateEventHandler;

typedef std::function<void(RoomSetEventArgs)> RoomSetEventHandler;

typedef std::function<void(RoomDeleteEventArgs)> RoomDeleteEventHandler;

typedef std::function<void(RoomLeaveEventArgs)> RoomLeaveEventHandler;

typedef std::function<void(RoomMemberGetEventArgs)> RoomMemberGetEventHandler;

typedef std::function<void(RoomMemberSetEventArgs)> RoomMemberSetEventHandler;

typedef std::function<void(RoomRelayEventArgs)> RoomRelayEventHandler;

typedef std::function<void(RoomDirectRelayEventArgs)> RoomDirectRelayEventHandler;

typedef std::function<void(RoomMemberKickEventArgs)> RoomMemberKickEventHandler;

typedef std::function<void(MasterServerConnectionFailureEventArgs)> MasterServerConnectionFailureEventHandler;

typedef std::function<void(RoomServerConnectionFailureEventArgs)> RoomServerConnectionFailureEventHandler;

typedef std::function<void(RoomContextFailureEventArgs)> RoomContextFailureEventHandler;

typedef std::function<void(RoomContextOpenEventArgs)> RoomContextOpenEventHandler;

typedef std::function<void(RoomContextInvalidateEventArgs)> RoomContextInvalidateEventHandler;

typedef std::function<void(RoomServerConnectEventArgs)> RoomServerConnectEventHandler;

typedef std::function<void(RoomServerConnectionClosedEventArgs)> RoomServerConnectionClosedEventHandler;

typedef std::function<void(MasterServerConnectionClosedEventArgs)> MasterServerConnectionClosedEventHandler;

} } } }
