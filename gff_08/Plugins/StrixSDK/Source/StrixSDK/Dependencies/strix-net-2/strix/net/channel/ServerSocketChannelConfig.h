#pragma once

#include <strix/net/channel/SocketChannelConfig.h>

namespace strix { namespace net { namespace channel {

class ServerSocketChannelConfig
{
public:
	ServerSocketChannelConfig()
		: m_host("127.0.0.1"),
		  m_port(9123),
		  m_pSocketChannelConfig(std::make_shared<SocketChannelConfig>())
	{
	}

	virtual ~ServerSocketChannelConfig() {}

    const std::string &GetHost() const {
        return m_host;
    }

    ServerSocketChannelConfig &SetHost(const std::string &host) {
        m_host = host;
		return *this;
    }

    int GetPortNumber() const {
        return m_port;
    }

    ServerSocketChannelConfig &SetPortNumber(int port) {
        m_port = port;
		return *this;
    }

	const SocketChannelConfig &GetSocketChannelConfig() const {
		return *m_pSocketChannelConfig;
	}

	std::shared_ptr<SocketChannelConfig> GetSocketChannelConfigPtr() const {
		return m_pSocketChannelConfig;
	}

	ServerSocketChannelConfig &SetSocketChannelConfig(const SocketChannelConfig &config) {
		m_pSocketChannelConfig = std::make_shared<SocketChannelConfig>(config);
		return *this;
	}

protected:
	std::string m_host;
    int m_port;
	std::shared_ptr<SocketChannelConfig> m_pSocketChannelConfig;
};

} } }

