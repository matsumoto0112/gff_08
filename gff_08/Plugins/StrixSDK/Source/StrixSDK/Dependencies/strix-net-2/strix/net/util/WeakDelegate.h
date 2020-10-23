#pragma once

#include <functional>
#include <memory>

namespace strix { namespace net { namespace util {
	
template <typename T, typename PtrType, typename RetType>
std::function<RetType ()> WeakDelegate(PtrType p, RetType (T::*mem_func)())
{
	return std::function<void ()>([p, mem_func]() {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)();
			});
}
	
template <typename T, typename PtrType, typename RetType, typename ArgType1>
std::function<RetType (ArgType1)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1))
{
	return std::function<void (ArgType1)>([p, mem_func](ArgType1 arg1) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1);
			});
}
	
template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2>
std::function<RetType (ArgType1, ArgType2)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2))
{
	return std::function<void (ArgType1, ArgType2)>([p, mem_func](ArgType1 arg1, ArgType2 arg2) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2);
			});
}

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3>
std::function<RetType (ArgType1, ArgType2, ArgType3)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3))
{
	return std::function<void (ArgType1, ArgType2, ArgType3)>([p, mem_func](ArgType1 arg1, ArgType2 arg2, ArgType3 arg3) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2, arg3);
			});
}

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4))
{
	return std::function<void (ArgType1, ArgType2, ArgType3, ArgType4)>([p, mem_func](ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2, arg3, arg4);
			});
}

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5))
{
	return std::function<void (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5)>([p, mem_func](ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2, arg3, arg4, arg5);
			});
}

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6))
{
	return std::function<void (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6)>([p, mem_func](ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2, arg3, arg4, arg5, arg6);
			});
}

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7))
{
	return std::function<void (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7)>([p, mem_func](ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			});
}

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8))
{
	return std::function<void (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8)>([p, mem_func](ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			});
}

template <typename T, typename PtrType, typename RetType, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7, typename ArgType8, typename ArgType9>
std::function<RetType (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9)> WeakDelegate(PtrType p, RetType (T::*mem_func)(ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9))
{
	return std::function<void (ArgType1, ArgType2, ArgType3, ArgType4, ArgType5, ArgType6, ArgType7, ArgType8, ArgType9)>([p, mem_func](ArgType1 arg1, ArgType2 arg2, ArgType3 arg3, ArgType4 arg4, ArgType5 arg5, ArgType6 arg6, ArgType7 arg7, ArgType8 arg8, ArgType9 arg9) {
				std::shared_ptr<T> ptr = p.lock();

				if(ptr)
					(ptr.get()->*mem_func)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			});
}

} } }
