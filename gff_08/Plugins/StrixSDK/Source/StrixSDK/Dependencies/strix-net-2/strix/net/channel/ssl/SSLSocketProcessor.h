#pragma once

#include <strix/net/channel/SocketProcessor.h>

#include <memory>

namespace strix { namespace net { namespace ssl {
	class SSLContext;
} } }

namespace strix { namespace net { namespace channel {

class SSLSocketProcessor : public SocketProcessor
{
public:
	typedef strix::net::ssl::SSLContext SSLContext;

	SSLSocketProcessor() {}
	virtual ~SSLSocketProcessor() {}

	static std::unique_ptr<SSLSocketProcessor> Create();

	static std::unique_ptr<SSLSocketProcessor> Create(std::shared_ptr<SSLContext> pSSLContext);

	static std::unique_ptr<SSLSocketProcessor> Create(std::unique_ptr<SocketProcessor> pSocketProcessor);

	static std::unique_ptr<SSLSocketProcessor> Create(std::unique_ptr<SocketProcessor> pSocketProcessor, std::shared_ptr<SSLContext> pSSLContext);
};

} } }
