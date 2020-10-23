#pragma once

#include <memory>

namespace strix { namespace net { namespace channel {
	class SocketChannel;
	class ServerSocketChannel;
	typedef std::shared_ptr<SocketChannel> SocketChannelPtr;
	typedef std::shared_ptr<ServerSocketChannel> ServerSocketChannelPtr;
} } }

namespace strix { namespace net { namespace channel { namespace event {

class ServerSocketChannelAcceptEvent
{
public:
    ServerSocketChannelAcceptEvent(const ServerSocketChannelPtr &serverSocketChannel, const SocketChannelPtr &socketChannel)
		: m_serverSocketChannel(serverSocketChannel),
		  m_socketChannel(socketChannel) {
    }

	const ServerSocketChannelPtr &GetServerSocketChannel() const {
        return m_serverSocketChannel;
    }

	const SocketChannelPtr &GetSocketChannel() const {
        return m_socketChannel;
    }

private:
	const ServerSocketChannelPtr &m_serverSocketChannel;
	const SocketChannelPtr &m_socketChannel;
};

} } } }
