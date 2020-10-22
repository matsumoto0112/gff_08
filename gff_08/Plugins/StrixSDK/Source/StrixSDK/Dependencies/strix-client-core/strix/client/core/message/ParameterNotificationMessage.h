#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/ParameterMessage.h>
#include <strix/client/core/message/NotificationMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base parameter notification class
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *
 *  Strix notification type - Received when another player performed some action
 */
class ParameterNotificationMessage : public ParameterMessage, public NotificationMessage
{
public:
	STRIX_CLASS(ParameterNotificationMessage, ParameterMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.ParameterNotificationMessage")
		STRIX_CLASS_SUPER(NotificationMessage)
	)

	ParameterNotificationMessage() : ParameterMessage(1) {
	}

	/**
	 *  Construct a ParameterNotificationMessage that can operate on the given number of classes
	 *  @param	numClasses	The number of MetaClasses
	 */
	ParameterNotificationMessage(int numClasses) : ParameterMessage(numClasses) {
	}

	/**
	 *  Construct a ParameterNotificationMessage that can operate on the given class
	 *  @param	parameterClass	The MetaClass that can be operated on
	 */
	ParameterNotificationMessage(const MetaClass &parameterClass) : ParameterMessage(parameterClass) {
	}

	/**
	 *  Construct a ParameterNotificationMessage that can operate on the given classes
	 *  @param	parameterClasses	The MetaClasses that can be operated on
	 */
	ParameterNotificationMessage(const std::vector<const MetaClass *> &parameterClasses) : ParameterMessage(parameterClasses) {
	}
};

} } } }

