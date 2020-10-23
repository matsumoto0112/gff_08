#pragma once

#include <memory>

namespace strix { namespace net { namespace message {
	class MessageChannel;
	typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }

namespace strix { namespace net { namespace message { namespace event {

class MessageChannelCloseEvent
{
public:
	MessageChannelCloseEvent(const MessageChannelPtr &pMessageChannel)
		: m_pMessageChannel(pMessageChannel) {
    }

	const MessageChannelPtr &GetMessageChannel() const {
        return m_pMessageChannel;
    }

private:
	const MessageChannelPtr &m_pMessageChannel;
};

} } } }
