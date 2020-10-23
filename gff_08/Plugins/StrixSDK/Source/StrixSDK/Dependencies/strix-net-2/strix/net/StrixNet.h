#pragma once

#include <string>
#include <vector>

namespace strix { namespace net {

class StrixNet
{
public:
	class Initializer
	{
	public:
		Initializer();
		~Initializer();
	};

	static void ProvideLicense(const std::string &licenseFilename, const std::string &password);

	static void ProvideLicense(const std::vector<uint8_t> &license, const std::string &password);

	static void ProvideLicense(const uint8_t *license, const size_t licenseSize, const std::string& password);

	static void Init();

	static void Cleanup();

private:
	StrixNet() {}
};

} }

