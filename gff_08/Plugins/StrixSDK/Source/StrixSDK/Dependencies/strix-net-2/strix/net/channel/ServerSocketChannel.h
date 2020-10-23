#pragma once

#include <strix/net/channel/ServerChannel.h>

#include <memory>

namespace strix { namespace net { namespace socket {
class Socket;
} } }

namespace strix { namespace net { namespace channel {

class ServerSocketChannelListener;
class ServerSocketChannelConfig;

typedef std::shared_ptr<ServerSocketChannelListener> ServerSocketChannelListenerPtr;

class ServerSocketChannel : public ServerChannel
{
public:
	ServerSocketChannel() {}
	virtual ~ServerSocketChannel() {}

	virtual const ServerSocketChannelConfig &GetConfig() = 0;
	
    virtual socket::Socket *GetSocket() = 0;

	virtual ServerSocketChannelListenerPtr GetListener() const = 0;

	virtual void SetListener(const ServerSocketChannelListenerPtr &pListener) = 0;
};

typedef std::shared_ptr<ServerSocketChannel> ServerSocketChannelPtr;

} } }

