#pragma once

#include <strix/net/util/concurrent/Executor.h>

#include <chrono>
#include <functional>

namespace strix { namespace net { namespace util { namespace concurrent {

class ScheduledExecutor : public Executor
{
public:
	virtual void Schedule(std::function<void()> command, std::chrono::nanoseconds delay) = 0;
};

} } } }
