#pragma once

#include <strix/net/System.h>
#include <strix/net/socket/Address.h>

#ifdef WIN32
typedef SSIZE_T ssize_t;
#endif

namespace strix { namespace net { namespace buffer {
	struct RawBuffer;
} } }

namespace strix { namespace net { namespace socket {

class Socket
{
public:
	enum class ShutDownType
	{
		Read		= 0,
		Write		= 1,
		ReadWrite	= 2,
	};

	typedef strix::net::socket::Descriptor Descriptor;
	
	Socket();
	virtual ~Socket(void);

	Descriptor GetDescriptor () const;

	bool Init(Family af, Type type, Protocol protocol);

	bool Init(Descriptor sd);

	bool SetReuseAddr(bool bReuse);

	bool IsNonBlock() const;

	bool SetNonBlock(bool bNonBlock);

	bool SetNoDelay(bool bNoDelay);

	bool Connect(SockAddr *name, size_t namelen);

	bool Bind(const SockAddr *name, size_t namelen);

	bool Listen(int backlog);

	bool Shutdown(ShutDownType shutDownType);

	bool Close();

	ssize_t Read(buffer::RawBuffer *buffers, int numBuffers);

	ssize_t ReadFrom(buffer::RawBuffer *buffers, int numBuffers, SockAddr *srcAddress, socklen_t *srcAddressLen);

	ssize_t Write(buffer::RawBuffer *buffers, int numBuffers, SockAddr *destAddress, socklen_t destAddressLen);

	bool GetPeerAddress(Address &address) const;

	bool GetLocalAddress(Address &address) const;

	static int GetLastError();

	static bool IsWouldBlock(int err);

private:
	Descriptor m_socket;
	bool m_bNonBlock;
};

} } }
