#pragma once

namespace strix { namespace client { namespace core { namespace crypt {

class Crypt
{
public:
    static const int SHA256_DIGEST_LENGTH = 32;
    static const int SHA512_DIGEST_LENGTH = 64;

	/**
	 * Calculate Sha256 hash
	 * @param data          The input data
	 * @param datalength    The length of the input data
	 * @param digest        The output array for storing digest. This must be longer or equal length to SHA256_DIGEST_LENGTH
	 * @return returns digest if success or NULL if an error occurred.
	 */
    static unsigned char *Sha256(const unsigned char *data, size_t dataLength, unsigned char *digest);

	/**
	 * Calculate Sha512 hash
	 * @param data          The input data
	 * @param datalength    The length of the input data
	 * @param digest        The output array for storing digest. This must be longer or equal length to SHA512_DIGEST_LENGTH
	 * @return returns digest if success or NULL if an error occurred.
	 */
    static unsigned char *Sha512(const unsigned char *data, size_t dataLength, unsigned char *digest);

	/**
	 * Calculate HMAC with Sha256
	 * @param key          The secret key 
	 * @param keylength    The length of the secret key
	 * @param in           The data to HMAC
	 * @param inlength     The length of the data to HMAC
	 * @param out          [out] Destination of the authentication tag
	 * @param outlenength  [in/out] Max size and resulting size of authentication tag
	 * @return returns HMAC authentication tag if success or NULL if an error occurred.
	 */
    static unsigned char *HmacSha256(const unsigned char *key, size_t keyLength, const unsigned char *in, size_t inLength, unsigned char *out, size_t &outLength);

	/**
	 *  Convert string to Base64URL string
	 *  @param	bytes	The input bytes
	 *  @param	bytesLength	The length of bytes
	 *  @returns	The string in it's Base64URL representation
	 */
    static std::string Base64UrlEncode(const unsigned char *bytes, size_t bytesLength);
};

} } } }
