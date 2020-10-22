#pragma once

#include <strix/net/message/MessageChannel.h>
#include <strix/net/message/ServerMessageChannel.h>

#include <memory>

namespace strix { namespace net { namespace channel {
enum class Protocol;
class SocketProcessor;
} } }

namespace strix { namespace net { namespace message {

class ServerMessageChannelConfig;
class MessageChannelConfig;

class MessageChannelProcessor
{
public:
	MessageChannelProcessor() {}
	virtual ~MessageChannelProcessor() {}

	static std::unique_ptr<MessageChannelProcessor> Create();

	static std::unique_ptr<MessageChannelProcessor> Create(std::unique_ptr<strix::net::channel::SocketProcessor> pSocketProcessor);

	static std::unique_ptr<MessageChannelProcessor> Create(channel::Protocol protocol);

	virtual MessageChannelPtr Connect(const MessageChannelConfig &config, const MessageChannelListenerPtr &pListener) = 0;

	virtual ServerMessageChannelPtr Listen(const ServerMessageChannelConfig &config, const ServerMessageChannelListenerPtr &pListener) = 0;

	virtual void Process() = 0;
};

} } }

