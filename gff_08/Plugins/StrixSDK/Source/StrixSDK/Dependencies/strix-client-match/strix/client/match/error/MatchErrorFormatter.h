#pragma once

#include "MatchErrorCode.h"
#include <strix/client/core/error/ErrorFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace client { namespace match { namespace error {

using namespace strix::client::core::error;

class MatchErrorFormatter : public ErrorFormatter {
public:
    const char *GetErrorCodeName(int code) override {
        switch(code) {
            case MatchErrorCode::SelfKickProhibited: return "MatchErrorCode::SelfKickProhibited";
            default: return nullptr;
        }
    }

    std::string GetErrorDescription(int code) override {
        switch(code) {
            case MatchErrorCode::SelfKickProhibited: return "Kicking yourself from the room is not allowed";
			default: {
				std::stringstream st;
				st << "Unknown error: " << code;
				return st.str();
			}
        }
    }
};

} } } }
