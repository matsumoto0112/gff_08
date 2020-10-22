#pragma once

#include <strix/net/system/OS.h>

#if defined(STRIX_NET_APPLE)
#  include <machine/endian.h>
#elif defined(__GNUC__) || defined(STRIX_NET_ANDROID)
#  include <endian.h>
#endif

#if defined(__BYTE_ORDER)
#  if defined(__BIG_ENDIAN) && (__BYTE_ORDER == __BIG_ENDIAN)
#    define STRIX_NET_BIG_ENDIAN
#  elif defined(__LITTLE_ENDIAN) && (__BYTE_ORDER == __LITTLE_ENDIAN)
#    define STRIX_NET_LITTLE_ENDIAN
#  endif
#elif defined(BYTE_ORDER)
#  if defined(BIG_ENDIAN) && (BYTE_ORDER == BIG_ENDIAN)
#    define STRIX_NET_BIG_ENDIAN
#  elif defined(LITTLE_ENDIAN) && (BYTE_ORDER == LITTLE_ENDIAN)
#    define STRIX_NET_LITTLE_ENDIAN
#  endif
#endif

#if defined(STRIX_NET_WIN)
#  define STRIX_NET_LITTLE_ENDIAN
#endif

#if !defined(STRIX_NET_BIG_ENDIAN) && !defined(STRIX_NET_LITTLE_ENDIAN)
#  error "could not detect endian"
#endif


namespace strix { namespace net { namespace system {

class Endian
{
public:
	static int8_t Reverse(const int8_t &value) {
		return value;
	}

	static int16_t Reverse(const int16_t &value) {
		return ((value >> 8) & 0xff) | ((value & 0xff) << 8);
	}

	static int32_t Reverse(const int32_t &value) {
		return ((value & 0xff000000) >> 24) | ((value & 0x00ff0000) >> 8)
			| ((value & 0x0000ff00) << 8) | ((value & 0x000000ff) << 24);
	}

	static int64_t Reverse(const int64_t &value) {
		return ((value & 0xff00000000000000ull) >> 56)
			| ((value & 0x00ff000000000000ull) >> 40)
			| ((value & 0x0000ff0000000000ull) >> 24)
			| ((value & 0x000000ff00000000ull) >> 8)
			| ((value & 0x00000000ff000000ull) << 8)
			| ((value & 0x0000000000ff0000ull) << 24)
			| ((value & 0x000000000000ff00ull) << 40)
			| ((value & 0x00000000000000ffull) << 56);
	}

	static uint8_t Reverse(const uint8_t &value) {
		return value;
	}

	static uint16_t Reverse(const uint16_t &value) {
		return Reverse(static_cast<const int16_t &>(value));
	}

	static uint32_t Reverse(const uint32_t &value) {
		return Reverse(static_cast<const int32_t &>(value));
	}

	static uint64_t Reverse(const uint64_t &value) {
		return Reverse(static_cast<const int64_t &>(value));
	}

	static float Reverse(const float &value) {
		int32_t v = Reverse(reinterpret_cast<const int32_t &>(value));
		return reinterpret_cast<float&>(v);
	}

	static double Reverse(const double &value) {
		int64_t v = Reverse(reinterpret_cast<const int64_t &>(value));
		return reinterpret_cast<double&>(v);
	}
};

class LittleEndian
{
public:
	template <typename T>
	static T Convert(const T &value)
	{
	#ifdef STRIX_NET_LITTLE_ENDIAN
		return value;
	#else
		return Endian::Reverse(value);
	#endif
	}
};

class BigEndian
{
public:
	template <typename T>
	static T Convert(const T &value)
	{
	#ifdef STRIX_NET_LITTLE_ENDIAN
		return Endian::Reverse(value);
	#else
		return value;
	#endif
	}
};

} } }
