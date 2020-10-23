#pragma once

namespace strix { namespace client { namespace replica { namespace error {

enum ReplicaErrorCode: int {
    _MinValue = 0,

    NotReplicaOwner = 6000,
    NotRoomMember = 6001,
    NotRoomOwner = 6002,
    WrongPropertyMapFormat = 6003,
    ReplicaNotSynchronized = 6004,

    _MaxValue = 6005
};

} } } }
