#pragma once

namespace strix { namespace client { namespace node { namespace error {

enum NodeErrorCode: int {
    _MinValue = 0,

    NoNodesAvailable = 4000,
    NodeAlreadyExists = 4001,

    _MaxValue = 4002
};

} } } }
