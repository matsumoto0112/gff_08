#pragma once

#include <string>

namespace strix { namespace net { namespace util {

class EncodingConverter
{
public:
	EncodingConverter() {}
	virtual ~EncodingConverter() {}
	
	virtual std::wstring NativeToWideString(const char *str, size_t len) const = 0;

	virtual std::wstring Utf8ToWideString(const char *str, size_t len) const = 0;

	virtual std::u16string NativeToUtf16(const char *str, size_t len) const = 0;

	virtual std::string WideStringToNative(const wchar_t *str, size_t len) const = 0;

	virtual std::string WideStringToUtf8(const wchar_t *str, size_t len) const = 0;

	virtual std::string Utf16ToNative(const char16_t *str, size_t len) const = 0;

	virtual std::string NativeToUtf8(const char *str, size_t len) const = 0;

	virtual std::string Utf8ToNative(const char *str, size_t len) const = 0;
};

} } }
