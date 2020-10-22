#pragma once

#include <strix/net/message/ServerMessageChannel.h>
#include <strix/net/util/concurrent/ScheduledExecutor.h>
#include <strix/net/heartbeat/ServerHeartbeatListener.h>

#include <chrono>
#include <memory>

namespace strix { namespace net { namespace heartbeat {

class HeartbeatServer
{
public:
	typedef strix::net::message::ServerMessageChannelPtr ServerMessageChannelPtr;

	HeartbeatServer() : m_pScheduledExecutorService(nullptr) {}

    void Enable(const ServerMessageChannelPtr &pServerMessageChannel, util::concurrent::ScheduledExecutor &scheduledExecutor, const std::chrono::nanoseconds &heartbeatPeriod, const std::chrono::nanoseconds &heartbeatTimeout)
	{
		m_pServerMessageChannel = pServerMessageChannel;
		m_pScheduledExecutorService = &scheduledExecutor;
		m_heartbeatPeriod = heartbeatPeriod;
		m_heartbeatTimeout = heartbeatTimeout;

        m_serverHeartbeatListener = std::make_shared<ServerHeartbeatListener>(m_pServerMessageChannel, *m_pScheduledExecutorService, m_heartbeatPeriod, m_heartbeatTimeout);
        m_pServerMessageChannel->AddListener(m_serverHeartbeatListener);
    }

    void Disable()
	{
        m_pServerMessageChannel->RemoveListener(m_serverHeartbeatListener);
    }

private:
	ServerMessageChannelPtr m_pServerMessageChannel;
	util::concurrent::ScheduledExecutor *m_pScheduledExecutorService;
    std::chrono::nanoseconds m_heartbeatPeriod;
    std::chrono::nanoseconds m_heartbeatTimeout;
    std::shared_ptr<ServerHeartbeatListener> m_serverHeartbeatListener;
};

} } }
