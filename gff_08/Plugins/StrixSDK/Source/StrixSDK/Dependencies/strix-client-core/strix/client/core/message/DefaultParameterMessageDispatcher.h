#pragma once

#include <strix/client/core/message/MessageDispatcher.h>
#include <strix/net/object/MetaClass.h>
#include <strix/net/object/Object.h>

#include <unordered_map>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  The default implementation of a Message Dispatcher that handles parameterized classes
 *  
 *  On Dispatch calls the handler responsible for the message based on its type and its parameter types.
 */
class DefaultParameterMessageDispatcher : public MessageDispatcher
{
public:
	typedef strix::net::object::MetaClass MetaClass;
	DefaultParameterMessageDispatcher() {}
	
	virtual ~DefaultParameterMessageDispatcher() {}

	/**
	 *  Register the message handler for the given class of messages
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	messageHandler	The handler function that will accept messages of the messageClass type
	 */
	void AddMessageHandler(const MetaClass &messageClass, const MessageHandler &messageHandler);

	/**
	 *  Register the message handler for messages with the given class and parameter class
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	parameterClass	The type of the parameter in the given message
	 *  @params	messageHandler	The handler function that will accept messages with the given message and parameter classes
	 */
	void AddMessageHandler(const MetaClass &messageClass, const MetaClass &parameterClass, const MessageHandler &messageHandler);

	/**
	 *  Register the message handler for messages with the given class and two parameters
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	parameterClass	The first parameter type in the given message
	 *  @params	parameterClass2	The second parameter type in the given message
	 *  @params	messageHandler	The handler function that will accept messages with the given message and parameter classes
	 */
	void AddMessageHandler(const MetaClass &messageClass, const MetaClass &parameterClass, const MetaClass &parameterClass2, const MessageHandler &messageHandler);

	/**
	 *  Register a message handler for multiple types of messages
	 *  @params	messageClasses	A list of types of messages
	 *  @params	messageHandler	The handler for these types of messages
	 */
	void AddMessageHandler(const std::vector<MetaClass> &messageClasses, const MessageHandler &messageHandler);

	/**
	 *  Register a message handler for multiple types of messages
	 *  @params	messageClasses	A list of types of messages
	 *  @params	messageHandler	The handler for these types of messages
	 */
	void AddMessageHandler(const std::vector<std::reference_wrapper<const MetaClass>> &messageClasses, const MessageHandler &messageHandler);

	/**
	 *  Remove the message handler for the given message class
	 *  @params	messageClass	The class of messages to remove the handler of
	 */
	void RemoveMessageHandler(const MetaClass &messageClass);

	/**
	 *  Remove the message handler for the message of the given class and parameter class
	 *  @params	messageClass	The class of messages to remove the handler of
	 *  @params	parameterClass	The class of the parameter of the message
	 */
	void RemoveMessageHandler(const MetaClass &messageClass, const MetaClass &parameterClass);

	/**
	 *  Remove the message handler for the message of the given class and parameter classes
	 *  @params	messageClass	The class of messages to remove the handler of
	 *  @params	parameterClass	The type of the first parameter of the message
	 *  @params	parameterClass2	The type of the second parameter of the message
	 */
	void RemoveMessageHandler(const MetaClass &messageClass, const MetaClass &parameterClass, const MetaClass &parameterClass2);

	/**
	 *  Remove the message handler for the given message classes
	 *  @params	messageClasses	A list of the classes of messages to remove the handler of
	 */
	void RemoveMessageHandler(const std::vector<MetaClass> &messageClasses);

	/**
	 *  Get the message handler for the given class of message
	 *  @params	messageClass	The class of the message to get the handler of
	 *  @returns	The message handler for the class
	 */
	MessageHandler GetMessageHandler(const MetaClass &messageClass);

	/**
	 *  Get the message handler for the given class of message with the given parameter type
	 *  @params	messageClass	The class of the message to get the handler of
	 *  @params	messageParamClass	The type of the parameter of the message
	 *  @returns	The message handler for the class
	 */
	MessageHandler GetMessageHandler(const MetaClass &messageClass, const MetaClass &messageParamClass);

	/**
	 *  Get the message handler for the given class of messages
	 *  @params	messageClasses	A list of message classes to get the handler of
	 *  @returns	The message handler for the classes
	 */
	MessageHandler GetMessageHandler(const std::vector<MetaClass> &messageClasses);

