#pragma once

#include <queue>
#include <mutex>

namespace strix { namespace net { namespace util {
	
template <typename T>
class SynchronizedPriorityQueue
{
public:
	typedef T ElementType;

	SynchronizedPriorityQueue() {}
	~SynchronizedPriorityQueue() {}

	void Push(T v)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(v);
	}

	bool Pop(T &outValue)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (m_queue.empty())
			return false;

		T v = m_queue.top();
		m_queue.pop();

		outValue = v;

		return true;
	}

	bool IsEmpty()
	{
		return m_queue.empty();
	}

private:
	std::priority_queue<T> m_queue;
	std::mutex m_mutex;
};

} } }
