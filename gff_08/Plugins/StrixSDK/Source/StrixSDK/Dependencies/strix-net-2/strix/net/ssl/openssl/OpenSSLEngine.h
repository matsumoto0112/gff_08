#pragma once

#include <strix/net/ssl/SSLEngine.h>
#include <strix/net/ssl/openssl/OpenSSLTypes.h>

#include <memory>

namespace strix { namespace net { namespace buffer {
class Buffer;
} } }

namespace strix { namespace net { namespace ssl { namespace openssl {

class OpenSSLContext;

class OpenSSLEngine : public SSLEngine
{
public:

	OpenSSLEngine(std::shared_ptr<OpenSSLContext> pContext);
	virtual ~OpenSSLEngine();

	bool GetUseClientMode() const override;

	void SetUseClientMode(bool clientMode) override;

	SSLEngineResult::HandshakeStatus GetHandshakeStatus() const override;
	
	STRIX_NET_ERROR BeginHandshake() override;

	STRIX_NET_ERROR Wrap(buffer::Buffer &buffer, const uint8_t *src, int len, SSLEngineResult &outResult) override;

	STRIX_NET_ERROR Unwrap(buffer::Buffer &buffer, uint8_t *dst, int len, SSLEngineResult &outResult) override;

	STRIX_NET_ERROR Shutdown() override;

	STRIX_NET_ERROR Close() override;
	
private:
	STRIX_NET_ERROR Handshake(SSLEngineResult &result);

	int WriteFrom(buffer::Buffer &buffer);

	int ReadTo(buffer::Buffer &buffer);

	STRIX_NET_ERROR HandleError(int errorCode);

	bool m_useClientMode;
	std::shared_ptr<OpenSSLContext> m_pContext;
	SSL *m_ssl;
	BIO *m_rbio;
	BIO *m_wbio;
};

} } } }
