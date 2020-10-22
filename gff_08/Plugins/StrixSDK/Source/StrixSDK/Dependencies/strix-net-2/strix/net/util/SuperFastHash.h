#pragma once

namespace strix { namespace net { namespace util {

class SuperFastHash
{
public:
    static int Fast(const char* pData, size_t iLen);
    static int Fast(const wchar_t* wszStr);
//    static int Fast(const char16* szStr);
    static int Fast(const char* szStr);
};

} } }
