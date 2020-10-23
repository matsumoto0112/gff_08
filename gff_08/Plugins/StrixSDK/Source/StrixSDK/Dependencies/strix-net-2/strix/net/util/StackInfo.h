#pragma once

#ifdef WIN32
#pragma comment(lib, "imagehlp.lib")
#endif

namespace strix { namespace net { namespace util {

class StackInfo
{
public:
	struct StackFrame
	{
		std::string name;
		size_t address;
	};

	static int GetBackTrace(StackFrame *outStackFrames, int numStackFrames, int skipFrames);
};

} } }
