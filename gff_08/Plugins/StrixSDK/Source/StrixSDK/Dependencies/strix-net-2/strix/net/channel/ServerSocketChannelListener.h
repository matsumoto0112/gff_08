#pragma once

#include <memory>

namespace strix { namespace net { namespace channel { namespace event {
	
class ServerSocketChannelListenEvent;
class ServerSocketChannelAcceptEvent;
class ServerSocketChannelCloseEvent;
class ServerSocketChannelErrorEvent;

} } } }

namespace strix { namespace net { namespace channel {

class SocketChannel;
class SocketChannelListener;
class ServerSocketChannel;

typedef std::shared_ptr<SocketChannel> SocketChannelPtr;
typedef std::shared_ptr<ServerSocketChannel> ServerSocketChannelPtr;
typedef std::shared_ptr<SocketChannelListener> SocketChannelListenerPtr;

class ServerSocketChannelListener
{
public:
	ServerSocketChannelListener() {}
	virtual ~ServerSocketChannelListener() {}
	
	virtual SocketChannelListenerPtr CreateSocketChannelListener() = 0;

	virtual void OnServerListen(const event::ServerSocketChannelListenEvent &ev) = 0;

	/**
	 * @brief 通信の受付が完了したときに呼ばれます
	 */
	virtual void OnServerAccept(const event::ServerSocketChannelAcceptEvent &ev) = 0;

	virtual void OnServerClose(const event::ServerSocketChannelCloseEvent &ev) = 0;

	virtual void OnServerError(const event::ServerSocketChannelErrorEvent &ev) = 0;

	virtual void OnServerDetach() = 0;
};

typedef std::shared_ptr<ServerSocketChannelListener> ServerSocketChannelListenerPtr;

} } }

