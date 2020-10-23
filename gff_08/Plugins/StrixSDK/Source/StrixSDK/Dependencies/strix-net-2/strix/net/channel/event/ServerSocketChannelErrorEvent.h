#pragma once

#include <memory>

namespace strix { namespace net { namespace channel {
	class ServerSocketChannel;
	typedef std::shared_ptr<ServerSocketChannel> ServerSocketChannelPtr;
} } }

namespace strix { namespace net { namespace channel { namespace event {

class ServerSocketChannelErrorEvent
{
public:
	ServerSocketChannelErrorEvent(const ServerSocketChannelPtr &serverSocketChannel, int errorCode)
		: m_serverSocketChannel(serverSocketChannel), m_errorCode(errorCode) {
    }

	const ServerSocketChannelPtr &GetServerSocketChannel() const {
        return m_serverSocketChannel;
    }

	int GetErrorCode() const {
		return m_errorCode;
	}

private:
	const ServerSocketChannelPtr &m_serverSocketChannel;
	int m_errorCode;
};

} } } }
