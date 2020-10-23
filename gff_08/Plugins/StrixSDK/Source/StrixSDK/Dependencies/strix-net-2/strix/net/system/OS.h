#pragma once
#pragma warning(disable:4819)

#if defined(DEBUG)
#if !defined(_DEBUG)
#define _DEBUG
#endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#  define STRIX_NET_WIN

#elif defined(__APPLE__)
#  include "TargetConditionals.h"
#  define STRIX_NET_APPLE
#  define STRIX_NET_UNIX
#  if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#    define STRIX_NET_IOS
#  elif TARGET_OS_MAC
#    define STRIX_NET_MACOS
#  else
#    error "Unknown Apple platform"
#  endif

#elif defined(__linux__)
#  define STRIX_NET_LINUX
#  define STRIX_NET_UNIX
#
#  if defined(__ANDROID__)
#    define STRIX_NET_ANDROID
#  endif

#elif defined(__NX__)
#    define STRIX_NET_NX

#else
#   error "unsupported platform";
#endif

#if defined(__i386__) || defined(__x86_64__)
#  define STRIX_NET_X86

#elif defined(__arm__) || defined(__ARMEL__) || defined(__arm64__) || defined(__aarch64__)
#  define STRIX_NET_ARM
#  if defined(__arm64__) || defined(__aarch64__)
#    define STRIX_NET_ARM64
#  endif

#elif defined(_WIN64)
#  if defined(_M_IX86)
#    define STRIX_NET_X86
#  else
#    define STRIX_NET_X64
#  endif
#elif defined(_WIN32) && defined(_M_IX86)
#    define STRIX_NET_X86

#else
#  error "unsupported cpu architecture"
#endif
