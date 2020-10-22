#pragma once

#include <strix/net/util/concurrent/ScheduledExecutor.h>
#include <strix/net/util/concurrent/FutureTask.h>

#include <chrono>
#include <functional>
#include <mutex>

namespace strix { namespace net { namespace util {

class TimeoutTimer
{
public:
	TimeoutTimer() : m_pScheduledExecutor(nullptr) {}

    TimeoutTimer(concurrent::ScheduledExecutor &scheduledExecutor, std::function<void ()> timeoutCallback, std::chrono::nanoseconds timeout)
        :	m_pScheduledExecutor(&scheduledExecutor),
			m_timeoutCallback(timeoutCallback),
			m_timeout(timeout) {
    }

	TimeoutTimer(const TimeoutTimer &rhs) {
		operator=(rhs);
	}

	TimeoutTimer(TimeoutTimer &&rhs) = default;

	~TimeoutTimer() {
		Stop();
    }

	TimeoutTimer &operator=(const TimeoutTimer &rhs) {
		m_pScheduledExecutor = rhs.m_pScheduledExecutor;
		m_timeoutCallback = rhs.m_timeoutCallback;
		m_futureTask = rhs.m_futureTask;
		m_timeout = rhs.m_timeout;
		m_timeoutTime = rhs.m_timeoutTime;
		return *this;
	}

	TimeoutTimer &operator=(TimeoutTimer &&rhs) = default;

    bool CheckTimeout() {
        auto now = std::chrono::steady_clock::now();
        return CheckTimeout(now);
    }

    bool CheckTimeout(const std::chrono::steady_clock::time_point &now) {
		std::lock_guard<std::mutex> lock(m_mutex);
        return (now >= m_timeoutTime);
    }

    bool Update() {
		if(!m_timeoutCallback)
			return false;

        auto now = std::chrono::steady_clock::now();
        return Update(now);
    }

    bool Update(const std::chrono::steady_clock::time_point &now) {
		std::lock_guard<std::mutex> lock(m_mutex);

		if(!m_timeoutCallback)
			return false;

        m_timeoutTime = now + m_timeout;

		m_futureTask.Cancel();
		m_futureTask = concurrent::FutureTask<void>(std::bind(&TimeoutTimer::OnTimeout, this));

        m_pScheduledExecutor->Schedule(m_futureTask, m_timeout);

		return true;
    }

    void Stop() {
		std::lock_guard<std::mutex> lock(m_mutex);

		m_futureTask.Cancel();
        m_timeoutCallback = nullptr;
    }

private:
	void OnTimeout() {
		std::function<void()> callback;

		{
			std::lock_guard<std::mutex> lock(m_mutex);

            callback = m_timeoutCallback;
            m_timeoutCallback = nullptr;
        }

        if(callback) {
            callback();
        }
	}

    concurrent::ScheduledExecutor *m_pScheduledExecutor;
	std::function<void()> m_timeoutCallback;
    concurrent::FutureTask<void> m_futureTask;
    std::chrono::nanoseconds m_timeout;
    std::chrono::steady_clock::time_point m_timeoutTime;
	std::mutex m_mutex;
};

} } }
