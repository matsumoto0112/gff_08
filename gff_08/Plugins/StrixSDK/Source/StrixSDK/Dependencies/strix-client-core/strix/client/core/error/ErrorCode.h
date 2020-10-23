#pragma once

#include "ErrorFormatter.h"

#include <vector>
#include <memory>

namespace strix { namespace client { namespace core { namespace error {

/**
 *  An error code with formatters for human readable names and descriptions
 */
class ErrorCode {
public:
	/**
	 *  Add an error code formatter
	 */
	static void AddFormatter(std::shared_ptr<ErrorFormatter> formatter);

	/**
	 *  Get the name of the error code provided. Returns the result from the first formatter capable of parsing the code
	 *  @param	code	The error code
	 *  @returns	The name of the code
	 */
	static const char *GetErrorCodeName(int code);

	/**
	 *  Get the description of the error code provided. Returns the result from the first formatter capable of parsing the code
	 *  @param	code	The error code
	 *  @returns	The description of the code
	 */
	static std::string GetErrorDescription(int code);

private:
	static std::vector<std::shared_ptr<ErrorFormatter>> m_formatters;
};

} } } }
