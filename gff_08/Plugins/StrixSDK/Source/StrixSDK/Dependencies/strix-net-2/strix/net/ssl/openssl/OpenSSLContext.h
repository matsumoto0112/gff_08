#pragma once

#include <strix/net/ssl/SSLContext.h>
#include <strix/net/ssl/openssl/OpenSSLTypes.h>

#include <string>
#include <memory>

namespace strix { namespace net { namespace ssl { namespace openssl {

class OpenSSLContext : public SSLContext, public std::enable_shared_from_this<OpenSSLContext>
{
public:
	virtual ~OpenSSLContext();

	static std::shared_ptr<OpenSSLContext> Create() {
		return std::shared_ptr<OpenSSLContext>(new OpenSSLContext());
	}

	static std::shared_ptr<OpenSSLContext> Create(SSL_CTX *ctx) {
		return std::shared_ptr<OpenSSLContext>(new OpenSSLContext(ctx));
	}

	std::unique_ptr<SSLEngine> CreateSSLEngine() override;

	bool LoadCertificateChain(const std::string &certChainFile) override;

	bool LoadPrivateKey(const std::string &privateKeyFile, std::string password, FileType fileType = FileType::PEM) override;

	VerifyMode GetVerifyMode() const override;

	void SetVerifyMode(VerifyMode verifyMode) override;

	int GetVerifyDepth() const override;

	void SetVerifyDepth(int depth) override;

	bool LoadVerifyLocations(const std::string &caFile, const std::string &caPath) override;

	SSL_CTX *GetContext() {
		return m_ctx;
	}

private:
	OpenSSLContext();

	OpenSSLContext(SSL_CTX *ctx);

	SSL_CTX *m_ctx;
};

} } } }
