#pragma once

#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a failed search request
 * 
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix response type - Received from server after request made
 */
class SearchFailedResponse : public ParameterFailureMessage
{
public:
	STRIX_CLASS(SearchFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SearchFailedResponse")
	)

	SearchFailedResponse() {}
	
	virtual ~SearchFailedResponse() {}
};

} } } }
