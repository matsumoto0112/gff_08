#pragma once

#include <strix/net/channel/Channel.h>

#include <memory>

namespace strix { namespace net { namespace socket {
	class Socket;
} } }

namespace strix { namespace net { namespace buffer {
	class Buffer;
} } }

namespace strix { namespace net { namespace channel {

class SocketChannelConfig;
class ServerSocketChannel;
class SocketChannelListener;
typedef std::shared_ptr<ServerSocketChannel> ServerSocketChannelPtr;
typedef std::shared_ptr<SocketChannelListener> SocketChannelListenerPtr;

class SocketChannel : public Channel
{
public:
    SocketChannel() {}
    virtual ~SocketChannel() {}

	virtual const SocketChannelConfig &GetConfig() = 0;

    virtual socket::Socket *GetSocket() = 0;
	
    virtual SocketChannelListenerPtr GetListener() const = 0;

    virtual void SetListener(const SocketChannelListenerPtr &pListener) = 0;

	virtual const ServerSocketChannelPtr &GetServerSocketChannel() = 0;

    virtual buffer::Buffer *GetReadBuffer() = 0;

    virtual buffer::Buffer *GetWriteBuffer() = 0;

    virtual void Flush() = 0;

	virtual bool IsWritePossible() = 0;

	virtual bool WriteAndFlush(uint32_t len, uint32_t size, unsigned char *data) = 0;

	virtual void ResetWrite() = 0;
};

} } }

