#pragma once

#include <strix/net/channel/SocketChannel.h>
#include <strix/net/channel/SocketChannelListener.h>
#include <strix/net/channel/ServerSocketChannel.h>
#include <strix/net/channel/ServerSocketChannelListener.h>

namespace strix { namespace licensing { namespace client {
class LicenseClient;
} } }

namespace strix { namespace net { namespace channel {

enum class Protocol;

class SocketProcessor
{
public:
	SocketProcessor() {}
	virtual ~SocketProcessor() {}

	static std::unique_ptr<SocketProcessor> Create();
	static std::unique_ptr<SocketProcessor> Create(Protocol protocol);

	virtual SocketChannelPtr Connect(const SocketChannelConfig &config, const SocketChannelListenerPtr &pListener) = 0;

	virtual ServerSocketChannelPtr Listen(const ServerSocketChannelConfig &config, const ServerSocketChannelListenerPtr &pListener) = 0;

	virtual void Process() = 0;

	virtual void Stop() = 0;
};

} } }

