#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace auth {

/**
 *  Base class of Credential types
 */
class Credentials : public strix::net::object::Object
{
public:
	STRIX_ABSTRACT_CLASS(Credentials, strix::net::object::Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.Credentials")
	)
};

typedef std::shared_ptr<strix::client::core::auth::Credentials> CredentialsPtr;

} } } }
