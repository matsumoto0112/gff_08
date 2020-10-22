#pragma once

#ifdef WIN32
#include <strix/net/socket/win32/Types.h>
#elif defined __NX__
#include <strix/net/socket/nx/Types.h>
#else
#include <strix/net/socket/unix/Types.h>
#endif
