#pragma once

#include <memory>

namespace strix { namespace net { namespace object {
	class Object;
	typedef std::shared_ptr<Object> ObjectPtr;
} } }

namespace strix { namespace net { namespace message {
	class MessageChannel;
	typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }

namespace strix { namespace net { namespace message { namespace event {

class MessageChannelMessageEvent
{
public:
	MessageChannelMessageEvent(const MessageChannelPtr &pMessageChannel, const object::ObjectPtr &pMessage)
		: m_pMessageChannel(pMessageChannel), m_pMessage(pMessage){
    }

	const MessageChannelPtr &GetMessageChannel() const {
        return m_pMessageChannel;
    }

	const object::ObjectPtr &GetMessageObject() const {
		return m_pMessage;
	}

private:
	const MessageChannelPtr &m_pMessageChannel;
	const object::ObjectPtr &m_pMessage;
};

} } } }
