#pragma once

#include <string>
#include <memory>

namespace strix { namespace net { namespace ssl {

class SSLContext;
class SSLEngine;

class SSLContext
{
public:
	typedef int VerifyMode;
	const VerifyMode VerifyMode_None                = 0x00;
	const VerifyMode VerifyMode_Peer                = 0x01;
	const VerifyMode VerifyMode_FailIfNoPeerCert    = 0x02;
	const VerifyMode VerifyMode_ClientOnce          = 0x04;

	enum class FileType
	{
		PEM = 1,
		DER = 2,
	};

	virtual ~SSLContext();

	static std::shared_ptr<SSLContext> Create();

	virtual std::unique_ptr<SSLEngine> CreateSSLEngine() = 0;

	virtual bool LoadCertificateChain(const std::string &certChainFile) = 0;

	virtual bool LoadPrivateKey(const std::string &privateKeyFile, std::string password, FileType fileType = FileType::PEM) = 0;

	virtual VerifyMode GetVerifyMode() const = 0;

	virtual void SetVerifyMode(VerifyMode verifyMode) = 0;

	virtual int GetVerifyDepth() const = 0;

	virtual void SetVerifyDepth(int depth) = 0;

	virtual bool LoadVerifyLocations(const std::string &caFile, const std::string &caPath) = 0;

protected:
	SSLContext();
};

} } }
