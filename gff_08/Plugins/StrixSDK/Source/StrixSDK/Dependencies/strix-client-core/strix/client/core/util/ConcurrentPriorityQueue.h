#pragma once

#include <queue>
#include <mutex>
#include <functional>

namespace strix { namespace client { namespace core { namespace util {

/**
 *  A thread-safe priority queue
 */
template <typename T>
class ConcurrentPriorityQueue : std::priority_queue<T, std::vector<T>, std::function<bool(T, T)> > {
public:
	typedef std::priority_queue<T, std::vector<T>, std::function<bool(T, T)> > SuperType;

	/**
	 *  Construct a priority queue
	 *  
	 *  @param  comparator	Function to determine priority in the queue
	 */
	ConcurrentPriorityQueue(const std::function<bool(T, T)> &comparator) : SuperType(comparator) { }

	/**
	 *  Enqueue an item onto the priority queue
	 *  
	 *  @param  item    The item to add
	 */
	void Enqueue(const T& item)
	{
		std::lock_guard<std::mutex> lock(m_writeMutex);
		SuperType::push(item);
	}

	/**
	 *  Dequeue from the head of the queue
	 *  
	 *  @returns	The head of the queue
	 */
	T Dequeue()
	{
		std::lock_guard<std::mutex> lock(m_writeMutex);

		if (SuperType::empty())
		{
			return nullptr;
		}

		T head = SuperType::top();
		SuperType::pop();

		return head;
	}

	/**
	 *  Get the head of the queue without removing it from the queue
	 *  
	 *  @returns	The head of the queue
	 */
	T Peek()
	{
		std::lock_guard<std::mutex> lock(m_readMutex);

		if (SuperType::empty())
		{
			return nullptr;
		}

		return SuperType::top();
	}

	/**
	 *  Removes all elements matching the predicate
	 *  
	 *  @param  unaryEquivPredicate	The predicate to match against
	 *  @returns	True if removed a number of elements, else False
	 */
	bool Remove(std::function<bool(T)> unaryEquivPredicate)
	{
		std::lock_guard<std::mutex> lockW(m_writeMutex);
		std::lock_guard<std::mutex> lockR(m_readMutex);

		std::vector<T> queueContainer = SuperType::c;

		size_t prevSize = queueContainer.size();
		queueContainer.erase(std::remove_if(queueContainer.begin(), queueContainer.end(), unaryEquivPredicate), queueContainer.end());
		return queueContainer.size() != prevSize;
	}

	/**
	 *  Checks if the queue is empty
	 *  
	 *  @returns	True if the queue is empty, else False
	 */
	bool Empty()
	{
		std::lock_guard<std::mutex> lock(m_readMutex);

		return SuperType::empty();
	}

private:
	std::mutex m_readMutex;
	std::mutex m_writeMutex;
};

} } } }
