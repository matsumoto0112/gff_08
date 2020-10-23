#pragma once

#include <strix/net/object/MetaClass.h>
#include <strix/client/core/message/MessageDispatcher.h>

namespace strix { namespace net { namespace message {
class MessageChannel;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
}}}

#include <unordered_map>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  The default message dispatcher. Dispatches the incoming message from the server to the registered handlers
 */
class DefaultMessageDispatcher : public MessageDispatcher
{
public:
	DefaultMessageDispatcher() {}
	
	virtual ~DefaultMessageDispatcher() {}

	/**
	 *  Register the message handler for the given class of messages
	 *  @params	messageClass	The class of messages the handler will handle
	 *  @params	messageHandler	The handler function that will accept messages of the messageClass type
	 */
	void AddMessageHandler(const strix::net::object::MetaClass &messageClass, const MessageHandler &messageHandler);

	/**
	 *  Remove the message handler for the given message class
	 *  @params	messageClass	The class of messages to remove the handler of
	 */
	void RemoveMessageHandler(const strix::net::object::MetaClass &messageClass);

	/**
	 *  Get the message handler for a given message class
	 *  @params	messageClass	The class to get the handler of
	 */
	MessageHandler GetMessageHandler(const strix::net::object::MetaClass &messageClass);

	/**
	 *  Call the handler associated with the type of the given message
	 *  @params	messageChannel	The channel the message was received on. This may be given as an argument to the handler
	 *  @params	message	The message received. Dispatch should deduce its type and call the relevant handler
	 */
	bool Dispatch (const MessageChannelPtr &messageChannel, const strix::net::object::ObjectPtr &message);
	
private:
	std::unordered_map<strix::net::object::MetaClass::ClassId, MessageHandler> m_handlerMap;
};

} } } }
