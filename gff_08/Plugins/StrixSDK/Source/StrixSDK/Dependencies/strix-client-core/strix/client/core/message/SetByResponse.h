#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a successful set by request
 *  
 *  Parameter message with parameter classes
 *  
 *  Can contain multiple objects of the parameter type that matched the set by filter
 *  
 *  Strix response type - Received from server after request made
 */
class SetByResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(SetByResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SetByResponse")
		STRIX_PROPERTY(m_models)
	)

	SetByResponse() {}
	
	virtual ~SetByResponse() {}

	/**
	 *  Get the object models contained in this response
	 *  @returns	A vector of Objects
	 */
	strix::net::object::ObjectVector &GetModelCollection() {
		return m_models;
	}

	/**
	 *  Set the object models in this response
	 *  @param	models	A vector of Objects
	 */
	void SetModelCollection(const strix::net::object::ObjectVector &models) {
		m_models = models;
	}

private:
	strix::net::object::ObjectVector m_models;
};

typedef std::shared_ptr<SetByResponse> SetByResponsePtr;

} } } }
