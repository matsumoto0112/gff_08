#pragma once

namespace strix { namespace client { namespace room { namespace error {

enum RoomErrorCode: int {
    _MinValue = 0,

    MessageLimitReached = 5000,
    NotRoomMember = 5001,
    NotRoomOwner = 5002,
    RoomFullOfMembers = 5003,
    RoomNotFound = 5004,
    RoomMemberNotFound = 5005,
    NotAllowedForOtherRoomMember = 5006,
    AlreadyInRoom = 5007,
    WrongRoomPassword = 5008,
    RoomNotJoinable = 5009,
    NoRoomsAvailable = 5010,
    MaxRoomCountReached = 5011,

    _MaxValue = 5012
};

} } } }
