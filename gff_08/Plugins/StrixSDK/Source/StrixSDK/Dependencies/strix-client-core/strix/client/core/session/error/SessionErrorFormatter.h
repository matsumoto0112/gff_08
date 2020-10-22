#pragma once

#include "SessionErrorCode.h"
#include <strix/client/core/error/ErrorFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace client { namespace core { namespace session { namespace error {

using namespace strix::client::core::error;

class SessionErrorFormatter : public ErrorFormatter {
public:
    const char *GetErrorCodeName(int code) override {
        switch(code) {
            case SessionErrorCode::InvalidSessionToken: return "SessionErrorCode::InvalidSessionToken";
            case SessionErrorCode::SessionNotFound: return "SessionErrorCode::SessionNotFound";
            default: return nullptr;
        }
    }

    std::string GetErrorDescription(int code) override {
        switch(code) {
            case SessionErrorCode::InvalidSessionToken: return "Invalid session token";
            case SessionErrorCode::SessionNotFound: return "Session not found";
			default: {
				std::stringstream st;
				st << "Unknown error: " << code;
				return st.str();
			}
        }
    }
};

} } } } }
