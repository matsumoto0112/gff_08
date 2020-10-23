#pragma once

namespace strix { namespace client { namespace core { namespace error {

/**
 *  Categories of error types
 */
enum ErrorCategory : int {
	StrixNet,
	StrixClient,
	External
};

} } } }
