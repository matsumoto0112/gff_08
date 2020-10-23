#pragma once

#include <strix/net/system/OS.h>
#include <forward_list>
#include <memory>

#ifdef __GNUC__
	#ifndef GCC_VERSION
		#define GCC_VERSION (__GNUC__ * 10000 \
							+ __GNUC_MINOR__ * 100 \
							+ __GNUC_PATCHLEVEL__)
	#endif
#endif

#ifdef WIN32
	#if _MSC_VER >= 1800  // Visual Studio 2013
		#define HAS_MAKE_UNIQUE
	#endif
#elif defined __clang__
    #if __cplusplus >= 201402L
        #define HAS_MAKE_UNIQUE
    #endif
#elif defined __GNUC__
	#if GCC_VERSION >= 40900
		#define HAS_MAKE_UNIQUE
	#endif
#endif

#ifndef HAS_MAKE_UNIQUE

namespace std {

template <typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args && ...args) {
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}

#endif

