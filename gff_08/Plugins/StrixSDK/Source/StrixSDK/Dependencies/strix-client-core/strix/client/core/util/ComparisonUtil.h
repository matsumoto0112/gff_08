#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/MetaClass.h>
#include <strix/net/object/MetaClassT.h>
#include <strix/net/object/WrapperObject.h>

#include <cmath>

namespace strix { namespace client { namespace core { namespace util {

class ComparisonUtil
{
public:
	template<typename ListType>
	static int CompareObjectPtrList(const ListType &lhs, const ListType &rhs)
	{
		auto lit = lhs.begin();
		auto rit = rhs.begin();
		while (lit != lhs.end() || rit != rhs.end())
		{
			if (rit == rhs.end())
				return 1;
			if (lit == lhs.end())
				return -1;

			if (*lit && !*rit)
				return 1;
			if (!*lit && !*rit)
				return -1;
			if (*lit) {
				const int val = (*lit)->Compare(**rit);
				if (val != 0)
					return val;
			}

			++lit;
			++rit;
		}

		return 0;
	}
	
	template<typename ObjectPtrType>
	static int CompareObjectPtr(const ObjectPtrType &lhs, const ObjectPtrType &rhs)
	{
		if (lhs && !rhs)
			return 1;
		if (!lhs && rhs)
			return -1;
		if (lhs) {
			const int res = lhs->Compare(*rhs);
			if (res != 0)
				return res;
		}

		return 0;
	}

	template<typename ObjectPtrType>
	static bool NonNullEquals(const ObjectPtrType &lhs, const ObjectPtrType &rhs)
	{
		if (!lhs && !rhs)
			return false;

		return CompareObjectPtr(lhs, rhs) == 0;
	}

	template <typename T>
	static std::enable_if_t<std::is_floating_point<T>::value, bool>
	ApproximatelyEqual(const T &lhs, const T &rhs)
	{
		const T diff = std::abs(lhs - rhs);
		const T maxDiff = std::max(std::abs(lhs), std::abs(rhs)) * std::numeric_limits<T>::epsilon();
		return diff <= maxDiff;
	}

	template <typename T>
	static std::enable_if_t<!std::is_floating_point<T>::value, bool>
	ApproximatelyEqual(const T &lhs, const T &rhs)
	{
		return lhs == rhs;
	}
};

} } } }
