#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a successful create object request. Contains the created object
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix response type - Received from server after request made
 */
class CreateResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(CreateResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.CreateResponse")
		STRIX_PROPERTY(m_model)
	)

	CreateResponse() {}
	
	CreateResponse(strix::net::object::ObjectPtr model) : m_model(std::move(model)) {}
	
	virtual ~CreateResponse() {}

	/**
	 *  Get the created object
	 *  @returns	The created object
	 */
	const strix::net::object::ObjectPtr &GetModel() const {
		return m_model;
	}

	/**
	 *  Set the created object in this response
	 *  @param	model	The object
	 */
	void SetModel(const strix::net::object::ObjectPtr &model) {
		m_model = model;
	}

private:
	strix::net::object::ObjectPtr m_model;
};

typedef std::shared_ptr<CreateResponse> CreateResponsePtr;

} } } }
