#pragma once

#include <strix/net/message/MessageChannel.h>
#include <strix/net/util/concurrent/ScheduledExecutor.h>
#include <strix/net/heartbeat/HeartbeatListener.h>

#include <memory>
#include <chrono>

namespace strix { namespace net { namespace heartbeat {

class HeartbeatClient
{
public:
	typedef strix::net::message::MessageChannelPtr MessageChannelPtr;

	HeartbeatClient() : m_pScheduledExecutorService(nullptr), m_heartbeatListener(std::make_shared<HeartbeatListener>()){}

    void Enable(const MessageChannelPtr &pMessageChannel, util::concurrent::ScheduledExecutor &scheduledExecutor, const std::chrono::nanoseconds &heartbeatPeriod, const std::chrono::nanoseconds &heartbeatTimeout)
	{
		m_pMessageChannel = pMessageChannel;
		m_pScheduledExecutorService = &scheduledExecutor;
		m_heartbeatPeriod = heartbeatPeriod;
		m_heartbeatTimeout = heartbeatTimeout;

		m_heartbeatListener->Init(m_pMessageChannel, *m_pScheduledExecutorService, m_heartbeatPeriod, m_heartbeatTimeout);
        m_pMessageChannel->AddListener(m_heartbeatListener);
    }

    void Disable()
	{
        m_pMessageChannel->RemoveListener(m_heartbeatListener);
    }

private:
	MessageChannelPtr m_pMessageChannel;
	util::concurrent::ScheduledExecutor *m_pScheduledExecutorService;
    std::chrono::nanoseconds m_heartbeatPeriod;
    std::chrono::nanoseconds m_heartbeatTimeout;
    std::shared_ptr<HeartbeatListener> m_heartbeatListener;
};

} } }
