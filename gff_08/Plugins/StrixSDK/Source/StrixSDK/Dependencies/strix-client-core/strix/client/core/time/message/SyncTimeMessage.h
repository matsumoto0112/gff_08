#pragma once

#include <strix/client/core/message/DefaultRequestMessage.h>

namespace strix { namespace client { namespace core { namespace time { namespace message {

/**
 *  Request for a sync time response for time synchronization
 *  
 *  Strix message type - Requests sent to the server
 */
class SyncTimeMessage : public strix::client::core::message::DefaultRequestMessage
{
public:
	STRIX_CLASS(SyncTimeMessage, DefaultRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.time.message.SyncTimeMessage")
	)

  SyncTimeMessage() {}

	virtual ~SyncTimeMessage() {}

};

typedef std::shared_ptr<SyncTimeMessage> SyncTimeMessagePtr;

} } } } }

