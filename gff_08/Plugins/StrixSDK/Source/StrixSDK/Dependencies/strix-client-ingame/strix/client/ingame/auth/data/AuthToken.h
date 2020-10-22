#pragma once

#include <string>

namespace strix { namespace client { namespace ingame { namespace auth { namespace data {

/**
 *  A model of an authentication token with an id, password and nonce value
 */
class AuthToken {
public:
	// ToDo: use proper JSON lib/parsing
	/**
	 *  Set a property of a an auth token. Possible keys are "session_id", "session_password", and "nonce"
	 *  @param	key	The key value of the property
	 *  @param	value	The value to set
	 *  @param	authToken	The token to set the property on
	 *  @returns	True if the property was successfully set, or False if the key value was incorrect
	 */
	static bool SetPropertyInAuthToken(std::string key, std::string value, AuthToken* authToken)
	{
		if (key == "session_id")
		{
			authToken->m_sessionId = value;
			return true;
		}
		if (key == "session_password")
		{
			authToken->m_sessionPassword = value;
			return true;
		}
		if (key == "nonce")
		{
			authToken->m_nonce = value;
			return true;
		}

		return false;
	}

	/**
	 *  Set properties on a token by parsing a JSON object. The properties should be in the form
	 *  {
	 *  	"session_id": "id",
	 *  	"session_password": "password",
	 *  	"nonce": "owaifdhwa3r3refd"
	 *  }
	 *  @param	json	The json string
	 *  @param	token	The token to set the properties on
	 *  @returns	True if the properties were set correctly
	 */
	static bool ParseAuthTokenJson(std::string json, AuthToken* token)
	{
		int parsed = 0;

		size_t tokenBegin = -1, tokenEnd = -1;
		std::string key, value;
		bool wasKeyRead = false;

		while (parsed < 3) {
			tokenBegin = json.find('"', tokenEnd + 1);
			if (tokenBegin == std::string::npos)
				return false;
			else
				++tokenBegin;

			tokenEnd = json.find('"', tokenBegin);
			if (tokenEnd == std::string::npos)
				return false;

			if (!wasKeyRead)
			{
				key = json.substr(tokenBegin, (tokenEnd - tokenBegin));
				wasKeyRead = true;
			}
			else
			{
				value = json.substr(tokenBegin, (tokenEnd - tokenBegin));
				wasKeyRead = false;

				if (SetPropertyInAuthToken(key, value, token))
					++parsed;
			}
		}

		return true;
	}

	std::string m_sessionId;
	std::string m_sessionPassword;
	std::string m_nonce;
};

} } } } }
