#pragma once

#include <strix/net/channel/ServerSocketChannel.h>

namespace strix { namespace net { namespace ssl {
	class SSLContext;
	class SSLEngine;
} } }

namespace strix { namespace net { namespace channel { namespace ssl {
	
class SSLServerSocketChannel : public ServerSocketChannel
{
public:
	SSLServerSocketChannel() {}
	virtual ~SSLServerSocketChannel() {}
};

} } } }
