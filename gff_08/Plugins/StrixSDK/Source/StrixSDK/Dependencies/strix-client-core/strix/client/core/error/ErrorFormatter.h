#pragma once

namespace strix { namespace client { namespace core { namespace error {

/**
 *  Interface for classes that provide human readable names and descriptions of error codes
 */
class ErrorFormatter {
public:
	/**
	 *  Return the name of the code as a human readable string
	 *  @param	code	The code
	 *  @returns	The name
	 */
	virtual const char *GetErrorCodeName(int code) = 0;

	/**
	 *  Return the description of the code as a human readable string
	 *  @param	code	The code
	 *  @return	The description
	 */
	virtual std::string GetErrorDescription(int code) = 0;
};

} } } }
