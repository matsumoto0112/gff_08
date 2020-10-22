#pragma once

#include <memory>

namespace strix { namespace net { namespace socket {
	class Address;
} } }

namespace strix { namespace net { namespace channel {

class Channel
{
public:
    Channel() {}
    virtual ~Channel() {}

    virtual bool IsOpen() = 0;
	
    virtual const socket::Address &GetLocalAddress() = 0;

    virtual const socket::Address &GetRemoteAddress() = 0;

    virtual void Close() = 0;

	virtual void *GetData() = 0;

	virtual void SetData(void *data) = 0;
};

typedef std::shared_ptr<Channel> ChannelPtr;

} } }

