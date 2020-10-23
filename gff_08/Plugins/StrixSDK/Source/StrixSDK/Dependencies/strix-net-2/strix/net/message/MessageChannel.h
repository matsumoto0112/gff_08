#pragma once

#include <strix/net/channel/Channel.h>

#include <memory>
#include <vector>

namespace strix { namespace net { namespace channel {
class SocketChannel;
typedef std::shared_ptr<SocketChannel> SocketChannelPtr;
} } }

namespace strix { namespace net { namespace object {
class Object;
typedef std::shared_ptr<Object> ObjectPtr;
} } }

namespace strix { namespace net { namespace message {

class MessageChannel;
class MessageChannelConfig;
class MessageChannelListener;
class ServerMessageChannel;

typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
typedef std::shared_ptr<MessageChannelListener> MessageChannelListenerPtr;

class MessageChannel : public channel::Channel
{
public:
    MessageChannel() {}

    virtual ~MessageChannel() {}

	virtual const MessageChannelConfig &GetConfig() = 0;

	virtual channel::SocketChannelPtr &GetSocketChannel() = 0;

	virtual const std::shared_ptr<ServerMessageChannel> &GetServerMessageChannel() = 0;
	
    virtual std::vector<MessageChannelListenerPtr> GetListeners() const = 0;

    virtual void AddListener(const MessageChannelListenerPtr &listener) = 0;

    virtual void RemoveListener(const MessageChannelListenerPtr &listener) = 0;

	virtual bool Send(const object::ObjectPtr &message) = 0;
};

typedef std::shared_ptr<strix::net::message::MessageChannel> MessageChannelPtr;

} } }

