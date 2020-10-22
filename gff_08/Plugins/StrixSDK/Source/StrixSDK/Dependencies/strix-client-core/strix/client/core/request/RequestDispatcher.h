#pragma once

#include <strix/client/core/util/ConcurrentPriorityQueue.h>
#include <strix/client/core/request/RequestResult.h>

#include <atomic>
#include <map>
#include <memory>

namespace strix { namespace net { namespace object {
class Object;
typedef std::shared_ptr<Object> ObjectPtr;
} } }

namespace strix { namespace net { namespace message {
class MessageChannel;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }

namespace strix { namespace client { namespace core { namespace request {

class RequestConfig;
typedef std::shared_ptr<RequestConfig> RequestConfigPtr;

/**
 *  A dispatcher for making requests to the server and handling their responses
 */
class RequestDispatcher {
public:

	/**
	 *  Context information about a request
	 */
	class Context {
	public:
		strix::client::core::message::RequestMessagePtr request;
		std::weak_ptr<strix::net::message::MessageChannel> messageChannel;
		RequestResultHandler handler;
		RequestFailureHandler failureHandler;
		int requestId;
		std::chrono::steady_clock::time_point timeoutTime;
	};

	RequestDispatcher() : m_nextRequestId(1), m_timeoutQueue([](const std::shared_ptr<Context> &lhs, const std::shared_ptr<Context> &rhs) -> bool { return lhs->timeoutTime > rhs->timeoutTime; }) {}

	/**
	 *  Send a request to the server. Handlers are called on response from the server
	 *  @param	messageChannel	The message channel to send the request on
	 *  @param	request	The request to send
	 *  @param	handler	The handler to call on response that the request succeeded
	 *  @param	failureHandler	The handler to call on response that the request failed
	 *  @param	config	The length of the timeout for this request
	 *  @returns	The request ID for this request
	 */
	int Request(strix::net::message::MessageChannelPtr messageChannel, strix::net::object::ObjectPtr request, RequestResultHandler handler, RequestFailureHandler failureHandler, std::shared_ptr<RequestConfig> config = nullptr);

	/**
	 *  Dispatch the response message to the handlers of its request and remove the request from the list of contexts
	 *  @param	messageChannel	The message channel the response was received on
	 *  @param	message	The response
	 *  @returns	True if this response matches a request. False if the response does not match a request or the request has timed out
	 */
	bool Dispatch(strix::net::message::MessageChannelPtr messageChannel, strix::net::object::ObjectPtr message);

	/**
	 *  Remove request contexts with the given IDs. This prevents further handling of responses to these requests
	 *  @param	ids	The list of request IDs
	 */
	void RemoveRequestContextsByIds(const std::set<int> &ids);

	/**
	 *  Check the timeouts of each current request and remove the request context if the timeout has passed
	 */
	void CheckTimeout();

	void FailAllRequests(int errorCode);

private:
	std::atomic<int> m_nextRequestId;
	const int MaxRequestIdMask = 0xffff;
	std::map<int, std::shared_ptr<Context> > m_contextMap;
	strix::client::core::util::ConcurrentPriorityQueue<std::shared_ptr<Context>> m_timeoutQueue;
	std::mutex m_mutex;
};

typedef std::shared_ptr<strix::client::core::request::RequestDispatcher> RequestDispatcherPtr;

} } } }
