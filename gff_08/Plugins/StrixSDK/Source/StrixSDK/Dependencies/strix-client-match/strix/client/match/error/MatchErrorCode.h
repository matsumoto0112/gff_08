#pragma once

namespace strix { namespace client { namespace match { namespace error {

enum MatchErrorCode: int {
    _MinValue = 0,

    SelfKickProhibited = 7000,

    _MaxValue = 7001
};

} } } }
