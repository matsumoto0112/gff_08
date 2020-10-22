#pragma once

#ifdef WIN32

#include <winsock2.h>
#include <windows.h>

#endif

#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <sstream>
#include <memory>
#include <typeinfo>
#include <functional>
#include <atomic>
#include <mutex>
#include <cassert>
#include <algorithm>

#include <strix/net/system/Compatibility.h>
#include <strix/net/system/OS.h>

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#endif
