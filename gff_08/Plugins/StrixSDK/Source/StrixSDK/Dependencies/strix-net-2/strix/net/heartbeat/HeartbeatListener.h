#pragma once

#include <strix/net/message/MessageChannel.h>
#include <strix/net/message/MessageChannelListener.h>
#include <strix/net/heartbeat/message/HeartbeatMessage.h>
#include <strix/net/heartbeat/message/HeartbeatResponse.h>
#include <strix/net/util/TimeoutTimer.h>

#include <memory>
#include <chrono>

namespace strix { namespace net { namespace heartbeat {

class HeartbeatListener : public strix::net::message::MessageChannelListener
{
public:
	typedef strix::net::message::MessageChannelPtr MessageChannelPtr;

	HeartbeatListener() : m_pScheduledExecutor(nullptr) {}

	~HeartbeatListener() {
		Stop();
    }

	void Init(const MessageChannelPtr &pMessageChannel, util::concurrent::ScheduledExecutor &scheduledExecutor, const std::chrono::nanoseconds &heartbeatPeriod, const std::chrono::nanoseconds &heartbeatTimeout)
	{
		m_pScheduledExecutor = &scheduledExecutor;
		m_heartbeatPeriod = heartbeatPeriod;
		m_pMessageChannel = pMessageChannel;
		
        if(UseHeartbeatTimer()) {
            heartbeatTimer = util::TimeoutTimer(*m_pScheduledExecutor, std::bind(&HeartbeatListener::OnHeartbeatPeriod, this), m_heartbeatPeriod);
        }

        timeoutTimer = util::TimeoutTimer(*m_pScheduledExecutor, std::bind(&HeartbeatListener::OnTimeout, this), heartbeatTimeout);

        if(m_pMessageChannel && m_pMessageChannel->IsOpen()) {
			auto now = std::chrono::steady_clock::now();
            timeoutTimer.Update(now);

	        if(UseHeartbeatTimer()) {
                heartbeatTimer.Update(now);
            }
        }
	}

	void OnConnect(const MessageChannelConnectEvent &ev) override {
        m_pMessageChannel = ev.GetMessageChannel();

		auto now = std::chrono::steady_clock::now();
        timeoutTimer.Update(now);

	    if(UseHeartbeatTimer()) {
            heartbeatTimer.Update(now);
        }
    }

	void OnMessage(const MessageChannelMessageEvent &ev) override {
		timeoutTimer.Update();

		if (ev.GetMessageObject()->InstanceOf<message::HeartbeatMessage>()) {
			ev.GetMessageChannel()->Send(std::make_shared<message::HeartbeatResponse>());
		}
	}

	void OnClose(const MessageChannelCloseEvent &ev) override {
	}

	void OnError(const MessageChannelErrorEvent &ev) override {
	}

	void OnDetach() override {
        Stop();
	}

    void Stop() {
        timeoutTimer.Stop();

        if(UseHeartbeatTimer()) {
            heartbeatTimer.Stop();
        }
    }

private:
	bool UseHeartbeatTimer() {
		return (m_heartbeatPeriod.count() > 0);
	}

    void OnTimeout() {
        if(!m_pMessageChannel) {
            return;
        }

        if(!m_pMessageChannel->IsOpen()) {
            return;
        }

        m_pMessageChannel->Close();
    }

    void OnHeartbeatPeriod() {
        if(!m_pMessageChannel) {
            return;
        }

        if(!m_pMessageChannel->IsOpen()) {
            return;
        }

        if(UseHeartbeatTimer()) {
            m_pMessageChannel->Send(std::make_shared<message::HeartbeatMessage>());

            heartbeatTimer = util::TimeoutTimer(*m_pScheduledExecutor, std::bind(&HeartbeatListener::OnHeartbeatPeriod, this), m_heartbeatPeriod);
            heartbeatTimer.Update();
        }
    }

	util::concurrent::ScheduledExecutor *m_pScheduledExecutor;
	std::chrono::nanoseconds m_heartbeatPeriod;
	util::TimeoutTimer timeoutTimer;
	util::TimeoutTimer heartbeatTimer;
    MessageChannelPtr m_pMessageChannel;

};

} } }
