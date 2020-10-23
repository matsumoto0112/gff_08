#pragma once

#include <memory>

namespace strix { namespace net { namespace channel { namespace event {

class SocketChannelCloseEvent;
class SocketChannelConnectEvent;
class SocketChannelReceiveEvent;
class SocketChannelReceiveFromEvent;
class SocketChannelErrorEvent;

} } } }

namespace strix { namespace net { namespace channel {

class SocketChannel;
typedef std::shared_ptr<SocketChannel> SocketChannelPtr;

class SocketChannelListener
{
public:
	SocketChannelListener() {}
	virtual ~SocketChannelListener() {}

	virtual void OnConnect(const event::SocketChannelConnectEvent &ev) = 0;

	virtual void OnReceive(const event::SocketChannelReceiveEvent &ev) = 0;

	virtual void OnReceiveFrom(const event::SocketChannelReceiveFromEvent &ev) = 0;

	virtual void OnClose(const event::SocketChannelCloseEvent &ev) = 0;

	virtual void OnError(const event::SocketChannelErrorEvent &ev) = 0;

	virtual void OnDetach() = 0;
};

typedef std::shared_ptr<SocketChannelListener> SocketChannelListenerPtr;

} } }

