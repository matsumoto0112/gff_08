#pragma once

#include <memory>

namespace strix { namespace net { namespace message {
	class ServerMessageChannel;
	typedef std::shared_ptr<ServerMessageChannel> ServerMessageChannelPtr;
} } }

namespace strix { namespace net { namespace message { namespace event {

class ServerMessageChannelListenEvent
{
public:
	ServerMessageChannelListenEvent(const ServerMessageChannelPtr &pServerMessageChannel)
		: m_pServerMessageChannel(pServerMessageChannel) {
    }

	const ServerMessageChannelPtr &GetServerMessageChannel() const {
        return m_pServerMessageChannel;
    }

private:
	const ServerMessageChannelPtr &m_pServerMessageChannel;
};

} } } }
