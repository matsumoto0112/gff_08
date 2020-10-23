#pragma once

#include <strix/net/message/MessageChannelListener.h>
#include <strix/net/message/MessageChannel.h>
#include <strix/net/event/EventListenerList.h>

#include <memory>

namespace strix { namespace net { namespace message {

class MessageChannelEventDispatcher
{
public:
	typedef event::MessageChannelConnectEvent MessageChannelConnectEvent;
	typedef event::MessageChannelMessageEvent MessageChannelMessageEvent;
	typedef event::MessageChannelCloseEvent MessageChannelCloseEvent;
	typedef event::MessageChannelErrorEvent MessageChannelErrorEvent;

    std::vector<MessageChannelListenerPtr> GetListeners() const {
		return m_listeners.GetEventListeners();
    }

    void AddListener(const MessageChannelListenerPtr &listener) {
		m_listeners.AddEventListener(listener);
    }

    void RemoveListener(const MessageChannelListenerPtr &listener) {
		m_listeners.RemoveEventListener(listener);
    }

	void FireOnConnect(const MessageChannelConnectEvent &ev);

	void FireOnMessage(const MessageChannelMessageEvent &ev);

	void FireOnClose(const MessageChannelCloseEvent &ev);

	void FireOnError(const MessageChannelErrorEvent &ev);

	void FireOnDetach();

private:
	typedef strix::net::event::EventListenerList<std::shared_ptr<MessageChannelListener> > MessageChannelListenerList;
	MessageChannelListenerList m_listeners;
};

inline void MessageChannelEventDispatcher::FireOnConnect(const MessageChannelConnectEvent &ev)
{
	for(const MessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnConnect(ev);
	}
}

inline void MessageChannelEventDispatcher::FireOnMessage(const MessageChannelMessageEvent &ev)
{
	for (const MessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnMessage(ev);
	}
}

inline void MessageChannelEventDispatcher::FireOnClose(const MessageChannelCloseEvent &ev)
{
	for (const MessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnClose(ev);
	}
}

inline void MessageChannelEventDispatcher::FireOnError(const MessageChannelErrorEvent &ev)
{
	for (const MessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnError(ev);
	}
}

inline void MessageChannelEventDispatcher::FireOnDetach()
{
	for (const MessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnDetach();
	}

	m_listeners = MessageChannelListenerList();
}

} } }

