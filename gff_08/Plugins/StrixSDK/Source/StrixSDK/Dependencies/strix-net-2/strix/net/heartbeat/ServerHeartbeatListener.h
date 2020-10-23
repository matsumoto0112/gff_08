#pragma once

#include <strix/net/message/ServerMessageChannelListener.h>
#include <strix/net/util/concurrent/ScheduledExecutor.h>
#include <strix/net/heartbeat/HeartbeatListener.h>

#include <chrono>
#include <memory>

namespace strix { namespace net { namespace heartbeat {

class ServerHeartbeatListener : public strix::net::message::ServerMessageChannelListener
{
public:
	typedef strix::net::message::ServerMessageChannelPtr ServerMessageChannelPtr;
	typedef strix::net::message::MessageChannelPtr MessageChannelPtr;
	typedef strix::net::message::MessageChannelListener MessageChannelListener;
	typedef strix::net::util::concurrent::ScheduledExecutor ScheduledExecutor;

	ServerHeartbeatListener() : m_pScheduledExecutor(nullptr) {}

    ServerHeartbeatListener(ScheduledExecutor &scheduledExecutor, const std::chrono::nanoseconds &heartbeatPeriod, const std::chrono::nanoseconds &heartbeatTimeout)
        :	m_pScheduledExecutor(&scheduledExecutor),
			m_heartbeatPeriod(heartbeatPeriod),
			m_heartbeatTimeout(heartbeatTimeout)
	{
    }

    ServerHeartbeatListener(const ServerMessageChannelPtr &pServerMessageChannel, ScheduledExecutor &scheduledExecutor, const std::chrono::nanoseconds &heartbeatPeriod, const std::chrono::nanoseconds &heartbeatTimeout)
        :	m_pServerMessageChannel(pServerMessageChannel),
			m_pScheduledExecutor(&scheduledExecutor),
			m_heartbeatPeriod(heartbeatPeriod),
			m_heartbeatTimeout(heartbeatTimeout)
	{
    }

	MessageChannelListenerPtr CreateMessageChannelListener() override {
		std::shared_ptr<HeartbeatListener> pHeartbeatListener = std::make_shared<HeartbeatListener>();
		pHeartbeatListener->Init(nullptr, *m_pScheduledExecutor, m_heartbeatPeriod, m_heartbeatTimeout);
		return pHeartbeatListener;
    }

	void OnServerListen(const ServerMessageChannelListenEvent &ev) override {
	}

	void OnServerAccept(const ServerMessageChannelAcceptEvent &ev) override {
	}

	void OnServerClose(const ServerMessageChannelCloseEvent &ev) override {
	}

	void OnServerError(const ServerMessageChannelErrorEvent &ev) override {
	}

	void OnServerDetach() override {
	}

private:
	ServerMessageChannelPtr m_pServerMessageChannel;
    ScheduledExecutor *m_pScheduledExecutor;
    std::chrono::nanoseconds m_heartbeatPeriod;
    std::chrono::nanoseconds m_heartbeatTimeout;
};

} } }
