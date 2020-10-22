#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace net { namespace heartbeat { namespace message {

class HeartbeatResponse : public object::Object
{
public:
	STRIX_CLASS(HeartbeatResponse, object::Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.net.heartbeat.message.HeartbeatResponse")
	)
};

typedef std::shared_ptr<HeartbeatResponse> HeartbeatResponsePtr;

} } } }
