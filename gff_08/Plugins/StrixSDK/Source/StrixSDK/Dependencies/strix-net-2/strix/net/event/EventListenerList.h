#pragma once

#include <vector>
#include <algorithm>

namespace strix { namespace net { namespace event {

template <typename T>
class EventListenerList
{
public:
	typedef std::vector<T> ListType;

	EventListenerList() {}
	~EventListenerList() {}

    ListType GetEventListeners() const {
		return list;
	}

    void AddEventListener(const T &eventListener) {
		list.push_back(eventListener);
	}

    bool RemoveEventListener(const T &eventListener) {
		typename ListType::iterator it = std::remove(list.begin(), list.end(), eventListener);

		if(it == list.end())
			return false;

		list.erase(it, list.end());

		return true;
	}

private:
	ListType list;
};

} } }
