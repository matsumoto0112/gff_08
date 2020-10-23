#pragma once

#include <memory>

namespace strix { namespace net { namespace channel {
	class SocketChannel;
	typedef std::shared_ptr<SocketChannel> SocketChannelPtr;
} } }

namespace strix { namespace net { namespace channel { namespace event {

class SocketChannelErrorEvent
{
public:
	SocketChannelErrorEvent(const SocketChannelPtr &socketChannel, int errorCode)
		: m_socketChannel(socketChannel), m_errorCode(errorCode) {
    }

	const SocketChannelPtr &GetSocketChannel() const {
        return m_socketChannel;
    }

	int GetErrorCode() const {
		return m_errorCode;
	}

private:
	const SocketChannelPtr &m_socketChannel;
	int m_errorCode;
};

} } } }
