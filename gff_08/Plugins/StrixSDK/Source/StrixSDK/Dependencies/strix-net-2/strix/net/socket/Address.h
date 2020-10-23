#pragma once

#include <strix/net/System.h>
#include <strix/net/socket/Types.h>

namespace strix { namespace net { namespace socket {

class Address
{
public:
	Address();
	Address(const Address &rhs);
	~Address();

	const std::string &GetHost() const      { return m_host; }

	void SetHost(const std::string &host)   { m_host = host; }

	unsigned short GetPortNumber() const          { return m_port; }

	void SetPortNumber(unsigned short port)       { m_port = port; }

	const SockAddr *GetAddress() const      { return m_address; }

	SockAddr *GetAddress()                  { return m_address; }

	size_t GetAddressLength() const         { return m_addrLen; }

	void SetAddress(SockAddr *addr, socklen_t addrlen);

	Address &operator=(const Address &rhs);

	bool operator<(const Address& rhs) const;

private:
	std::string m_host;
	unsigned short m_port;
	SockAddr *m_address;
	size_t m_addrLen;
};

} } }
