#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultResponseMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  Response to a successful register request
 *  
 *  Strix response type - Received from server after request made
 */
class RegisterResponse : public strix::client::core::message::DefaultResponseMessage
{
public:
	STRIX_CLASS(RegisterResponse, DefaultResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.RegisterResponse")
		STRIX_PROPERTY(m_uid)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	RegisterResponse() {}

	virtual ~RegisterResponse() {}

	/**
	 *  Get the new UID for the player
	 *  @returns	The UID
	 */
	const UIDPtr &GetUid() const {
		return m_uid;
	}

	/**
	 *  Set the UID in this message
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) {
		m_uid = uid;
	}

private:
	UIDPtr m_uid;
};

typedef std::shared_ptr<RegisterResponse> RegisterResponsePtr;

} } } } }

