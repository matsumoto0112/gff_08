#pragma once

namespace strix { namespace client { namespace core { namespace auth { namespace error {

enum AuthErrorCode: int {
    _MinValue = 0,

    DuplicateConnectionForSameUid = 1000,
    CouldNotCalculateHash = 1001,
    InvalidCredentialsType = 1002,
    InvalidCredentialsValue = 1003,
    WrongCredentials = 1004,
    DuplicateUid = 1005,
    UnsupportedLibraryVersion = 1006,
    InvalidApplicationIdToken = 1007,
    ApplicationIdRequired = 1008,
    UserNotFound = 1009,
    InvalidDigest = 1010,
    InvalidNonce = 1011,
    NonceExpired = 1012,
    NonceGenerationFailed = 1013,
    RegisterFailed = 1014,
    TokenAuthorizationRequired = 1015,
    AuthorizationNotEnabled = 1016,

    _MaxValue = 1017
};

} } } } }
