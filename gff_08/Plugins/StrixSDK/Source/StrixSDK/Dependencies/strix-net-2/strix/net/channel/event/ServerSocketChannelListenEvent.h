#pragma once

#include <memory>

namespace strix { namespace net { namespace channel {
	class ServerSocketChannel;
	typedef std::shared_ptr<ServerSocketChannel> ServerSocketChannelPtr;
} } }

namespace strix { namespace net { namespace channel { namespace event {

class ServerSocketChannelListenEvent
{
public:
	ServerSocketChannelListenEvent(const ServerSocketChannelPtr &serverSocketChannel)
		: m_serverSocketChannel(serverSocketChannel) {
    }

	const ServerSocketChannelPtr &GetServerSocketChannel() const {
        return m_serverSocketChannel;
    }

private:
	const ServerSocketChannelPtr &m_serverSocketChannel;
};

} } } }
