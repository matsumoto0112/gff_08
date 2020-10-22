#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/auth/Credentials.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace auth {

/**
 *  UID based credentials
 */
class UIDCredentials : public Credentials
{
public:
	STRIX_CLASS(UIDCredentials, Credentials)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.UIDCredentials")
		STRIX_PROPERTY(m_uid)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;
	
	UIDCredentials() {}

	virtual ~UIDCredentials() {}
	
	/**
	 *  Get the UID
	 *  @returns	The UID
	 */
	const strix::client::core::UIDPtr &GetUid() const {
	    return m_uid;
	}

	/**
	 *  Set the UID in these credentials
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) {
	    m_uid = uid;
	}
	
private:
	UIDPtr m_uid;
};

} } } }
