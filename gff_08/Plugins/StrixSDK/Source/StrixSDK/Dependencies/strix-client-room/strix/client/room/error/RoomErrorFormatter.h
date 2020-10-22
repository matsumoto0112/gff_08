#pragma once

#include "RoomErrorCode.h"
#include <strix/client/core/error/ErrorFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace client { namespace room { namespace error {

using namespace strix::client::core::error;

class RoomErrorFormatter : public ErrorFormatter {
public:
    const char *GetErrorCodeName(int code) override {
        switch(code) {
            case RoomErrorCode::MessageLimitReached: return "RoomErrorCode::MessageLimitReached";
            case RoomErrorCode::NotRoomMember: return "RoomErrorCode::NotRoomMember";
            case RoomErrorCode::NotRoomOwner: return "RoomErrorCode::NotRoomOwner";
            case RoomErrorCode::RoomFullOfMembers: return "RoomErrorCode::RoomFullOfMembers";
            case RoomErrorCode::RoomNotFound: return "RoomErrorCode::RoomNotFound";
            case RoomErrorCode::RoomMemberNotFound: return "RoomErrorCode::RoomMemberNotFound";
            case RoomErrorCode::NotAllowedForOtherRoomMember: return "RoomErrorCode::NotAllowedForOtherRoomMember";
            case RoomErrorCode::AlreadyInRoom: return "RoomErrorCode::AlreadyInRoom";
            case RoomErrorCode::WrongRoomPassword: return "RoomErrorCode::WrongRoomPassword";
            case RoomErrorCode::RoomNotJoinable: return "RoomErrorCode::RoomNotJoinable";
            case RoomErrorCode::NoRoomsAvailable: return "RoomErrorCode::NoRoomsAvailable";
            case RoomErrorCode::MaxRoomCountReached: return "RoomErrorCode::MaxRoomCountReached";
            default: return nullptr;
        }
    }

    std::string GetErrorDescription(int code) override {
        switch(code) {
            case RoomErrorCode::MessageLimitReached: return "Message limit reached";
            case RoomErrorCode::NotRoomMember: return "Not room member";
            case RoomErrorCode::NotRoomOwner: return "Not room owner";
            case RoomErrorCode::RoomFullOfMembers: return "The room is full of members";
            case RoomErrorCode::RoomNotFound: return "Room not found";
            case RoomErrorCode::RoomMemberNotFound: return "Room member not found";
            case RoomErrorCode::NotAllowedForOtherRoomMember: return "Not allowed for other room member";
            case RoomErrorCode::AlreadyInRoom: return "Already in the room";
            case RoomErrorCode::WrongRoomPassword: return "Wrong room password";
            case RoomErrorCode::RoomNotJoinable: return "The room is not joinable";
            case RoomErrorCode::NoRoomsAvailable: return "No rooms available";
            case RoomErrorCode::MaxRoomCountReached: return "Max room count reached";
			default: {
				std::stringstream st;
				st << "Unknown error: " << code;
				return st.str();
			}
        }
    }
};

} } } }
