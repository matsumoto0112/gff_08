#pragma once

#include <strix/client/core/message/CreateResponse.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace replica { namespace message {

/**
 *  Represents a response from the server after a replica create request
 */
class ReplicaCreateResponse : public strix::client::core::message::CreateResponse
{
public:
	STRIX_CLASS(ReplicaCreateResponse, CreateResponse)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.message.ReplicaCreateResponse")
	)

	ReplicaCreateResponse() {}

	ReplicaCreateResponse(strix::net::object::ObjectPtr model) : CreateResponse(std::move(model)) {}

	virtual ~ReplicaCreateResponse() {}

};

} } } }
