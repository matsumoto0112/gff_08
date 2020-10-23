#pragma once

#include <strix/net/System.h>
#include <strix/net/util/StackInfo.h>

namespace strix { namespace net { namespace util {

template <class T>
class DebugSharedPtr : public std::shared_ptr<T>
{
public:
	STRIX_NET_LOGGER("strix.net.util")

	typedef std::shared_ptr<T> BaseType;

	DebugSharedPtr() {}

	DebugSharedPtr(const DebugSharedPtr &p) : BaseType(p)
	{
		Trace(0);
	}

	DebugSharedPtr(const BaseType &p) : BaseType(p)
	{
		Trace(0);
	}

	~DebugSharedPtr()
	{
		Trace(-1);
	}

	DebugSharedPtr& operator=(const DebugSharedPtr &p) {
		BaseType::operator=(p);
		Trace(0);
	}

	using BaseType::operator*;
	using BaseType::operator->;
	using BaseType::operator bool;
	
private:
	void Trace(int incr) {
		STRIX_NET_LOG_DEBUG("shared_ptr " << typeid(T).name() << " use:" << (use_count() + incr) << " " << GetCaller());
	}

	std::string GetCaller()
	{
		StackInfo::StackFrame frame;

		int num = StackInfo::GetBackTrace(&frame, 1, 3);

		std::stringstream st;

		if(num)
		{
			st << frame.name << " - 0x" << std::hex << frame.address;
		}

		return st.str();
	}
};

} } }
