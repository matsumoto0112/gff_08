#pragma once

#include <strix/net/socket/Types.h>

namespace strix { namespace net { namespace socket {

class SocketUtil
{
public:
	static int getAddrInfo(const char* pNodeName, const char* pServername, const AddrInfo* pHints, AddrInfo** pResult);

	static void freeAddrInfo(AddrInfo* addrInfoStorage);

	static int getSockOpt(Descriptor socket, Level level, Option optionName, void* pOutOptionValue, SockLenT* pOutOptionLength);

	static const char* inetNtop(Family family, const void* pNetworkAddress, char* addressStringBuffer, SockLenT addressStringBufferLength);

	static Descriptor accept(Descriptor socket, SockAddr* pOutAddress, SockLenT* pOutAddressLength);
	
	static int select(int numberOfDescriptors, FdSet* pReadDescriptors, FdSet* pWriteDescriptors, FdSet* pExceptDescriptors, TimeVal* pTimeout);
};

} } }
