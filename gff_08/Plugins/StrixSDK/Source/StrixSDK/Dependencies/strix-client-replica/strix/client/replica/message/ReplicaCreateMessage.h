#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/UID.h>
#include <strix/client/core/message/ParameterRequestMessage.h>

namespace strix { namespace client { namespace replica { namespace message {

/**
 *  A message holding data for a creation of a replica
 */
class ReplicaCreateMessage : public strix::client::core::message::ParameterRequestMessage
{
public:
	STRIX_CLASS(ReplicaCreateMessage, ParameterRequestMessage)		
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.message.ReplicaCreateMessage")
		STRIX_PROPERTY(m_objectType)
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_properties)
	)

	ReplicaCreateMessage()
	{
	}

	ReplicaCreateMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass)
	{
	}

	virtual ~ReplicaCreateMessage()
	{
	}

	/**
	 *  Return the desired object type
	 *  @returns	The type id
	 */
	int GetObjectType()
	{
		return m_objectType;
	}

	/**
	 *  Set the desired object type
	 *  @param	objectType	The type id
	 */
	void SetObjectType(int objectType)
	{
		m_objectType = objectType;
	}

	/**
	 *  Return the id of the desired room to create in
	 *  @returns	The room id
	 */
	long long GetRoomId()
	{
		return m_roomId;
	}

	/**
	 *  Set the id for the desired room to create in
	 *  @param	roomId	The room id
	 */
	void SetRoomId(long long roomId)
	{
		m_roomId = roomId;
	}

	/**
	 *  Return the desired properties to set on create
	 *  @returns	A map of int (property id) to object (property value)
	 */
	std::map<int, net::object::ObjectPtr> &GetProperties()
	{
		return m_properties;
	}

	/**
	 *  Set the desired properties to set on create
	 *  @param	properties	A map of int (property id) to object (property value)
	 */
	void SetProperties(const std::map<int, net::object::ObjectPtr> &properties)
	{
		m_properties = properties;
	}

private:
	int m_objectType;
	long long m_roomId;
	std::map<int, net::object::ObjectPtr> m_properties;
};

} } } }
