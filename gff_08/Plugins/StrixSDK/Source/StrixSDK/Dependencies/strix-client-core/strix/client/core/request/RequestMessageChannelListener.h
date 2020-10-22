#pragma once

#include <strix/net/message/event/MessageChannelCloseEvent.h>
#include <strix/net/message/event/MessageChannelConnectEvent.h>
#include <strix/net/message/event/MessageChannelMessageEvent.h>
#include <strix/net/message/event/MessageChannelErrorEvent.h>
#include <strix/net/message/MessageChannel.h>
#include <strix/net/message/MessageChannelListener.h>

#include <strix/client/core/RequestClient.h>
#include <strix/client/core/message/MessageDispatcher.h>
#include <strix/client/core/request/RequestDispatcher.h>

namespace strix { namespace client { namespace core { namespace request {

/**
 *  Message channel listener for request messages
 */
class RequestMessageChannelListener : public strix::net::message::MessageChannelListener
{
public:	
	RequestMessageChannelListener(const strix::client::core::message::MessageDispatcherPtr &messageDispatcher, const RequestDispatcherPtr &requestDispatcher)
	: m_messageDispatcher(messageDispatcher), m_requestDispatcher(requestDispatcher) { }
	
	virtual ~RequestMessageChannelListener() {}

	void OnConnect(const strix::net::message::event::MessageChannelConnectEvent &ev) override;

	/**
	 *  Dispatch the message contained in the message channel message event with the message dispatcher
	 *  @param	ev	The message channel message event
	 */
	void OnMessage(const strix::net::message::event::MessageChannelMessageEvent &ev) override;

	void OnClose(const strix::net::message::event::MessageChannelCloseEvent &ev) override;
	void OnError(const strix::net::message::event::MessageChannelErrorEvent &ev) override;
	void OnDetach() override;
	
private:
	strix::client::core::message::MessageDispatcherPtr m_messageDispatcher;
	RequestDispatcherPtr m_requestDispatcher;
};

typedef std::shared_ptr<RequestMessageChannelListener> RequestMessageChannelListenerPtr;

} } } }