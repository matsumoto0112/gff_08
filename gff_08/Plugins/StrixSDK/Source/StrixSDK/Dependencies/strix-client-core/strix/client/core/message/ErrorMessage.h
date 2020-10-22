#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  A message communicating an error has occurred
 */
class ErrorMessage : public strix::net::object::Object
{
public:
	STRIX_CLASS(ErrorMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.ErrorMessage")
		STRIX_PROPERTY(m_error)
	)

	ErrorMessage() {}

	/**
	 *  Construct an ErrorMessage with a given error string
	 *  @param	error	The error string
	 */
	ErrorMessage(const std::string &error) {
		m_error = error;
	}

	virtual ~ErrorMessage() {}

	/**
	 *  Get the error string
	 *  @returns	The error string
	 */
	std::string &GetError() {
		return m_error;
	}

	/**
	 *  Set the error string
	 *  @param	error	The error string
	 */
	void SetError(const std::string &error) {
		m_error = error;
	}

private:
	std::string m_error;
};

} } } }
