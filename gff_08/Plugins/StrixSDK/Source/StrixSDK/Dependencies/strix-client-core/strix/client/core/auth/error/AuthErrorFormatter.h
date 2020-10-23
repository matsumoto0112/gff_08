#pragma once

#include "AuthErrorCode.h"
#include <strix/client/core/error/ErrorFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace client { namespace core { namespace auth { namespace error {

using namespace strix::client::core::error;

class AuthErrorFormatter : public ErrorFormatter {
public:
    const char *GetErrorCodeName(int code) override {
        switch(code) {
            case AuthErrorCode::DuplicateConnectionForSameUid: return "AuthErrorCode::DuplicateConnectionForSameUid";
            case AuthErrorCode::CouldNotCalculateHash: return "AuthErrorCode::CouldNotCalculateHash";
            case AuthErrorCode::InvalidCredentialsType: return "AuthErrorCode::InvalidCredentialsType";
            case AuthErrorCode::InvalidCredentialsValue: return "AuthErrorCode::InvalidCredentialsValue";
            case AuthErrorCode::WrongCredentials: return "AuthErrorCode::WrongCredentials";
            case AuthErrorCode::DuplicateUid: return "AuthErrorCode::DuplicateUid";
            case AuthErrorCode::UnsupportedLibraryVersion: return "AuthErrorCode::UnsupportedLibraryVersion";
            case AuthErrorCode::InvalidApplicationIdToken: return "AuthErrorCode::InvalidApplicationIdToken";
            case AuthErrorCode::ApplicationIdRequired: return "AuthErrorCode::ApplicationIdRequired";
            case AuthErrorCode::UserNotFound: return "AuthErrorCode::UserNotFound";
            case AuthErrorCode::InvalidDigest: return "AuthErrorCode::InvalidDigest";
            case AuthErrorCode::InvalidNonce: return "AuthErrorCode::InvalidNonce";
            case AuthErrorCode::NonceExpired: return "AuthErrorCode::NonceExpired";
            case AuthErrorCode::NonceGenerationFailed: return "AuthErrorCode::NonceGenerationFailed";
            case AuthErrorCode::RegisterFailed: return "AuthErrorCode::RegisterFailed";
            case AuthErrorCode::TokenAuthorizationRequired: return "AuthErrorCode::TokenAuthorizationRequired";
            case AuthErrorCode::AuthorizationNotEnabled: return "AuthErrorCode::AuthorizationNotEnabled";
            default: return nullptr;
        }
    }

    std::string GetErrorDescription(int code) override {
        switch(code) {
            case AuthErrorCode::DuplicateConnectionForSameUid: return "Duplicate connection for same uid";
            case AuthErrorCode::CouldNotCalculateHash: return "Could not calculate hash";
            case AuthErrorCode::InvalidCredentialsType: return "Invalid credentials type";
            case AuthErrorCode::InvalidCredentialsValue: return "Invalid credentials value";
            case AuthErrorCode::WrongCredentials: return "Wrong credentials";
            case AuthErrorCode::DuplicateUid: return "Duplicate uid";
            case AuthErrorCode::UnsupportedLibraryVersion: return "Unsupported library version";
            case AuthErrorCode::InvalidApplicationIdToken: return "Invalid token for applicationId credentials";
            case AuthErrorCode::ApplicationIdRequired: return "ApplicationId required";
            case AuthErrorCode::UserNotFound: return "User not found";
            case AuthErrorCode::InvalidDigest: return "Invalid digest";
            case AuthErrorCode::InvalidNonce: return "Invalid nonce";
            case AuthErrorCode::NonceExpired: return "Nonce is expired";
            case AuthErrorCode::NonceGenerationFailed: return "Failed to generate nonce";
            case AuthErrorCode::RegisterFailed: return "Register failed";
            case AuthErrorCode::TokenAuthorizationRequired: return "Token authorization required";
            case AuthErrorCode::AuthorizationNotEnabled: return "Authorization not enabled";
			default: {
				std::stringstream st;
				st << "Unknown error: " << code;
				return st.str();
			}
        }
    }
};

} } } } }
