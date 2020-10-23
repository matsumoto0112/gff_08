#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/NotificationMessage.h>

namespace strix { namespace client { namespace core { namespace message {

class DefaultNotificationMessage : public strix::net::object::Object, public NotificationMessage
{
public:
	STRIX_CLASS(DefaultNotificationMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DefaultNotificationMessage")
		STRIX_CLASS_SUPER(NotificationMessage)
	)

protected:
	DefaultNotificationMessage() {}
};

} } } }
