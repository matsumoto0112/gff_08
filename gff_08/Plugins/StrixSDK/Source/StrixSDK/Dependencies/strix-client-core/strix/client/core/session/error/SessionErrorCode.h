#pragma once

namespace strix { namespace client { namespace core { namespace session { namespace error {

enum SessionErrorCode: int {
    _MinValue = 0,

    InvalidSessionToken = 2000,
    SessionNotFound = 2001,

    _MaxValue = 2002
};

} } } } }
