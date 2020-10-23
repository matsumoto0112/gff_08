#pragma once

#include <strix/client/core/auth/RegistrationDetails.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultRequestMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  Requests the registration of a player with the stored Registration Details
 *  
 *  Strix message type - Requests sent to the server
 */
class RegisterMessage : public strix::client::core::message::DefaultRequestMessage
{
public:
	STRIX_CLASS(RegisterMessage, DefaultRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.RegisterMessage")
		STRIX_PROPERTY(m_registrationDetails)
	)
	
	typedef std::shared_ptr<strix::client::core::auth::RegistrationDetails> RegistrationDetailsPtr;

	RegisterMessage() {}

	virtual ~RegisterMessage() {}

	/**
	 *  Get the RegistrationDetails contained in this message
	 *  @returns	The registration details
	 */
	const RegistrationDetailsPtr &GetRegistrationDetails() const {
		return m_registrationDetails;
	}

	/**
	 *  Set registration details in this message
	 *  @param	registrationDetails	The registration details
	 */
	void SetRegistrationDetails(const RegistrationDetailsPtr &registrationDetails) {
		m_registrationDetails = registrationDetails;
	}

private:
	RegistrationDetailsPtr m_registrationDetails;
};

typedef std::shared_ptr<RegisterMessage> RegisterMessagePtr;

} } } } }

