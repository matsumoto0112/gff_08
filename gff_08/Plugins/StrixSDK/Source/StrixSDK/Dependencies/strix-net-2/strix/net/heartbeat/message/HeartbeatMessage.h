#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace net { namespace heartbeat { namespace message {

class HeartbeatMessage : public object::Object
{
public:
	STRIX_CLASS(HeartbeatMessage, object::Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.net.heartbeat.message.HeartbeatMessage")
	)
};

typedef std::shared_ptr<HeartbeatMessage> HeartbeatMessagePtr;

} } } }
