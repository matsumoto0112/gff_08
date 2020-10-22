#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/RequestClient.h>
#include <strix/client/core/session/SessionMessages.h>
#include <strix/client/core/message/FailureMessage.h>

namespace strix { namespace client { namespace core { namespace session {

/**
 *  Interface for classes containing session information
 */
class SessionData {
public:

	/**
	 *  Get the UID of the session
	 *  @returns	The UID
	 */
	virtual const UIDPtr &GetUid() const = 0;

	/**
	 *  Set the UID of the session data
	 *  @param	uid	The UID
	 */
	virtual void SetUid(const UIDPtr &uid) = 0;

};

class DefaultSessionData : public SessionData
{
public:
	DefaultSessionData() {}

	~DefaultSessionData() {}

	/**
	 *  Get the UID of the session
	 *  @returns	The UID
	 */
	const UIDPtr &GetUid() const override {
		return m_uid;
	}

	/**
	 *  Set the UID of the session data
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) override {
		m_uid = uid;
	}

private:
	UIDPtr m_uid;

};

/**
 *  Client controller for session authentication actions
 */
class SessionClient : public strix::client::core::RequestClient
{
public:
	SessionClient() : m_sessionData(std::make_shared<DefaultSessionData>()) {}

	SessionClient(std::shared_ptr<SessionData> sessionData) : m_sessionData(sessionData) {}

	virtual ~SessionClient() {}

	/**
	 *  Challenge the server with a SessionChallengeMessage to authenticate. Calls OnChallengeResponse or OnChallengeFailed when the response is received
	 *  @param	message	The challenge message
	 *  @param	handler	The additional handler to call on a successful response from the server
	 *  @param	failureHandler	The additional handler to call on an unsuccessful response from the server
	 *  @param	config	Additional parameters for the request
	 */
	void Challenge(message::SessionChallengeMessagePtr message, request::RequestResultHandlerT<message::SessionChallengeResponse> handler, request::RequestFailureHandler failureHandler, request::RequestConfigPtr config = nullptr);

	/**
	 *  Restore an existing session with a token. Calls OnRestoreSessionResponse or OnRestoreSessionFailed when the response is received
	 *  @param	message	The restore session message containing the token
	 *  @param	handler	The additional handler to call on a successful response from the server
	 *  @param	failureHandler	The additional handler to call on a failure response from the server
	 *  @param	config	Addtional parameters for the request
	 */
	void RestoreSession(message::RestoreSessionMessagePtr message, request::RequestResultHandlerT<message::RestoreSessionResponse> handler, request::RequestFailureHandler failureHandler, request::RequestConfigPtr config = nullptr);

	/**
	 *  Called on a successful challenge response
	 *  @param	result	The challenge result information
	 */
	virtual void OnChallengeResponse(core::request::RequestResult<message::SessionChallengeResponsePtr> result) {}

	/**
	 *  Called on a failed challenge response
	 *  @param	result	The challenge result information
	 */
	virtual void OnChallengeFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called on a restored session response. Sets the session data's UID to the received UID
	 *  @param	result	The restored session result information
	 */
	virtual void OnRestoreSessionResponse(core::request::RequestResult<message::RestoreSessionResponsePtr> result)
	{
		m_sessionData->SetUid(result.m_result->GetUid());
	}

	/**
	 *  Called on a restored session failure response
	 *  @param	result	The restored session result information
	 */
	virtual void OnRestoreSessionFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

protected:

	/**
	 *  Set the session data UID to null
	 */
	virtual void ResetData()
	{
		m_sessionData->SetUid(nullptr);
	}

	std::shared_ptr<SessionData> m_sessionData;
};

typedef std::shared_ptr<SessionClient> SessionClientPtr;

} } } }