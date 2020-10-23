#pragma once

#include "StandardErrorCode.h"
#include <strix/client/core/error/ErrorFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace client { namespace core { namespace error {

using namespace strix::client::core::error;

class StandardErrorFormatter : public ErrorFormatter {
public:
    const char *GetErrorCodeName(int code) override {
        switch(code) {
            case StandardErrorCode::UnknownError: return "StandardErrorCode::UnknownError";
            case StandardErrorCode::InternalError: return "StandardErrorCode::InternalError";
            case StandardErrorCode::PermissionDenied: return "StandardErrorCode::PermissionDenied";
            case StandardErrorCode::LockFailed: return "StandardErrorCode::LockFailed";
            case StandardErrorCode::LockTimeout: return "StandardErrorCode::LockTimeout";
            case StandardErrorCode::InstantiationFailed: return "StandardErrorCode::InstantiationFailed";
            case StandardErrorCode::NoSuchProperty: return "StandardErrorCode::NoSuchProperty";
            case StandardErrorCode::InvalidPropertySetting: return "StandardErrorCode::InvalidPropertySetting";
            case StandardErrorCode::IncorrectMessageType: return "StandardErrorCode::IncorrectMessageType";
            case StandardErrorCode::RequestTimeout: return "StandardErrorCode::RequestTimeout";
            case StandardErrorCode::ModelNotFound: return "StandardErrorCode::ModelNotFound";
            case StandardErrorCode::ConnectionError: return "StandardErrorCode::ConnectionError";
            default: return nullptr;
        }
    }

    std::string GetErrorDescription(int code) override {
        switch(code) {
            case StandardErrorCode::UnknownError: return "Unknown error";
            case StandardErrorCode::InternalError: return "Internal error";
            case StandardErrorCode::PermissionDenied: return "Permission denied";
            case StandardErrorCode::LockFailed: return "Lock failed";
            case StandardErrorCode::LockTimeout: return "Lock timed out";
            case StandardErrorCode::InstantiationFailed: return "Instantiation failed";
            case StandardErrorCode::NoSuchProperty: return "No such property";
            case StandardErrorCode::InvalidPropertySetting: return "Invalid property setting";
            case StandardErrorCode::IncorrectMessageType: return "Incorrect message type";
            case StandardErrorCode::RequestTimeout: return "Request timeout";
            case StandardErrorCode::ModelNotFound: return "Model not found";
            case StandardErrorCode::ConnectionError: return "Connection error";
			default: {
				std::stringstream st;
				st << "Unknown error: " << code;
				return st.str();
			}
        }
    }
};

} } } }
