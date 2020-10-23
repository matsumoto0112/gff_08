#pragma once

#include <strix/client/ingame/auth/AbstractSessionRestoreHandler.h>

namespace strix { namespace client { namespace ingame { namespace auth {

/**
 *  Implementation of session restore handler
 */
class DefaultSessionRestoreHandler : public AbstractSessionRestoreHandler
{
protected:

	/**
	 *  Calculate the c nonce value for the token
	 *  @returns	The nonce value as a string
	 */
	std::string GenerateCNonce() override;

	/**
	 *  Calculate the hash value for the token
	 *  @param	password	The user password
	 *  @param	nonce	The nonce value
	 *  @param	cnonce	The c nonce value
	 *  @returns	The hash value as a string
	 */
	std::string CalculateHash(const std::string &password, const std::string &nonce, const std::string &cnonce) override;
	
	/**
	 *  Calculate a SHA-256 hashed message authentication code from a message and key
	 *  @param	md	The message string to authenticate
	 *  @param	key	The secret key
	 *  @returns	A SHA-256 HMAC as a string
	 */
	std::vector<unsigned char> CalculateHMAC(const std::vector<unsigned char> &md, const std::vector<unsigned char> &key);
};

} } } }
