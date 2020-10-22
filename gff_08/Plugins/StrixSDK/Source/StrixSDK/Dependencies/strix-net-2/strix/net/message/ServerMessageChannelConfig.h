#pragma once

#include <strix/net/channel/SocketChannelConfig.h>
#include <strix/net/channel/ServerSocketChannelConfig.h>
#include <strix/net/message/MessageChannelConfig.h>

#include <memory>
#include <string>

namespace strix { namespace net { namespace message {

class ServerMessageChannelConfig : public channel::ServerSocketChannelConfig
{
public:
	ServerMessageChannelConfig() {}
	virtual ~ServerMessageChannelConfig() {}

    ServerMessageChannelConfig &SetHost(const std::string &host) {
        channel::ServerSocketChannelConfig::SetHost(host);
		return *this;
    }

    ServerMessageChannelConfig &SetPortNumber(int port) {
        channel::ServerSocketChannelConfig::SetPortNumber(port);
		return *this;
    }

	const MessageChannelConfig &GetMessageChannelConfig() const {
		return static_cast<const MessageChannelConfig &>(*m_pSocketChannelConfig);
	}

	std::shared_ptr<MessageChannelConfig> GetMessageChannelConfigPtr() const {
		return std::static_pointer_cast<MessageChannelConfig>(m_pSocketChannelConfig);
	}

	ServerMessageChannelConfig &SetMessageChannelConfig(const MessageChannelConfig &config) {
		m_pSocketChannelConfig = std::static_pointer_cast<channel::SocketChannelConfig>(std::make_shared<MessageChannelConfig>(config));
		return *this;
	}
};

} } }

