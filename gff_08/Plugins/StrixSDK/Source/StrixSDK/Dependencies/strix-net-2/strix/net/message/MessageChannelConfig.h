#pragma once

#include <strix/net/channel/SocketChannelConfig.h>

#include <string>

namespace strix { namespace net { namespace message {

class MessageChannelConfig : public channel::SocketChannelConfig
{
public:
	MessageChannelConfig() {}
	virtual ~MessageChannelConfig() {}

    MessageChannelConfig &SetHost(const std::string &host) {
        channel::SocketChannelConfig::SetHost(host);
		return *this;
    }

    MessageChannelConfig &SetPortNumber(int port) {
		channel::SocketChannelConfig::SetPortNumber(port);
		return *this;
    }

    MessageChannelConfig &SetTimeout(int timeout) {
		channel::SocketChannelConfig::SetTimeout(timeout);
		return *this;
    }

	SocketChannelConfig &SetReadBufferExtendSize(size_t readBufferExtendSize) {
		channel::SocketChannelConfig::SetReadBufferExtendSize(readBufferExtendSize);
		return *this;
	}

	SocketChannelConfig &SetMaxReadBufferSize(size_t maxReadBufferSize) {
		channel::SocketChannelConfig::SetMaxReadBufferSize(maxReadBufferSize);
		return *this;
	}

	SocketChannelConfig &SetMaxWriteBufferSize(size_t maxWriteBufferSize) {
		channel::SocketChannelConfig::SetMaxWriteBufferSize(maxWriteBufferSize);
		return *this;
	}
};

typedef std::shared_ptr<MessageChannelConfig> MessageChannelConfigPtr;

} } }

