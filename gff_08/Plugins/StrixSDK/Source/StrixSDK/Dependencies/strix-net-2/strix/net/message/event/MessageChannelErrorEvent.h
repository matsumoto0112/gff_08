#pragma once

#include <memory>

namespace strix { namespace net { namespace message {
	class MessageChannel;
	typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }

namespace strix { namespace net { namespace message { namespace event {

class MessageChannelErrorEvent
{
public:
	MessageChannelErrorEvent(const MessageChannelPtr &pMessageChannel, int errorCode)
		: m_pMessageChannel(pMessageChannel), m_errorCode(errorCode) {
	}

	const MessageChannelPtr &GetMessageChannel() const {
        return m_pMessageChannel;
    }

	int GetErrorCode() const {
		return m_errorCode;
	}

private:
	const MessageChannelPtr &m_pMessageChannel;
	int m_errorCode;
};

} } } }
