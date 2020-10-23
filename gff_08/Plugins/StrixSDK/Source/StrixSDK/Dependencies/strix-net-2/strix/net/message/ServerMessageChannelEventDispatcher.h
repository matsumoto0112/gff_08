#pragma once

#include <strix/net/message/ServerMessageChannelListener.h>
#include <strix/net/message/ServerMessageChannel.h>
#include <strix/net/event/EventListenerList.h>

#include <vector>

namespace strix { namespace net { namespace message {

class ServerMessageChannelEventDispatcher
{
public:
	typedef event::ServerMessageChannelListenEvent ServerMessageChannelListenEvent;
	typedef event::ServerMessageChannelAcceptEvent ServerMessageChannelAcceptEvent;
	typedef event::ServerMessageChannelCloseEvent ServerMessageChannelCloseEvent;
	typedef event::ServerMessageChannelErrorEvent ServerMessageChannelErrorEvent;

    std::vector<ServerMessageChannelListenerPtr> GetListeners() const {
		return m_listeners.GetEventListeners();
    }

    void AddListener(const ServerMessageChannelListenerPtr &listener) {
		m_listeners.AddEventListener(listener);
    }

    void RemoveListener(const ServerMessageChannelListenerPtr &listener) {
		m_listeners.RemoveEventListener(listener);
    }

	void FireOnServerListen(const ServerMessageChannelListenEvent &ev);

	void FireOnServerAccept(const ServerMessageChannelAcceptEvent &ev);

	void FireOnServerClose(const ServerMessageChannelCloseEvent &ev);

	void FireOnServerError(const ServerMessageChannelErrorEvent &ev);

	void FireOnServerDetach();

private:
	typedef strix::net::event::EventListenerList<ServerMessageChannelListenerPtr> ServerMessageChannelListenerList;
	ServerMessageChannelListenerList m_listeners;
};

inline void ServerMessageChannelEventDispatcher::FireOnServerListen(const ServerMessageChannelListenEvent &ev)
{
	for(const ServerMessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnServerListen(ev);
	}
}

inline void ServerMessageChannelEventDispatcher::FireOnServerAccept(const ServerMessageChannelAcceptEvent &ev)
{
	for (const ServerMessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnServerAccept(ev);
	}
}

inline void ServerMessageChannelEventDispatcher::FireOnServerClose(const ServerMessageChannelCloseEvent &ev)
{
	for (const ServerMessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnServerClose(ev);
	}
}

inline void ServerMessageChannelEventDispatcher::FireOnServerError(const ServerMessageChannelErrorEvent &ev)
{
	for (const ServerMessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnServerError(ev);
	}
}

inline void ServerMessageChannelEventDispatcher::FireOnServerDetach()
{
	for (const ServerMessageChannelListenerPtr &pListener : GetListeners())
	{
		pListener->OnServerDetach();
	}

	m_listeners = ServerMessageChannelListenerList();
}

} } }

