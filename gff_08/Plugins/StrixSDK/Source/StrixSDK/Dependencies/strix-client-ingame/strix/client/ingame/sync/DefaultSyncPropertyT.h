#pragma once

#include <strix/client/ingame/sync/SyncPropertyT.h>

#include <memory>

namespace strix { namespace client { namespace ingame { namespace sync {

/**
 *  A property of type T synchronizable between clients
 */
template <typename T>
class DefaultSyncPropertyT : public SyncPropertyT<T>
{
public:
	DefaultSyncPropertyT(std::string propertyName, T *value)
		: SyncPropertyT<T>(*value), m_propertyName(std::move(propertyName)), m_propertyId(0), m_value(value) {}
	
	DefaultSyncPropertyT(int propertyId, T *value)
		: SyncPropertyT<T>(*value), m_propertyName(""), m_propertyId(propertyId), m_value(value) {}

	/**
	 *  Get this property's ID
	 *  @returns	The ID
	 */
	int GetPropertyId() const override
	{
		return m_propertyId;
	}

	/**
	 *  Get this property's name
	 *  @returns	The name of the property
	 */
	const std::string & GetPropertyName() const override
	{
		return m_propertyName;
	}

	/**
	 *  Get the local value of the property
	 *  @returns	The value
	 */
	const T &GetValue() const override
	{
		return *m_value;
	}

	/**
	 *  Set the local value of the property
	 *  @param	value	The value
	 */
	void SetValue(T value) override
	{
		*m_value = value;
	}

protected:
	std::string m_propertyName;
	int m_propertyId;
	T *m_value;
};

} } } }
