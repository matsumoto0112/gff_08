#pragma once

#include <memory>

namespace strix { namespace net { namespace message {
	class ServerMessageChannel;
	typedef std::shared_ptr<ServerMessageChannel> ServerMessageChannelPtr;
} } }

namespace strix { namespace net { namespace message { namespace event {

class ServerMessageChannelErrorEvent
{
public:
	ServerMessageChannelErrorEvent(const ServerMessageChannelPtr &pServerMessageChannel, int errorCode)
		: m_pServerMessageChannel(pServerMessageChannel), m_errorCode(errorCode) {
    }

	const ServerMessageChannelPtr &GetServerMessageChannel() const {
        return m_pServerMessageChannel;
    }

	int GetErrorCode() const {
		return m_errorCode;
	}

private:
	const ServerMessageChannelPtr &m_pServerMessageChannel;
	int m_errorCode;
};

} } } }
