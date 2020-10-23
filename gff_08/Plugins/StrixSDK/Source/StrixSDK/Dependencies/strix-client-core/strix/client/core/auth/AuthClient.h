#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/RequestClient.h>
#include <strix/client/core/auth/AuthMessages.h>

namespace strix { namespace client { namespace core { namespace auth {

/**
 *  Controller class for authentication actions.
 *  Provides methods for login and registration 
 */
class AuthClient : public strix::client::core::RequestClient
{
public:
	AuthClient() {}

	virtual ~AuthClient() {}

	/**
	 *  Sends the login message given to the server. The callbacks are triggered on a create response from the server
	 *  @param	message	The login message to send
	 *  @param	handler	The callback to call on a successful response. A function that takes a RequestResult<LoginResponse> as input
	 *  @param	failureHandler	The callback to call on a failure response. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	void Login(message::LoginMessagePtr message, request::RequestResultHandlerT<message::LoginResponse> handler, request::RequestFailureHandler failureHandler, request::RequestConfigPtr config = nullptr);

	/**
	 *  Sends the register message given to the server. The callbacks are triggered on a create response from the server
	 *  @param	message	The register message to send
	 *  @param	handler	The callback to call on a successful response. A function that takes a RequestResult<RegisterResponse> as input
	 *  @param	failureHandler	The callback to call on a failure response. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	void Register(message::RegisterMessagePtr message, request::RequestResultHandlerT<message::RegisterResponse> handler, request::RequestFailureHandler failureHandler, request::RequestConfigPtr config = nullptr);

	/**
	 *  A handler for a login response. Sets the UID of this client to the UID from the response
	 *  @param	result	The login response
	 */
	virtual void OnLoginResponse(strix::client::core::request::RequestResult<message::LoginResponsePtr> result);

	/**
	 *  A handler for a failed login response. Sets the UID of this client to null
	 *  @param	result	The login failure response
	 */
	virtual void OnLoginFailed(strix::client::core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  A handler for a register response
	 *  @param	result	The register response
	 */
	virtual void OnRegisterResponse(strix::client::core::request::RequestResult<message::RegisterResponsePtr> result);

	/**
	 *  A handler for a failed register response
	 *  @param	result	The register failed response
	 */
	virtual void OnRegisterFailed(strix::client::core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Get the UID of this client
	 *  @returns	The UID
	 */
	const strix::client::core::UIDPtr &GetUid() const {
		return m_uid;
	}

	/**
	 *  Set the UID of this client
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) {
		m_uid = uid;
	}

protected:
	/**
	 *  Set the UID of this client to null
	 */
	virtual void ResetData();

private:
	strix::client::core::UIDPtr m_uid;
};

typedef std::shared_ptr<AuthClient> AuthClientPtr;

} } } }
