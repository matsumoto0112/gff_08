#pragma once

#include <strix/net/channel/SocketChannel.h>

namespace strix { namespace net { namespace ssl {
	class SSLContext;
	class SSLEngine;
} } }

namespace strix { namespace net { namespace channel { namespace ssl {
	
class SSLSocketChannel : public SocketChannel
{
public:
	SSLSocketChannel() {}
	virtual ~SSLSocketChannel() {}
};

} } } }
