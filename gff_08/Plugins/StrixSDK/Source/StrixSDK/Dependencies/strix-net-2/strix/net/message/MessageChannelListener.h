#pragma once

#include <strix/net/message/event/MessageChannelCloseEvent.h>
#include <strix/net/message/event/MessageChannelConnectEvent.h>
#include <strix/net/message/event/MessageChannelMessageEvent.h>
#include <strix/net/message/event/MessageChannelErrorEvent.h>

#include <memory>

namespace strix { namespace net { namespace message {

class MessageChannel;

typedef std::shared_ptr<MessageChannel> MessageChannelPtr;

class MessageChannelListener
{
public:
	typedef event::MessageChannelConnectEvent MessageChannelConnectEvent;
	typedef event::MessageChannelMessageEvent MessageChannelMessageEvent;
	typedef event::MessageChannelCloseEvent MessageChannelCloseEvent;
	typedef event::MessageChannelErrorEvent MessageChannelErrorEvent;

	MessageChannelListener();
	virtual ~MessageChannelListener();

	virtual void OnConnect(const MessageChannelConnectEvent &ev) = 0;

	virtual void OnMessage(const MessageChannelMessageEvent &ev) = 0;

	virtual void OnClose(const MessageChannelCloseEvent &ev) = 0;

	virtual void OnError(const MessageChannelErrorEvent &ev) = 0;

	virtual void OnDetach() = 0;
};

typedef std::shared_ptr<MessageChannelListener> MessageChannelListenerPtr;

} } }

