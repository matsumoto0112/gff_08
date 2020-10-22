#pragma once

#include <strix/client/ingame/network/node/NodeAuthContextFactory.h>

#include <string>

namespace strix { namespace client { namespace core { namespace http {
class HttpClient;
typedef std::shared_ptr<HttpClient> HttpClientPtr;
} } } } 

namespace strix { namespace client { namespace ingame { namespace auth {
class SessionRestoreHandler;
typedef std::shared_ptr<SessionRestoreHandler> SessionRestoreHandlerPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace network { namespace node {

/**
 *  Factory that produces authentication contexts for HTTP server connections
 */
class HttpSessionNodeAuthContextFactory : public NodeAuthContextFactory
{
public:
	HttpSessionNodeAuthContextFactory();

	/**
	 *  Construct a new factory with a given HTTP client
	 *  @param	httpClient	The HTTP client
	 */
	HttpSessionNodeAuthContextFactory(core::http::HttpClientPtr httpClient);

	/**
	 *  Construct a new factory with a given HTTP client and access token
	 *  @param	authorizationAccessToken	The access token to use
	 *  @param	httpClient	The HTTP client
	 */
	HttpSessionNodeAuthContextFactory(std::string authorizationAccessToken, core::http::HttpClientPtr httpClient);

	/**
	 *  Construct a new AuthContext for the given node. The node must have an authUrl property to construct the auth context
	 *  @param	node	The node
	 *  @returns	A new AuthContext
	 */
	auth::AuthContextPtr BuildAuthContext(match::node::model::CustomizableMatchServerNodePtr node) override;

	/**
	 *  Get the authorization access token to use to build the contexts
	 *  @returns	The token
	 */
	const std::string &GetAuthorizationAccessToken() const;

	/**
	 *  Set the authorization access token to use to build the contexts
	 *  @param	authorizationAccessToken	The token
	 */
	void SetAuthorizationAccessToken(std::string authorizationAccessToken);

	/**
	 *  Get the HTTP client to use to build the contexts
	 *  @returns	The HTTP client
	 */
	core::http::HttpClientPtr GetHttpClient() const;
	
	/**
	 *  Set the HTTP client to use to build the contexts
	 *  @param	httpClient	The HTTP client
	 */
	void SetHttpClient(core::http::HttpClientPtr httpClient);

	/**
	 *  Get the session restore handler to use to build the contexts
	 *  @returns	The session restore handler
	 */
	auth::SessionRestoreHandlerPtr GetSessionRestoreHandler() const;

	/**
	 *  Set the session restore handler to use to build the contexts
	 *  @param	sessionRestoreHandler	The session restore handler
	 */
	void SetSessionRestoreHandler(auth::SessionRestoreHandlerPtr sessionRestoreHandler);

private:
	std::string m_authorizationAccessToken;
	core::http::HttpClientPtr m_httpClient;
	auth::SessionRestoreHandlerPtr m_sessionRestoreHandler;
};
	
} } } } }
