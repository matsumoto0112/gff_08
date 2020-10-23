#pragma once

#include <memory>

namespace strix { namespace net { namespace channel {
	class SocketChannel;
	typedef std::shared_ptr<SocketChannel> SocketChannelPtr;
} } }

namespace strix { namespace net { namespace channel { namespace event {

class SocketChannelConnectEvent
{
public:
	SocketChannelConnectEvent(const SocketChannelPtr &socketChannel)
		: m_socketChannel(socketChannel) {
    }

	const SocketChannelPtr &GetSocketChannel() const {
        return m_socketChannel;
    }

private:
	const SocketChannelPtr &m_socketChannel;
};

} } } }