	/**
	 *  Call the handler associated with the type of the given message
	 *  @params	messageChannel	The channel the message was received on. This may be given as an argument to the handler
	 *  @params	message	The message received. Dispatch should deduce its type and call the relevant handler
	 */
	bool Dispatch (const MessageChannelPtr &messageChannel, const strix::net::object::ObjectPtr &message);

	/**
	 *  Register the message handler for the given class of messages. When calling the message handler, the message is casted to type T.
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	messageHandler	The handler function that will accept messages of type T
	 */
	template <typename T>
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler(messageClass, [messageHandler](auto pChannel, auto pMessage) {
			messageHandler(pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Register the message handler for the given class of messages with the given parameter type. 
	 *  When calling the message handler, the message is casted to type T.
	 *  
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	parameterClass	The parameter type of the message
	 *  @params	messageHandler	The handler function that will accept messages of type T
	 */
	template <typename T>
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const strix::net::object::MetaClass &parameterClass, const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler(messageClass, parameterClass, [messageHandler](auto pChannel, auto pMessage) {
			messageHandler(pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Register the message handler for the given class of messages with the given parameter type.
	 *  When calling the message handler, the message is casted to type T.
	 *
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	parameterClass	The parameter type of the message
	 *  @params	messageHandler	The handler function that will accept messages of type T
	 */
	template <typename T, typename T2>
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const strix::net::object::MetaClass &parameterClass, const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler(messageClass, parameterClass, [messageHandler](auto pChannel, auto pMessage) {
			messageHandler(pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Register the message handler for the given class of messages with the given parameter types.
	 *  When calling the message handler, the message is casted to type T.
	 *
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	parameterClass	The first of the parameter types of the message
	 *  @params	parameterClass2	The second of the parameter types of the message
	 *  @params	messageHandler	The handler function that will accept messages of type T
	 */
	template <typename T, typename T2, typename T3>
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const strix::net::object::MetaClass &parameterClass, const strix::net::object::MetaClass &parameterClass2, const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler(messageClass, parameterClass, parameterClass2, [messageHandler](auto pChannel, auto pMessage) {
			messageHandler(pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Register the message handler for message of type messageClass as a function of type F called on V* obj with arguments (MessageChannelPtr, T),
	 *  where the message is casted to type T before the call
	 *  @params	messageClass	The class of messages this handler will handle
	 *  @params	messageHandler	The handler that will be registered
	 *  @params	obj	The object to call the handler on
	 */
	template <typename T, typename F, typename V>
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, F messageHandler, V *obj) {
		auto f = std::mem_fn(messageHandler);
		AddMessageHandler(messageClass, [obj, f](auto pChannel, auto pMessage) {
			f(obj, pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Register the message handler for messages of type messageClass with the parameter type parameterClass, 
	 *  as a function of type F called on V* obj with arguments (MessageChannelPtr, T),
	 *  where the message is casted to type T before the call
	 *  
	 *  @params	messageClass	The class of messages this handler will handle
	 *  @params	parameterClass	The parameter class of this message
	 *  @params	messageHandler	The handler that will be registered
	 *  @params	obj	The object to call the handler on
	 */
	template <typename T, typename T2, typename F, typename V>
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const strix::net::object::MetaClass &parameterClass, F messageHandler, V *obj) {
		auto f = std::mem_fn(messageHandler);
		AddMessageHandler(messageClass, parameterClass, [obj, f](auto pChannel, auto pMessage) {
			f(obj, pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Register the message handler for messages of type messageClass with the parameter types parameterClass and parameterClass2,
	 *  as a function of type F called on V* obj with arguments (MessageChannelPtr, T),
	 *  where the message is casted to type T before the call
	 *
	 *  @params	messageClass	The class of messages this handler will handle
	 *  @params	parameterClass	The first parameter class of this message
	 *  @params	parameterClass	The second parameter class of this message
	 *  @params	messageHandler	The handler that will be registered
	 *  @params	obj	The object to call the handler on
	 */
	template <typename T, typename T2, typename T3, typename F, typename V>
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const strix::net::object::MetaClass &parameterClass, const strix::net::object::MetaClass &parameterClass2, F messageHandler, V *obj) {
		auto f = std::mem_fn(messageHandler);
		AddMessageHandler(messageClass, parameterClass, parameterClass2, [obj, f](auto pChannel, auto pMessage) {
			f(obj, pChannel, std::static_pointer_cast<T>(pMessage));
		});
	}

	/**
	 *  Register the message handler for messages of type T
	 *  @params	messageHandler	The message handler
	 */
	template <typename T>
	void AddMessageHandlerT(const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler<T>(strix::net::object::MetaClassT<T>::Get(), messageHandler);
	}

	/**
	 *  Register the message handler for messages of type T with a parameter of type T2
	 *  @params	messageHandler	The message handler
	 */
	template <typename T, typename T2>
	void AddMessageHandlerT(const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler<T, T2>(strix::net::object::MetaClassT<T>::Get(), strix::net::object::MetaClassT<T2>::Get(), messageHandler);
	}

	/**
	 *  Register the message handler for messages of type T with parameters of types T2 and T3
	 *  @params	messageHandler	The message handler
	 */
	template <typename T, typename T2, typename T3>
	void AddMessageHandlerT(const MessageHandlerT<T> &messageHandler) {
		AddMessageHandler<T, T2, T3>(strix::net::object::MetaClassT<T>::Get(), strix::net::object::MetaClassT<T2>::Get(), strix::net::object::MetaClassT<T3>::Get(), messageHandler);
	}

	/**
	 *  Register the message handler for messages of type T as a function of type F called on V* obj with arguments (MessageChannelPtr, T)
	 *
	 *  @params	messageHandler	The handler that will be registered
	 *  @params	obj	The object to call the handler on
	 */
	template <typename T, typename F, typename V>
	void AddMessageHandlerT(F messageHandler, V *obj) {
		AddMessageHandler<T, F, V>(strix::net::object::MetaClassT<T>::Get(), messageHandler, obj);
	}

	/**
	 *  Register the message handler for messages of type T with parameters of type T2,
	 *  as a function of type F called on V* obj with arguments (MessageChannelPtr, T)
	 *
	 *  @params	messageHandler	The handler that will be registered
	 *  @params	obj	The object to call the handler on
	 */
	template <typename T, typename T2, typename F, typename V>
	void AddMessageHandlerT(F messageHandler, V *obj) {
		AddMessageHandler<T, T2, F, V>(strix::net::object::MetaClassT<T>::Get(), strix::net::object::MetaClassT<T2>::Get(), messageHandler, obj);
	}

	/**
	 *  Register the message handler for messages of type T with parameters of type T2 and T3,
	 *  as a function of type F called on V* obj with arguments (MessageChannelPtr, T)
	 *
	 *  @params	messageHandler	The handler that will be registered
	 *  @params	obj	The object to call the handler on
	 */
	template <typename T, typename T2, typename T3, typename F, typename V>
	void AddMessageHandlerT(F messageHandler, V *obj) {
		AddMessageHandler<T, T2, T3, F, V>(strix::net::object::MetaClassT<T>::Get(), strix::net::object::MetaClassT<T2>::Get(), strix::net::object::MetaClassT<T3>::Get(), messageHandler, obj);
	}

	/**
	 *  Remove the message handler for messages of type T
	 */
	template <typename T>
	void RemoveMessageHandlerT() {
		RemoveMessageHandler(strix::net::object::MetaClassT<T>::Get());
	}

	/**
	 *  Remove the message handler for messages of type T with parameter class T2
	 */
	template <typename T, typename T2>
	void RemoveMessageHandlerT() {
		RemoveMessageHandler(strix::net::object::MetaClassT<T>::Get(), strix::net::object::MetaClassT<T2>::Get());
	}

	/**
	 *  Remove the message handler for messages of type T with parameter class T2 and T3
	 */
	template <typename T, typename T2, typename T3>
	void RemoveMessageHandlerT() {
		RemoveMessageHandler(strix::net::object::MetaClassT<T>::Get(), strix::net::object::MetaClassT<T2>::Get(), strix::net::object::MetaClassT<T3>::Get());
	}

private:
	/**
	 *  A hash for the vector keys of the std::unordered_map holding the message handlers
	 */
	struct vec_hash {
		std::size_t operator()(const std::vector<MetaClass::ClassId> &vec) const {
			std::size_t seed = vec.size();
			for (auto& i : vec) {
				seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
			return seed;
		}
	};
	std::unordered_map<std::vector<MetaClass::ClassId>, MessageHandler, vec_hash> m_handlerMap;
};

typedef std::shared_ptr<DefaultParameterMessageDispatcher> DefaultParameterMessageDispatcherPtr;

} } } }
