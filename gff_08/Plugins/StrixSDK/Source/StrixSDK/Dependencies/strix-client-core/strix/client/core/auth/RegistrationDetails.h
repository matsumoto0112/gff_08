#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace auth {

/**
 *  Base class of details for registering players on the server
 */
class RegistrationDetails : public strix::net::object::Object
{
public:
	STRIX_ABSTRACT_CLASS(RegistrationDetails, strix::net::object::Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.RegistrationDetails")
	)
};

typedef std::shared_ptr<strix::client::core::auth::RegistrationDetails> RegistrationDetailsPtr;

} } } }
