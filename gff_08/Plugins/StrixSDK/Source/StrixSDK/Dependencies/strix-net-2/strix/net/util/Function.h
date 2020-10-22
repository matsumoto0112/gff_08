#pragma once

#include <functional>

namespace strix { namespace net { namespace util {
	
template <typename T, typename PtrType, typename RetType>
std::function<RetType (void)> Delegate(PtrType p, RetType (T::*mem_func)(void))
{
	return std::bind(mem_func, p);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1>
std::function<RetType (ArgType1)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1))
{
	return std::bind(mem_func, p, std::placeholders::_1);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2>
std::function<RetType (ArgType1, ArgType2)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3>
std::function<RetType (ArgType1, ArgType2, ArgType3)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8);
};

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9)> Delegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9))
{
	return std::bind(mem_func, p, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9);
};

} } }
