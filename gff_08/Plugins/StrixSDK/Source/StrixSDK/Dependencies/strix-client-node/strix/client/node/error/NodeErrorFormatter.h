#pragma once

#include "NodeErrorCode.h"
#include <strix/client/core/error/ErrorFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace client { namespace node { namespace error {

using namespace strix::client::core::error;

class NodeErrorFormatter : public ErrorFormatter {
public:
    const char *GetErrorCodeName(int code) override {
        switch(code) {
            case NodeErrorCode::NoNodesAvailable: return "NodeErrorCode::NoNodesAvailable";
            case NodeErrorCode::NodeAlreadyExists: return "NodeErrorCode::NodeAlreadyExists";
            default: return nullptr;
        }
    }

    std::string GetErrorDescription(int code) override {
        switch(code) {
            case NodeErrorCode::NoNodesAvailable: return "No nodes available";
            case NodeErrorCode::NodeAlreadyExists: return "Node already exists";
			default: {
				std::stringstream st;
				st << "Unknown error: " << code;
				return st.str();
			}
        }
    }
};

} } } }
