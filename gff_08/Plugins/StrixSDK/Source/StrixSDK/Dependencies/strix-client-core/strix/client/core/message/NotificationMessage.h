#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base class for notification messages
 *  
 *  Strix notification type - Received when another player performed some action
 */
class NotificationMessage
{
public:
	STRIX_BASE_ABSTRACT_CLASS(NotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.NotificationMessage")
	)

protected:
	NotificationMessage() {}
};

} } } }
