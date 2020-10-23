#pragma once

#include <memory>

namespace strix { namespace net { namespace message {
class MessageChannel;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }

namespace strix { namespace client { namespace core {

/**
 *  Wrapper for notification message types and a message channel
 */
template <typename T>
class NotificationEventArgs {
public:
	NotificationEventArgs() = default;

	NotificationEventArgs(const strix::net::message::MessageChannelPtr &messageChannel, const T &data)
		: m_messageChannel(messageChannel), m_data(data) {}

	strix::net::message::MessageChannelPtr m_messageChannel;
	T m_data;
};

} } }
