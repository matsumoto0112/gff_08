#pragma once

#include <strix/net/channel/Channel.h>

namespace strix { namespace net { namespace channel {

class ServerChannel : public Channel
{
public:
	ServerChannel() {}
	virtual ~ServerChannel() {}
};

typedef std::shared_ptr<ServerChannel> ServerChannelPtr;

} } }

