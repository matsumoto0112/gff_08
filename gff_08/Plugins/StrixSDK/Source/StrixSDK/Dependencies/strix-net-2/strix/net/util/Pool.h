#pragma once

#include <strix/net/util/SynchronizedQueue.h>

#include <memory>

namespace strix { namespace net { namespace util {
	
template<class _PoolType>
class PoolDeleter;

template<class T, class Allocator = std::allocator<T> >
class Pool
{
public:
	typedef T ElementType;
	typedef Allocator AllocatorType;
	typedef PoolDeleter<Pool<T, Allocator> > DeleterType;

	Pool()
	{
		Init(16);
	}

	Pool(int initialSize)
	{
		Init(initialSize);
	}

	~Pool()
	{
		while(true)
		{
			T *p;
			
			if(!m_queue.Pop(p))
				break;

			m_allocator.deallocate(p);
		}
	}

	void Init(int initialSize)
	{
		for(int i=0; i<initialSize; i++)
			m_queue.Push(m_allocator.allocate());
	}

	T *Allocate()
	{
		T *p;
		
		if(m_queue.Pop(p))
			return p;
		
		return m_allocator.allocate();
	}

	void Free(T* p)
	{
		if(p)
			m_queue.Push(p);
	}

	Allocator &GetAllocator()
	{
		return m_allocator;
	}

private:
	Allocator m_allocator;
	SynchronizedQueue<T*> m_queue;
};

template<class _PoolType>
class PoolDeleter
{
public:
	typedef _PoolType PoolType;

	PoolDeleter(PoolType &pool) : m_pool(pool) {}

	void operator()(typename PoolType::ElementType *p) const {
		m_pool.Free(p);
	}

private:
	PoolType &m_pool;
};

} } }
