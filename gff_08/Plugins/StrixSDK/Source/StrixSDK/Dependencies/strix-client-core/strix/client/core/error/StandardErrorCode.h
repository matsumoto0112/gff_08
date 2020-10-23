#pragma once

namespace strix { namespace client { namespace core { namespace error {

enum StandardErrorCode: int {
    _MinValue = 0,

    UnknownError = 0,
    InternalError = 1,
    PermissionDenied = 2,
    LockFailed = 3,
    LockTimeout = 4,
    InstantiationFailed = 5,
    NoSuchProperty = 6,
    InvalidPropertySetting = 7,
    IncorrectMessageType = 8,
    RequestTimeout = 9,
    ModelNotFound = 10,
    ConnectionError = 11,

    _MaxValue = 12
};

} } } }
