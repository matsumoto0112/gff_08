#pragma once

#include <strix/client/core/message/MessageDispatcher.h>
#include <strix/net/message/MessageChannel.h>
#include <strix/net/message/MessageChannelListener.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace connection {

/**
 *  Default message channel listener. Provides methods to call on various message channel events to control message dispatch
 */
class DefaultMessageChannelListener : public strix::net::message::MessageChannelListener
{
public:
	typedef std::shared_ptr<strix::client::core::message::MessageDispatcher> MessageDispatcherPtr;
	typedef std::shared_ptr<strix::net::message::MessageChannel> MessageChannelPtr;

	/**
	 *  Construct a DefaultMessageChannelListener with the given message dispatcher
	 *  @param	messageDispatcher	The message dispatcher to use
	 */
	DefaultMessageChannelListener(const MessageDispatcherPtr &messageDispatcher) {
		m_messageDispatcher = messageDispatcher;
	}
	
	virtual ~DefaultMessageChannelListener() {}


	void OnConnect(const MessageChannelConnectEvent &ev) override;

	/**
	 *  Called when message received on the message channel. Dispatches the message object held by this event with the message dispatcher
	 *  @param	ev	The message channel message event
	 */
	void OnMessage(const MessageChannelMessageEvent &ev) override;

	void OnClose(const MessageChannelCloseEvent &ev) override;
	void OnError(const MessageChannelErrorEvent &ev) override;
	void OnDetach() override;
	
private:
	MessageDispatcherPtr m_messageDispatcher;
};

} } } }
