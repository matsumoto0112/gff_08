#pragma once

#include <strix/net/message/event/ServerMessageChannelListenEvent.h>
#include <strix/net/message/event/ServerMessageChannelAcceptEvent.h>
#include <strix/net/message/event/ServerMessageChannelCloseEvent.h>
#include <strix/net/message/event/ServerMessageChannelErrorEvent.h>

#include <memory>

namespace strix { namespace net { namespace message {

class MessageChannel;
class MessageChannelListener;
class ServerMessageChannel;

typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
typedef std::shared_ptr<ServerMessageChannel> ServerMessageChannelPtr;

class ServerMessageChannelListener
{
public:
	typedef std::shared_ptr<MessageChannelListener> MessageChannelListenerPtr;
	typedef event::ServerMessageChannelListenEvent ServerMessageChannelListenEvent;
	typedef event::ServerMessageChannelAcceptEvent ServerMessageChannelAcceptEvent;
	typedef event::ServerMessageChannelCloseEvent ServerMessageChannelCloseEvent;
	typedef event::ServerMessageChannelErrorEvent ServerMessageChannelErrorEvent;

	ServerMessageChannelListener() {}
	virtual ~ServerMessageChannelListener() {}

	virtual MessageChannelListenerPtr CreateMessageChannelListener() = 0;

	virtual void OnServerListen(const ServerMessageChannelListenEvent &ev) = 0;

	/**
	 * @brief 通信の受付が完了したときに呼ばれます
	 */
	virtual void OnServerAccept(const ServerMessageChannelAcceptEvent &ev) = 0;

	virtual void OnServerClose(const ServerMessageChannelCloseEvent &ev) = 0;

	virtual void OnServerError(const ServerMessageChannelErrorEvent &ev) = 0;

	virtual void OnServerDetach() = 0;
};

typedef std::shared_ptr<ServerMessageChannelListener> ServerMessageChannelListenerPtr;

} } }

