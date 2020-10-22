#pragma once

#include <strix/net/message/MessageChannel.h>
#include <strix/net/message/MessageChannelConfig.h>
#include <strix/net/object/Object.h>
#include <strix/net/util/SynchronizedQueue.h>

#include <strix/client/core/connection/HandshakeHandlers.h>

#include <mutex>

namespace strix { namespace client { namespace core { namespace connection {

/**
 *  A wrapper for a message channel. Provides reconnection capability to the message channel
 *  and can queue messages when disconnected and resend on connect
 */
class ReconnectableMessageChannel : public strix::net::message::MessageChannel, public std::enable_shared_from_this<ReconnectableMessageChannel>
{
public:
	ReconnectableMessageChannel(const strix::net::message::MessageChannelConfig &config) :
		strix::net::message::MessageChannel(), m_messageChannelConfig(config), m_shouldConnect(false)
	{	}

	virtual ~ReconnectableMessageChannel() {}

	/**
	 *  Get the socket channel of the underlying message channel
	 *  @returns	The socket channel
	 */
	strix::net::channel::SocketChannelPtr &GetSocketChannel() override;

	/**
	 *  Get the server message channel of the underlying message channel
	 *  @returns	The server message channel
	 */
	const std::shared_ptr<strix::net::message::ServerMessageChannel> &GetServerMessageChannel() override;

	/**
	 *  Get the configuration information of this message channel
	 *  @returns	Config information
	 */
	const strix::net::message::MessageChannelConfig &GetConfig() override;

	/**
	 *  Get a pointer to the raw data of the underlying message channel
	 *  @returns	A pointer to the data
	 */
	void *GetData() override;

	/**
	 *  Set the pointer to the raw data of the underlying message channel
	 *  @param	data	The pointer to the data
	 */
	void SetData(void *data) override;

	/**
	 *  Get the message channel listeners of this message channel
	 *  @returns	A list of the message channel listeners
	 */
	std::vector<strix::net::message::MessageChannelListenerPtr> GetListeners() const override;

	/**
	 *  Add a message channel listener to this message channel
	 *  @param	listener	The listener to add
	 */
	void AddListener(const strix::net::message::MessageChannelListenerPtr &listener) override;

	/**
	 *  Remove a listener from this message channel
	 *  @param	listener	The listener to remove
	 */
	void RemoveListener(const strix::net::message::MessageChannelListenerPtr &listener) override;

	/**
	 *  Return if the underlying message channel is open or not
	 *  @returns	True if channel has connection to server, else false
	 */
	bool IsOpen() override;

	/**
	 *  Get the local address of the underlying message channel
	 *  @returns	The address
	 */
	const strix::net::socket::Address &GetLocalAddress() override;

	/**
	 *  Get the remote address of the underlying message channel
	 *  @returns	The address
	 */
	const strix::net::socket::Address &GetRemoteAddress() override;

	/**
	 *  Close the underlying message channel and destroy it
	 */
	void Close() override;

	/**
	 *  Send the given message on the underlying message channel. If the message channel
	 *  is currently handshaking with the server, the message will be queued for transmission.
	 *  If the message channel is currently disconnected, the message will be queued, and reconnection
	 *  attempted
	 *  @param	message	The message to send
	 *  @returns	False if the message could not be sent. True if the message was sent correctly, or is currently queued
	 */
	bool Send(const strix::net::object::ObjectPtr &message) override;

	/**
	 *  To be called when the underlying message channel has completed its handshake with the server and connected.
	 *  Attempts to send all queued messages
	 */
	void OnHandshakeCompleted();

	/**
	 *  To be called when the underlying message channel has failed to handshake with the server.
	 *  Closes and destroys the message channel and attempts reconnection
	 */
	void OnHandshakeFailed();

	/**
	 *  Return whether this message channel is attempting reconnection
	 *  @returns	True if the message channel is attempting reconnection
	 */
	bool GetShouldConnect()
	{
		return m_shouldConnect;
	}

	/**
	 *  Set if this channel should attempt/not attempt reconnection
	 *  @param	shouldConnect	True if should attempt reconnection, otherwise false
	 */
	void SetShouldConnect(bool shouldConnect)
	{
		m_shouldConnect = shouldConnect;
	}

	/**
	 *  Get if this channel is currently handshaking
	 *  @returns	True if this channel is currently handshaking
	 */
	bool GetIsHandshaking()
	{
		return m_isHandshaking;
	}

	/**
	 *  Set if this channel is handshaking
	 *  @param	isHandshaking	True for is handshaking
	 */
	void SetIsHandshaking(bool isHandshaking)
	{
		m_isHandshaking = isHandshaking;
	}

	/**
	 *  Get the amount of reconnection attempts made so far
	 *  @returns	The number of attempts made
	 */
	int GetCurrentRetry()
	{
		return m_currentRetry;
	}

	/**
	 *  Set the amount of reconnection attempts made
	 *  @param	currentRetry	The number of attempts made
	 */
	void SetCurrentRetry(int currentRetry)
	{
		m_currentRetry = currentRetry;
	}

	/**
	 *  Get the max number of reconnect attempts this channel will make if it becomes disconnected
	 *  @returns	The number of attempts
	 */
	int GetRetryCount()
	{
		return m_retryCount;
	}

	/**
	 *  Get the underlying message channel
	 *  @returns	The underlying message channel
	 */
	const strix::net::message::MessageChannelPtr &GetInnerMessageChannel() const {
		return m_messageChannel;
	}

	/**
	 *  Set the underlying message channel
	 *  @param	messageChannel	The message channel to set
	 */
	void SetInnerMessageChannel(const strix::net::message::MessageChannelPtr &messageChannel) {
		m_messageChannel = messageChannel;
	}

	/**
	 *  Get the current queue of messages waiting to be sent
	 *  @returns	The queue of messages
	 */
	strix::net::util::SynchronizedQueue<strix::net::object::ObjectPtr> &GetMessageQueue()
	{
		return m_messageQueue;
	}

	/**
	 *  Get the handshake context of this message channel
	 *  @returns	The handshake context
	 */
	const HandshakeContext &GetHandshakeContext()
	{
		return m_handshakeContext;
	}

	/**
	 *  Set the handshake context of this message channel
	 *  @param	handshakeContext	The handshake context
	 */
	void SetHandshakeContext(HandshakeContext handshakeContext)
	{
		m_handshakeContext = handshakeContext;
	}

private:
	strix::net::message::MessageChannelPtr m_messageChannel;
	strix::net::message::MessageChannelConfig m_messageChannelConfig;
	std::vector<strix::net::message::MessageChannelListenerPtr> m_listeners;
	strix::net::util::SynchronizedQueue<strix::net::object::ObjectPtr> m_messageQueue;
	HandshakeContext m_handshakeContext;

	bool m_shouldConnect;
	bool m_isHandshaking;
	int m_currentRetry = 0;
	int m_retryCount = 3;
};

typedef std::shared_ptr<ReconnectableMessageChannel> ReconnectableMessageChannelPtr;
typedef std::weak_ptr<ReconnectableMessageChannel> ReconnectableMessageChannelWeakPtr;

} } } }
