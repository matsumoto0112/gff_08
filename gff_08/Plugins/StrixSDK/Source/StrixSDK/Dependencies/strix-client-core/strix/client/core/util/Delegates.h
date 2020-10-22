#pragma once

#include <map>
#include <memory>
#include <functional>

namespace strix { namespace client { namespace core { namespace util {


/**
 *  Utility class for binding methods to objects
 */
class MethodBinding
{
public:
	/**
	 *  Returns a function bound to a copy of the given object
	 *  
	 *  @param  obj	The object to bind to
	 *  @param  method  The method to bind
	 *  @returns	A bound function
	 */
	template<class TObj, typename TRet, typename ...TArgs>
	static std::function<TRet(TArgs...)> BindCopy(TObj obj, TRet(TObj::*method)(TArgs...))
	{
		auto func = std::mem_fn(method);
		return [func, obj](TArgs... args) mutable {return func(obj, args...);};
	}

	/**
	 *  Returns a function bound to the given object. Holds a shared_ptr to the object
	 *
	 *  @param  obj	The object to bind to
	 *  @param  method  The method to bind
	 *  @returns	A bound function
	 */
	template<class TObj, typename TRet, typename ...TArgs>
	static std::function<TRet(TArgs...)> BindShared(std::shared_ptr<TObj> obj, TRet(TObj::*method)(TArgs...))
	{
		auto func = std::mem_fn(method);
		return [func, obj](TArgs... args) {return func(obj.get(), args...);};
	}

	/**
	 *  Returns a function bound to the given object. Holds a weak_ptr to the object
	 *
	 *  @param  obj	The object to bind to
	 *  @param  method  The method to bind
	 *  @returns	A bound function
	 */
	template<class TObj, typename TRet, typename ...TArgs>
	static std::function<TRet(TArgs...)> BindWeak(std::shared_ptr<TObj> obj, TRet(TObj::*method)(TArgs...))
	{
		return BindWeak(static_cast<std::weak_ptr<TObj>>(obj), method);
	}


	/**
	 *  Returns a function bound to the given object. Holds a weak_ptr to the object
	 *
	 *  @param  obj	The object to bind to
	 *  @param  method  The method to bind
	 *  @returns	A bound function
	 */
	template<class TObj, typename TRet, typename ...TArgs>
	static std::function<TRet(TArgs...)> BindWeak(std::weak_ptr<TObj> obj, TRet(TObj::*method)(TArgs...))
	{
		auto func = std::mem_fn(method);
		return [func, obj](TArgs... args)
		{
			if (std::shared_ptr<TObj> lock = obj.lock()) {
				return func(lock.get(), args...);
			}
		};
	}

	/**
	 *  Returns a function bound to the given pointer
	 *
	 *  @param  obj	The object pointer to bind to
	 *  @param  method  The method to bind
	 *  @returns	A bound function
	 */
	template<class TObj, typename TRet, typename ...TArgs>
	static std::function<TRet(TArgs...)> BindRaw(TObj *obj, TRet(TObj::*method)(TArgs...))
	{
		auto func = std::mem_fn(method);
		return [func, obj](TArgs... args) {return func(obj, args...);};
	}
};

/**
 *  A list of delegate functions that can be called
 */
template <typename ...TArgs>
class DelegateList {
public:
	typedef size_t Handle;
	typedef std::function<void(TArgs...)> Handler;

	DelegateList() : m_needSwap(false), m_indexSequence(1), m_delegates(), m_nextDelegates() {}

	virtual ~DelegateList() = default;

	/**
	 *  Adds a new delegate function to the list. If a new function is added after a Call,
	 *  then all handles before that call are removed
	 *  
	 *  @param  handler The handler to add
	 *  @returns	A handle to the handler in the list
	 */
	virtual Handle Add(Handler handler)
	{
		Handle handle;
		do
		{
			handle = m_indexSequence++;
		} while (m_nextDelegates.find(handle) != m_nextDelegates.end());

		m_nextDelegates[handle] = handler;
		m_needSwap = true;
		return handle;
	}

	/**
	 *  Removes a handler from the list. If a function is removed after a Call,
	 *  then all handles before that call are removed
	 *  
	 *  @param  handle  The handle for the handler to remove
	 */
	virtual void Remove(const Handle &handle)
	{
		m_nextDelegates.erase(handle);
		m_needSwap = true;
	}

	/**
	 *  Calls all active delegates. If any delegates have been added after the previous call, 
	 *  only those delegates will be called. Otherwise, the current set of delegates will be called
	 *  
	 *  @param  args    The arguments for the calls
	 */
	virtual void Call(TArgs... args)
	{
		if (m_needSwap)
		{
			m_delegates = m_nextDelegates;
			m_needSwap = false;
		}

		for (auto handler : m_delegates)
		{
			handler.second(args...);
		}
	}

	/**
	 *  Calls all active delegates. If any delegates have been added after the previous call,
	 *  only those delegates will be called. Otherwise, the current set of delegates will be called
	 *
	 *  @param  args    The arguments for the calls
	 */
	void operator()(TArgs... args)
	{
		Call(args...);
	}

private:
	bool m_needSwap;
	size_t m_indexSequence;
	std::map<Handle, Handler> m_delegates;
	std::map<Handle, Handler> m_nextDelegates;
};

} } } }
