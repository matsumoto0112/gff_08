#pragma once

#include <memory>
#include <functional>

namespace strix { namespace net { namespace message {
class MessageChannel;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }


namespace strix { namespace client { namespace core { namespace message {
class RequestMessage;
class ResponseMessage;
class FailureMessage;
typedef std::shared_ptr<RequestMessage> RequestMessagePtr;
} } } }

namespace strix { namespace client { namespace core { namespace request {

/**
 *  Information about the result of a request
 */
template <typename T>
class RequestResult {
public:

	RequestResult(strix::net::message::MessageChannelPtr messageChannel, strix::client::core::message::RequestMessagePtr request, T result)
		: m_messageChannel(messageChannel),
		  m_request(request),
		  m_result(result)
	  { }

	strix::net::message::MessageChannelPtr m_messageChannel;
	strix::client::core::message::RequestMessagePtr m_request;
  T m_result;
};

template<typename TResponse, typename TBaseClass>
struct RequestResultHandlerTypeHolder {
	static_assert(std::is_base_of<TBaseClass, TResponse>::value, "RequestResult type parameter does not derive required super class");
	typedef std::function<void(RequestResult<std::shared_ptr<TResponse> >)> Type;
};

template struct RequestResultHandlerTypeHolder<message::ResponseMessage, message::ResponseMessage>;
template struct RequestResultHandlerTypeHolder<message::FailureMessage, message::FailureMessage>;

template<typename T>
using RequestResultHandlerT = typename RequestResultHandlerTypeHolder<T, message::ResponseMessage>::Type;

template<typename T>
using RequestFailureHandlerT = typename RequestResultHandlerTypeHolder<T, message::FailureMessage>::Type;

using RequestResultHandler = RequestResultHandlerT<message::ResponseMessage>;
using RequestFailureHandler = RequestFailureHandlerT<message::FailureMessage>;

} } } }
