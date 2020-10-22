#pragma once

#include <functional>

namespace strix { namespace net { namespace util { namespace concurrent {

class Executor
{
public:
	virtual ~Executor() {}

	virtual void Execute(std::function<void()> command) = 0;
};

} } } }
