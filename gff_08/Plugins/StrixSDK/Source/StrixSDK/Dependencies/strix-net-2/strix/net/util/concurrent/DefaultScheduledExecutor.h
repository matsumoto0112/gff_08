#pragma once

#include <strix/net/util/concurrent/ScheduledExecutor.h>
#include <strix/net/util/SynchronizedPriorityQueue.h>

#include <chrono>
#include <functional>

namespace strix { namespace net { namespace util { namespace concurrent {

class DefaultScheduledExecutor : public ScheduledExecutor
{
public:
	void Execute(std::function<void()> command) override;

	void Schedule(std::function<void()> command, std::chrono::nanoseconds delay) override;

	void ExecuteQueued();

private:
	struct Job
	{
		std::function<void()> command;
		std::chrono::steady_clock::time_point time;

		bool operator<(const Job &rhs) const {
			if(time > rhs.time)
				return true;
			else if(time < rhs.time)
				return false;

			return (this < &rhs);
		}

		void Cancel()
		{
			command = std::function<void()>();
		}
	};

	typedef SynchronizedPriorityQueue<Job> PriorityQueue;
	PriorityQueue m_priorityQueue;
};

} } } }
