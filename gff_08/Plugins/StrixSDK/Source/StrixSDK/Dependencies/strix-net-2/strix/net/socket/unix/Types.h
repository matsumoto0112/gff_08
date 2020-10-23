#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

namespace strix { namespace net { namespace socket {

typedef int Descriptor;
typedef int Family;
typedef int Type;
typedef int Protocol;
typedef int AddrInfoFlag;
typedef addrinfo AddrInfo;
typedef sockaddr SockAddr;
typedef sockaddr_in SockAddrIn;
typedef sockaddr_in6 SockAddrIn6;
typedef int Level;
typedef int Option;
typedef socklen_t SockLenT;
typedef fd_set FdSet;
typedef timeval TimeVal;

} } }
