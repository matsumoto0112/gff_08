#pragma once

#include <memory>

namespace strix { namespace net { namespace message {
	class MessageChannel;
	class ServerMessageChannel;
	typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
	typedef std::shared_ptr<ServerMessageChannel> ServerMessageChannelPtr;
} } }

namespace strix { namespace net { namespace message { namespace event {

class ServerMessageChannelAcceptEvent
{
public:
	ServerMessageChannelAcceptEvent(const ServerMessageChannelPtr &pServerMessageChannel, const MessageChannelPtr &pMessageChannel)
		: m_pServerMessageChannel(pServerMessageChannel), m_pMessageChannel(pMessageChannel){
    }

	const ServerMessageChannelPtr &GetServerMessageChannel() const {
        return m_pServerMessageChannel;
    }

	const MessageChannelPtr &GetMessageChannel() const {
		return m_pMessageChannel;
	}

private:
	const ServerMessageChannelPtr &m_pServerMessageChannel;
	const MessageChannelPtr &m_pMessageChannel;
};

} } } }
