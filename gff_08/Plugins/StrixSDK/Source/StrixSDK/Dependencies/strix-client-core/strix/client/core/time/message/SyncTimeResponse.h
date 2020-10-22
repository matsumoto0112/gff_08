#pragma once

#include <strix/client/core/message/DefaultResponseMessage.h>

namespace strix { namespace client { namespace core { namespace time { namespace message {

/**
 *  Response to a sync time request. Contains time value for synchronization
 *  
 *  Strix response type - Received from server after request made
 */
class SyncTimeResponse : public strix::client::core::message::DefaultResponseMessage
{
public:
	STRIX_CLASS(SyncTimeResponse, DefaultResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.time.message.SyncTimeResponse")
		STRIX_PROPERTY(m_time)
	)

	SyncTimeResponse() {}

	virtual ~SyncTimeResponse() {}
	
	long long GetTime() const {
		return m_time;
	}

	void SetTime(long long time) {
		m_time = time;
	}

private:
	long long m_time;
};

typedef std::shared_ptr<SyncTimeResponse> SyncTimeResponsePtr;

} } } } }