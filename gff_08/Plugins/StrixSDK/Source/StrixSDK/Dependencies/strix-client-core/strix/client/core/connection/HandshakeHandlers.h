#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/message/MessageChannel.h>

#include <functional>

namespace strix { namespace client { namespace core { namespace connection {

/**
 *  A handler for a successful handshake
 */
typedef std::function<void()> HandshakeResultHandler;

/**
 *  A handler for a failed handshake
 */
typedef std::function<void()> HandshakeFailureHandler;

/**
 *  A handler for the result of a handshake attempt
 */
typedef std::function<void(HandshakeResultHandler, HandshakeFailureHandler)> HandshakeCallback;

/**
 *  A verification function for checking if a message is part of a handshake
 */
typedef std::function<bool(strix::net::object::ObjectPtr)> HandshakeVerifier;

/**
 *  A container for a handshake callback and a handshake verifier for use with message channels
 */
struct HandshakeContext
{
  HandshakeCallback m_callback;
  HandshakeVerifier m_verifier;
};

} } } }
