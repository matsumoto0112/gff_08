#pragma once

#include <string>

namespace strix { namespace net { namespace channel {

enum class Protocol
{
	TCP,
	UDP
};

class ProtocolStringConverter
{
public:
	static std::string ToString(Protocol protocol)
	{
		if (protocol == Protocol::TCP)
		{
			return "TCP";
		}
		if (protocol == Protocol::UDP)
		{
			return "UDP";
		}
		return "";
	}

	static bool TryFromString(const std::string &value, Protocol &outProtocol)
	{
		if (value == "TCP")
		{
			outProtocol = Protocol::TCP;
			return true;
		}
		if (value == "UDP")
		{
			outProtocol = Protocol::UDP;
			return true;
		}
		return false;
	}

	static Protocol FromString(const std::string &value, Protocol defaultProtocol)
	{
		Protocol outProtocol;
		if (TryFromString(value, outProtocol))
		{
			return outProtocol;
		}

		return defaultProtocol;
	}
};

} } }

