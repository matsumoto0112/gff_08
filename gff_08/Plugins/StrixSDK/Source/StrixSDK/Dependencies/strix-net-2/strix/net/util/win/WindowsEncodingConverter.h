#pragma once

#include <strix/net/util/EncodingConverter.h>

#include <string>

namespace strix { namespace net { namespace util {

class WindowsEncodingConverter : public EncodingConverter
{
public:
	WindowsEncodingConverter() {}
	virtual ~WindowsEncodingConverter() {}
	
	std::wstring NativeToWideString(const char *str, size_t len) const override;

	std::wstring Utf8ToWideString(const char *str, size_t len) const override;

	std::u16string NativeToUtf16(const char *str, size_t len) const override;

	std::string WideStringToNative(const wchar_t *str, size_t len) const override;

	std::string WideStringToUtf8(const wchar_t *str, size_t len) const override;

	std::string Utf16ToNative(const char16_t *str, size_t len) const override;

	std::string NativeToUtf8(const char *str, size_t len) const override;

	std::string Utf8ToNative(const char *str, size_t len) const override;

private:
	std::wstring ToWideString(const char *str, size_t len, unsigned int codePage) const;

	std::u16string ToUtf16(const char *str, size_t len, unsigned int codePage) const;

	std::string ToString(const wchar_t *str, size_t len, unsigned int codePage) const;
};

} } }
