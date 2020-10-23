#pragma once

#include "ReplicaErrorCode.h"
#include <strix/client/core/error/ErrorFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace client { namespace replica { namespace error {

using namespace strix::client::core::error;

class ReplicaErrorFormatter : public ErrorFormatter {
public:
    const char *GetErrorCodeName(int code) override {
        switch(code) {
            case ReplicaErrorCode::NotReplicaOwner: return "ReplicaErrorCode::NotReplicaOwner";
            case ReplicaErrorCode::NotRoomMember: return "ReplicaErrorCode::NotRoomMember";
            case ReplicaErrorCode::NotRoomOwner: return "ReplicaErrorCode::NotRoomOwner";
            case ReplicaErrorCode::WrongPropertyMapFormat: return "ReplicaErrorCode::WrongPropertyMapFormat";
            case ReplicaErrorCode::ReplicaNotSynchronized: return "ReplicaErrorCode::ReplicaNotSynchronized";
            default: return nullptr;
        }
    }

    std::string GetErrorDescription(int code) override {
        switch(code) {
            case ReplicaErrorCode::NotReplicaOwner: return "Not replica owner";
            case ReplicaErrorCode::NotRoomMember: return "Not room member";
            case ReplicaErrorCode::NotRoomOwner: return "Not room owner";
            case ReplicaErrorCode::WrongPropertyMapFormat: return "Wrong property map format";
            case ReplicaErrorCode::ReplicaNotSynchronized: return "Replica is not synchronized";
			default: {
				std::stringstream st;
				st << "Unknown error: " << code;
				return st.str();
			}
        }
    }
};

} } } }
