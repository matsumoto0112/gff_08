#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultResponseMessage.h>

namespace strix { namespace client { namespace core { namespace session { namespace message {

/**
 *  Response to a successful restore session request
 *  
 *  Strix response type - Received from server after request made
 */
class RestoreSessionResponse : public strix::client::core::message::DefaultResponseMessage
{
public:
	STRIX_CLASS(RestoreSessionResponse, DefaultResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.RestoreSessionResponse")
		STRIX_PROPERTY(m_uid)
	)

	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	RestoreSessionResponse() {}

	RestoreSessionResponse(const UIDPtr &uid) : m_uid(uid) {}

	virtual ~RestoreSessionResponse() {}

	/**
	 *  Get the UID of the restored session
	 *  @returns	The UID
	 */
	const UIDPtr &GetUid() const {
		return m_uid;
	}

	/**
	 *  Set the UID information
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) {
		m_uid = uid;
	}

private:
	UIDPtr m_uid;
};

typedef std::shared_ptr<RestoreSessionResponse> RestoreSessionResponsePtr;

} } } } }
