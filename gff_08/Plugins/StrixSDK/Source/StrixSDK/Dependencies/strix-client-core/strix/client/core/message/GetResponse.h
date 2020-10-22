#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a successful get request. Contains the object requested.
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix response type - Received from server after request made
 */
class GetResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(GetResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.GetResponse")
		STRIX_PROPERTY(m_model)
	)

	GetResponse() {}
	
	GetResponse(strix::net::object::ObjectPtr &model) {
		m_model = model;
	}
	
	virtual ~GetResponse() {}

	/**
	 *  Get the object requested 
	 *  @returns	The object
	 */
	const strix::net::object::ObjectPtr &GetModel() const {
		return m_model;
	}

	/**
	 *  Set the object in this response
	 *  @param	model	The object
	 */
	void SetModel(const strix::net::object::ObjectPtr &model) {
		m_model = model;
	}

private:
	strix::net::object::ObjectPtr m_model;
};

typedef std::shared_ptr<GetResponse> GetResponsePtr;

} } } }
