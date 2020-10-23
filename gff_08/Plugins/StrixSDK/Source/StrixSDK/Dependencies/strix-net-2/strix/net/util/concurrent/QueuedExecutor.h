#pragma once

#include <strix/net/util/concurrent/Executor.h>
#include <strix/net/util/SynchronizedQueue.h>

#include <functional>

namespace strix { namespace net { namespace util { namespace concurrent {

class QueuedExecutor : public Executor
{
public:
	void Execute(std::function<void()> command) override;

	void ExecuteQueued();

private:
	typedef SynchronizedQueue<std::function<void()> > CommandQueue;
	CommandQueue m_commandQueue;
};

} } } }
