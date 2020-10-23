#pragma once

#include <string>
#include <algorithm>
#include <cctype>
#include <functional>

namespace strix { namespace client { namespace core { namespace util {

/**
 *  Utility functions for strings
 */
class StringUtil
{
public:

	/**
	 *  Trims characters from the end of the string if they match the predicate. Stops when predicate fails
	 *  
	 *  @param  value   The string to remove from
	 *  @param  predicate	The predicate to match to
	 */
	static inline void RightTrim(std::string &value, std::function<bool(char)> predicate)
	{
		value.erase(std::find_if(value.rbegin(), value.rend(), [predicate](char current) {
			return !predicate(current);
		}).base(), value.end());
	}

	/**
	 *  Trims spaces from end of string. Stops once a non space character is encountered
	 *
	 *  @param  value   The string to remove from
	 */
	static inline void RightTrimWhitespaces(std::string &value) {
		RightTrim(value, [](char current) { return std::isspace(current); });
	}

	/**
	 *  Trims the given characters from end of string. Stops once a different character is encountered
	 *
	 *  @param  value   The string to remove from
	 *  @param  character	The character to trim
	 */
	static inline void RightTrimCharacter(std::string &value, char character) {
		RightTrim(value, [character](char current) { return current == character; });
	}

	/**
	 *  Trims the given characters and any spaces from end of string. Stops once a different character is encountered
	 *
	 *  @param  value   The string to remove from
	 *  @param  character	The character to trim
	 */
	static inline void RightTrimCharacterAndWhitespaces(std::string &value, char character) {
		RightTrim(value, [character](char current) { return (current == character) || std::isspace(current); });
	}
};

} } } }
