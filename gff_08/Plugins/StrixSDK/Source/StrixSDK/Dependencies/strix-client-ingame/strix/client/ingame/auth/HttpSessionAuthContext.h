#pragma once
#include <strix/client/ingame/auth/AuthContext.h>

namespace strix { namespace client { namespace core { namespace http {
class HttpClient;
typedef std::shared_ptr<HttpClient> HttpClientPtr;
} } } } 

namespace strix { namespace client { namespace ingame { namespace auth {
class SessionRestoreHandler;
typedef std::shared_ptr<SessionRestoreHandler> SessionRestoreHandlerPtr;
} } } } 

namespace strix { namespace client { namespace ingame { namespace auth {

/**
 *  Auth Context for HTTP session authentication
 */
class HttpSessionAuthContext : public auth::AuthContext
{
public:

	/**
	 *  Construct an HttpSessionAuthContext with the given http client
	 *  @param	httpClient	The HTTP client to use
	 */
	HttpSessionAuthContext(core::http::HttpClientPtr httpClient);

	/**
	 *  Construct an HttpSessionAuthContext with the given http client and authentication information
	 *  @param	authorizationAccessToken	The access token to use for authentication
	 *  @param	authUrl	The authentication url to use
	 *  @param	httpClient	The HTTP client to use
	 */
	HttpSessionAuthContext(std::string authorizationAccessToken, std::string authUrl, core::http::HttpClientPtr httpClient);

	/**
	 *  Get the access token
	 *  @returns	The access token as a string
	 */
	std::string GetAuthorizationAccessToken() const;

	/**
	 *  Set the authorization access token
	 *  @param	authorizationAccessToken	The token as a string
	 */
	void SetAuthorizationAccessToken(std::string authorizationAccessToken);

	/**
	 *  Get the authentication URL
	 *  @returns	The URL
	 */
	std::string GetAuthUrl() const;

	/**
	 *  Set the authentication URL
	 *  @param	authUrl	The authentication url
	 */
	void SetAuthUrl(std::string authUrl);

	/**
	 *  Get the HTTP client to use for authentication
	 *  @returns	The HTTP client
	 */
	core::http::HttpClientPtr GetHttpClient() const;

	/**
	 *  Set the HTTP client to use for authentication
	 *  @param	httpClient	The HTTP client
	 */
	void SetHttpClient(core::http::HttpClientPtr httpClient);

	/**
	 *  Get the session restore handler to use
	 *  @returns	The session restore handler
	 */
	auth::SessionRestoreHandlerPtr GetSessionRestoreHandler() const;

	/**
	 *  Set the session restore handler to use
	 *  @param	sessionRestoreHandler	The session restore handler
	 */
	void SetSessionRestoreHandler(auth::SessionRestoreHandlerPtr sessionRestoreHandler);

	/**
	 *  Perform an HTTP authentication attempt with the HTTP client. Requires the session restore handler, token, client, and url be set
	 *  @param	connection	The server connection
	 *  @param	success	The success handler
	 *  @param	failure	The failure handler. A function that takes an error code and category
	 */
	void PerformAuth(network::ServerConnectionPtr connection, Notifier success, ErrorCodeNotifier failure) override;

	/**
	 *  Return if a message is an Auth message
	 *  @param	connection	A server connection
	 *  @param	msg	The message to check
	 *  @returns	True if the message is an authentication message for this context
	 */
	bool IsAuthMessage(network::ServerConnectionPtr connection, net::object::ObjectPtr msg) override;

private:
	std::string m_authUrl;
	std::string m_authorizationAccessToken;
	core::http::HttpClientPtr m_httpClient;
	auth::SessionRestoreHandlerPtr m_sessionRestoreHandler;
};


} } } }
