#pragma once

namespace strix { namespace net { namespace util {

struct NumberComparator
{
	template <typename T, typename U>
	static int Compare(const T &v1, const U &v2);
};


template <typename T, typename U>
struct NumberComparatorImpl
{
	static int Compare(const T &v1, const U &v2)
	{
		if (v1 > v2)
			return 1;
		if (v1 < v2)
			return -1;
		return 0;
	}
};

template <typename T, typename U>
struct SignedUnsignedNumberComparator
{
	static int Compare(const T &v1, const U &v2);
};

template <typename T, typename U>
struct UnsignedSignedNumberComparator
{
	static int Compare(const T &v1, const U &v2);
};

#define STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(_Type1, _Type2) \
	template <> struct NumberComparatorImpl<_Type1, _Type2> : public SignedUnsignedNumberComparator<_Type1, _Type2> {}

#define STRIX_NET_DEFINE_UNSIGNED_SIGNED_NUMBER_COMPARATOR_2(_Type1, _Type2) \
	template <> struct NumberComparatorImpl<_Type1, _Type2> : public UnsignedSignedNumberComparator<_Type1, _Type2> {}

#define STRIX_NET_DEFINE_SIGNED_NUMBER_COMPARATOR(_Type) \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(_Type, uint8_t); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(_Type, unsigned short); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(_Type, unsigned int); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(_Type, unsigned long); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(_Type, unsigned long long); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(uint8_t, _Type); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(unsigned short, _Type); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(unsigned int, _Type); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(unsigned long, _Type); \
	STRIX_NET_DEFINE_SIGNED_UNSIGNED_NUMBER_COMPARATOR_2(unsigned long long, _Type);

STRIX_NET_DEFINE_SIGNED_NUMBER_COMPARATOR(int8_t);
STRIX_NET_DEFINE_SIGNED_NUMBER_COMPARATOR(short);
STRIX_NET_DEFINE_SIGNED_NUMBER_COMPARATOR(int);
STRIX_NET_DEFINE_SIGNED_NUMBER_COMPARATOR(long);
STRIX_NET_DEFINE_SIGNED_NUMBER_COMPARATOR(long long);

template <typename T, typename U>
int SignedUnsignedNumberComparator<T, U>::Compare(const T &v1, const U &v2)
{
	if (v1 < 0)
		return -1;

	return NumberComparatorImpl<U, U>::Compare(static_cast<U>(v1), v2);
}

template <typename T, typename U>
int UnsignedSignedNumberComparator<T, U>::Compare(const T &v1, const U &v2)
{
	if (v2 < 0)
		return 1;

	return NumberComparatorImpl<T, T>::Compare(v1, static_cast<T>(v2));
}

template <typename T, typename U>
int NumberComparator::Compare(const T &v1, const U &v2) { return NumberComparatorImpl<T, U>::Compare(v1, v2); }

} } }

