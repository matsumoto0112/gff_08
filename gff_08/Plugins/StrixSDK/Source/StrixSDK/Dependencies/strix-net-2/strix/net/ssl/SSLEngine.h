#pragma once

#include <strix/net/ssl/SSLEngineResult.h>
#include <strix/net/ErrorCode.h>

namespace strix {namespace net {namespace buffer {
	class Buffer;
} } }

namespace strix { namespace net { namespace ssl {

class SSLEngine
{
public:
	typedef buffer::Buffer Buffer;

	SSLEngine() {}
	virtual ~SSLEngine() {}
	
	virtual bool GetUseClientMode() const = 0;

	virtual void SetUseClientMode(bool clientMode) = 0;

	virtual SSLEngineResult::HandshakeStatus GetHandshakeStatus() const = 0;

	virtual STRIX_NET_ERROR BeginHandshake() = 0;

	virtual STRIX_NET_ERROR Wrap(Buffer &buffer, const uint8_t *src, int len, SSLEngineResult &outResult) = 0;

	virtual STRIX_NET_ERROR Unwrap(Buffer &buffer, uint8_t *dst, int len, SSLEngineResult &outResult) = 0;

	virtual STRIX_NET_ERROR Shutdown() = 0;

	virtual STRIX_NET_ERROR Close() = 0;
};

} } }
