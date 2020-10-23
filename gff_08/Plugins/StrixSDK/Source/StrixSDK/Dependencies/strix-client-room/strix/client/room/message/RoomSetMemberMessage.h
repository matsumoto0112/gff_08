#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>

#include <map>
#include <utility>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A request to set member properties
 *  
 *  Strix message type - Used for sending requests to the server
 */
class RoomSetMemberMessage : public strix::client::core::message::ParameterRequestMessage
{
public:
	STRIX_CLASS(RoomSetMemberMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomSetMemberMessage")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_properties)
	)

	RoomSetMemberMessage() {}

	RoomSetMemberMessage(const MetaClass &parameterClass)
		: ParameterRequestMessage(parameterClass) {}

	RoomSetMemberMessage(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	RoomSetMemberMessage(const MetaClass &parameterClass, long long primaryKey)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}
	
	RoomSetMemberMessage(const MetaClass &parameterClass, long long primaryKey, std::map<std::string, strix::net::object::ObjectPtr> properties)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey), m_properties(std::move(properties)) {}

	virtual ~RoomSetMemberMessage() = default;

	/**
	 *  Return the room id this message will be sent to
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() const {
		return m_primaryKey;
	}

	/**
	 *  Set the room to send to
	 *  @param	primaryKey	The room id
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Return the member properties that will be set
	 *  @returns	A map of strings (property names) and objects (values)
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() const {
		return m_properties;
	}

	/**
	 *  Set the member properties that will be set
	 *  @param	properties	A map of strings (property names) and objects (values)
	 */
	void SetProperties(std::map<std::string, strix::net::object::ObjectPtr> properties) {
		m_properties = std::move(properties);
	}

private:
	long long m_primaryKey;
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<RoomSetMemberMessage> RoomSetMemberMessagePtr;

} } } }
