#pragma once

#include <strix/net/message/MessageChannelProcessor.h>

#include <strix/client/core/connection/HandshakeHandlers.h>

namespace strix { namespace client { namespace core { namespace connection {

class ReconnectableMessageChannel;
typedef std::shared_ptr<ReconnectableMessageChannel> ReconnectableMessageChannelPtr;
typedef std::weak_ptr<ReconnectableMessageChannel> ReconnectableMessageChannelWeakPtr;

/**
 *  Wrapper for a message channel processor which provides reconnection capability
 */
class ReconnectableMessageChannelProcessor : public strix::net::message::MessageChannelProcessor
{
public:
	ReconnectableMessageChannelProcessor() : m_messageChannelProcessor(strix::net::message::MessageChannelProcessor::Create()) {}

	ReconnectableMessageChannelProcessor(strix::net::channel::Protocol protocol) : m_messageChannelProcessor(strix::net::message::MessageChannelProcessor::Create(protocol)) {}

	ReconnectableMessageChannelProcessor(strix::net::channel::Protocol protocol, HandshakeContext handshakeContext)
		: m_messageChannelProcessor(strix::net::message::MessageChannelProcessor::Create(protocol)), m_defaultHandshakeContext(handshakeContext) {}

	ReconnectableMessageChannelProcessor(std::unique_ptr<strix::net::message::MessageChannelProcessor> messageChannelProcessor)
		: m_messageChannelProcessor(std::move(messageChannelProcessor)) {}

	/**
	 *  Create and return a new ReconnectableMessageChannelProcessor
	 *  @param	protocol	The protocol type to use
	 */
	static std::unique_ptr<MessageChannelProcessor> Create(strix::net::channel::Protocol protocol);

	/**
	 *  Create and return a new ReconnectableMessageChannelProcessor
	 *  @param	protocol	The protocol type to use
	 *  @param	handshakeContext	The handshake context to use
	 */
	static std::unique_ptr<MessageChannelProcessor> Create(strix::net::channel::Protocol protocol, HandshakeContext handshakeContext);

	virtual ~ReconnectableMessageChannelProcessor() {}

	/**
	 *  Create a new ReconnectableMessageChannel and attempt to connect it to the server with the given config information.
	 *  Adds the listener to this new message channel and adds the channel to this processors channel list
	 *  @param	config	The configuration information for the connection attempt
	 *  @param	pListener	The listener to add to the new message channel
	 *  @returns	The new message channel
	 */
	strix::net::message::MessageChannelPtr Connect(const strix::net::message::MessageChannelConfig &config, const strix::net::message::MessageChannelListenerPtr &pListener) override;

	/**
	 *  Create a new ReconnectableMessageChannel and attempt to connect it to the server with the given config information and handshake context.
	 *  Adds the listener to this new message channel and adds the channel to this processors channel list
	 *  @param	config	The configuration information for the connection attempt
	 *  @param	pListener	The listener to add to the new message channel
	 *  @param	handshakeContext	The handshake context to use when connecting
	 *  @returns	The new message channel
	 */
	virtual strix::net::message::MessageChannelPtr ConnectWithHandshake(const strix::net::message::MessageChannelConfig &config, const strix::net::message::MessageChannelListenerPtr &pListener, HandshakeContext handshakeContext);

	/**
	 *  Call the underlying message processor's Listen
	 *  @param	config	The config to use
	 *  @param	pListener	The listener to use
	 *  @returns	The server message channel
	 */
	strix::net::message::ServerMessageChannelPtr Listen(const strix::net::message::ServerMessageChannelConfig &config, const strix::net::message::ServerMessageChannelListenerPtr &pListener) override;

	/**
	 *  Process every message channel. Reconnect those ready for reconnection
	 */
	void Process() override;

	/**
	 *  Attempt reconnection of the given message channel
	 *  @param	messageChannel	The message channel to reconnect
	 *  @returns	True if the message channel is now reconnecting. False if the reconnection attempts are higher than the maximum accepted attempts for the channel
	 */
	bool ReconnectMessageChannel(ReconnectableMessageChannelPtr messageChannel);

	/**
	 *  Set the default handshake context to use if not specified
	 *  @param	defaultHandshakeContext	The context
	 */
	void SetDefaultHandshakeContext(HandshakeContext defaultHandshakeContext)
	{
		m_defaultHandshakeContext = defaultHandshakeContext;
	}

private:
	std::unique_ptr<strix::net::message::MessageChannelProcessor> m_messageChannelProcessor;
	std::vector<ReconnectableMessageChannelWeakPtr> m_messageChannels;

	HandshakeContext m_defaultHandshakeContext;
};

} } } }
