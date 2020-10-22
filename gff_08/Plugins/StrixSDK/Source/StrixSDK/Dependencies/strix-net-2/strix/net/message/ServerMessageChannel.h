#pragma once

#include <strix/net/channel/ServerChannel.h>
#include <strix/net/message/ServerMessageChannelListener.h>

#include <memory>
#include <vector>

namespace strix { namespace net { namespace message {

class ServerMessageChannel;
class ServerMessageChannelConfig;

typedef std::shared_ptr<ServerMessageChannel> ServerMessageChannelPtr;

class ServerMessageChannel : public channel::ServerChannel
{
public:
	ServerMessageChannel() {}
	virtual ~ServerMessageChannel() {}

	virtual const ServerMessageChannelConfig &GetConfig() = 0;
	
    virtual std::vector<ServerMessageChannelListenerPtr> GetListeners() const = 0;

    virtual void AddListener(const ServerMessageChannelListenerPtr &listener) = 0;

    virtual void RemoveListener(const ServerMessageChannelListenerPtr &listener) = 0;
};

} } }

