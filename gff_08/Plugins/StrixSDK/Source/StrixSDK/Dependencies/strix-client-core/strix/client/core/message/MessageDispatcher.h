#pragma once

#include <strix/net/object/MetaClassT.h>

#include <memory>
#include <functional>

namespace strix { namespace net { namespace message {
class MessageChannel;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
}}}

namespace strix { namespace client { namespace core { namespace message {

using strix::net::message::MessageChannelPtr;

template<typename T>
struct MessageHandlerTypeHolder {
	static_assert(std::is_base_of<strix::net::object::Object, T>::value, "Type parameter does not derive Object");
	typedef std::function<void(MessageChannelPtr messageChannel, std::shared_ptr<T> message)> Type;
};

template struct MessageHandlerTypeHolder<strix::net::object::Object>;
template<typename T>
using MessageHandlerT = typename MessageHandlerTypeHolder<T>::Type;
using MessageHandler = MessageHandlerT<strix::net::object::Object>;

/**
 *  Dispatches the incoming message from the server to the registered handlers
 */
class MessageDispatcher
{
public:
	virtual ~MessageDispatcher() = default;

	/**
	 *  Register the message handler for the given class of messages
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	messageHandler	The handler function that will accept messages of the messageClass type
	 */
	virtual void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const MessageHandler &messageHandler) = 0;

	/**
	 *  Remove the message handler for the given message class
	 *  @params	messageClass	The class of messages to remove the handler of
	 */
	virtual void RemoveMessageHandler(const strix::net::object::MetaClass &messageClass) = 0;

	/**
	 *  Get the message handler for the given message class
	 *  @params	messageClass	The class to get the handler of
	 */
	virtual MessageHandler GetMessageHandler(const strix::net::object::MetaClass &messageClass) = 0;

	/**
	 *  Call the handler associated with the type of the given message
	 *  @params	messageChannel	The channel the message was received on. This may be given as an argument to the handler
	 *  @params	message	The message received. Dispatch should deduce its type and call the relevant handler
	 */
	virtual bool Dispatch(const MessageChannelPtr &messageChannel , const strix::net::object::ObjectPtr &message) = 0;

	/**
	 *  Registers the message handler for messages of type T
	 *  @params	messageHandler	The message handler
	 */
	template <typename T>
	void AddMessageHandlerT(const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler(strix::net::object::MetaClassT<T>::Get(), [messageHandler](auto pChannel, auto pMessage) {
			messageHandler(pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Registers the message handler for a message of type T as a function of type F called on V* obj with arguments (MessageChannelPtr, T)
	 *  @params	messageHandler	The handler that will be registered
	 *  @params	obj	The object to call the handler on
	 */
	template <typename T, typename F, typename V>
	void AddMessageHandlerT(F messageHandler, V *obj) {
		auto f = std::mem_fn(messageHandler);
		AddMessageHandler(strix::net::object::MetaClassT<T>::Get(), [obj, f](auto pChannel, auto pMessage) {
			f(obj, pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Remove the message handler of message type T
	 */
	template <typename T>
	void RemoveMessageHandlerT() {
		RemoveMessageHandler(strix::net::object::MetaClassT<T>::Get());
	}
};

typedef std::shared_ptr<strix::client::core::message::MessageDispatcher> MessageDispatcherPtr;

} } } }
