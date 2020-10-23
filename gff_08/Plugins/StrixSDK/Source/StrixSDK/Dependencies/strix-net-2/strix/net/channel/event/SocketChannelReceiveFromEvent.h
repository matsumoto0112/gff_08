#pragma once

#include <strix/net/stream/FixedSizeMemoryStream.h>

#include <memory>

namespace strix { namespace net { namespace channel {
	class SocketChannel;
	typedef std::shared_ptr<SocketChannel> SocketChannelPtr;
} } }

namespace strix { namespace net { namespace channel { namespace event {

class SocketChannelReceiveFromEvent
{
public:
	typedef strix::net::stream::FixedSizeMemoryStream FixedSizeMemoryStream;

	SocketChannelReceiveFromEvent(const SocketChannelPtr &socketChannel, const std::shared_ptr<FixedSizeMemoryStream> &memoryStream)
		: m_socketChannel(socketChannel), m_memoryStream(memoryStream) {
    }

	const SocketChannelPtr &GetSocketChannel() const {
        return m_socketChannel;
    }

	const std::shared_ptr<FixedSizeMemoryStream> &GetBuffer() const {
		return m_memoryStream;
	}

private:
	const SocketChannelPtr &m_socketChannel;
	const std::shared_ptr<FixedSizeMemoryStream> &m_memoryStream;
};

} } } }
