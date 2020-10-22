#pragma once

#include <strix/client/core/message/FailureMessage.h>
#include <strix/client/core/message/ResponseMessage.h>
#include <strix/client/core/request/RequestDispatcher.h>
#include <memory>

namespace strix { namespace net { namespace object {
class Object;
typedef std::shared_ptr<Object> ObjectPtr;
} } }

namespace strix { namespace net { namespace message {
class MessageChannel;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }

namespace strix { namespace client { namespace core {

/**
 *  Client controller for request actions
 */
class RequestClient {
public:
	strix::net::message::MessageChannelPtr m_messageChannel;
	request::RequestDispatcherPtr m_requestDispatcher;

	RequestClient() : m_requestIds() {}

	virtual ~RequestClient()
	{
		if (m_requestDispatcher)
		{
			m_requestDispatcher->RemoveRequestContextsByIds(m_requestIds);
		}
	}

	/**
	 *  Initialize the request client on a message channel with a request dispatcher
	 *  @param	messageChannel	The channel to send and receive on
	 *  @param	requestDispatcher	The request dispatcher to use
	 */
	virtual void Init(strix::net::message::MessageChannelPtr messageChannel, request::RequestDispatcherPtr requestDispatcher);

protected:
	typedef request::RequestResultHandler ResponseHandler;

	/**
	 *  Send a request of type T. Call handlers on success/failure
	 *  @param	message	The message to send
	 *  @param	defaultHandler	The default handler to call on successful request
	 *  @param	handler	Second success handler
	 *  @param	defaultFailureHandler	The default handler to call on a failed request
	 *  @param	failureHandler	Second failure handler
	 *  @param	config	Additional parameters for the request
	 */
	template <typename T>
	void Request(net::object::ObjectPtr message, request::RequestResultHandlerT<T> defaultHandler, request::RequestResultHandlerT<T> handler, request::RequestFailureHandler defaultFailureHandler, request::RequestFailureHandler failureHandler, request::RequestConfigPtr config)
	{
		ResponseHandler newHandler = [defaultHandler, handler, requestIds = &m_requestIds](request::RequestResult<message::ResponseMessagePtr> requestResult) -> void {

			std::shared_ptr<T> result = std::static_pointer_cast<T>(requestResult.m_result);
			request::RequestResult<std::shared_ptr<T>> downcastedResult(
				requestResult.m_messageChannel,
				requestResult.m_request,
				result
			);

			requestIds->erase(requestResult.m_result->GetRequestId());

			if (defaultHandler)
			{
				defaultHandler(downcastedResult);
			}
			if (handler)
			{
				handler(downcastedResult);
			}
		};

		request::RequestFailureHandler newFailureHandler = (!defaultFailureHandler) ? failureHandler
			: [defaultFailureHandler, failureHandler, requestIds = &m_requestIds](request::RequestResult<message::FailureMessagePtr> requestResult) -> void {
			defaultFailureHandler(requestResult);

			requestIds->erase(requestResult.m_result->GetRequestId());

			if (failureHandler)
			{
				failureHandler(requestResult);
			}
		};

		int result = m_requestDispatcher->Request(m_messageChannel, message, newHandler, newFailureHandler, config);
		if (result != 0)
		{
			m_requestIds.insert(result);
		}
	}

private:
	std::set<int> m_requestIds;
};

} } }
