#pragma once

#include <strix/client/core/connection/ReconnectableMessageChannel.h>

namespace strix { namespace client { namespace core { namespace connection {

/**
 *  Listener for a ReconnectableMessageChannel. Forwards message channel events to the listeners on 
 *  its message channel.  
 */
class ReconnectableMessageChannelListener : public strix::net::message::MessageChannelListener
{
public:
	ReconnectableMessageChannelListener(const ReconnectableMessageChannelPtr &messageChannel) {
		m_messageChannel = messageChannel;
	}

	virtual ~ReconnectableMessageChannelListener() {}

	/**
	 *  Take a message channel connect event and forward to the listeners on the message channel. 
	 *  Call the handshake callback on the message channel
	 *  
	 *  @param	ev	The message channel event
	 */
	void OnConnect(const strix::net::message::event::MessageChannelConnectEvent &ev) override;

	/**
	 *  Take a message channel message event and forward to the listeners on the message channel
	 *
	 *  @param	ev	The message channel event
	 */
	void OnMessage(const strix::net::message::event::MessageChannelMessageEvent &ev) override;

	/**
	 *  Take a message channel close event and forward to the listeners on the message channel
	 *
	 *  @param	ev	The message channel event
	 */
	void OnClose(const strix::net::message::event::MessageChannelCloseEvent &ev) override;

	/**
	 *  Take a message channel error event and forward to the listeners on the message channel.
	 *  If not connected, tell the message channel to attempt reconnection
	 *
	 *  @param	ev	The message channel event
	 */
	void OnError(const strix::net::message::event::MessageChannelErrorEvent &ev) override;

	void OnDetach() override;

private:
	ReconnectableMessageChannelWeakPtr m_messageChannel;

	bool m_isConnected;
};

typedef std::shared_ptr<ReconnectableMessageChannelListener> ReconnectableMessageChannelListenerPtr;

} } } }
