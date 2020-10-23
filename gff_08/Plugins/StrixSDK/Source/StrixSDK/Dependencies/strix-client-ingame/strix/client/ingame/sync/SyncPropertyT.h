#pragma once

#include <strix/client/ingame/sync/SyncProperty.h>
#include <strix/client/core/util/ComparisonUtil.h>
#include <strix/client/core/util/ObjectConverter.h>	

#include <memory>

namespace strix { namespace client { namespace ingame { namespace sync {

/**
 *  A property of type T synchronizable between clients
 */
template <typename T>
class SyncPropertyT : public SyncProperty
{
	STRIX_NET_LOGGER("strix.client.ingame.sync");
public:
	static_assert(std::is_convertible<T, net::object::ObjectAdapter>::value, "T must be convertible to strix::net::object::ObjectAdapter");

	SyncPropertyT() : m_lastValue() {}
	SyncPropertyT(T initialValue) : m_lastValue(std::move(initialValue)) {}

	/**
	 *  Get the local value of the property
	 *  @returns	The value
	 */
	virtual const T &GetValue() const = 0;

	/**
	 *  Set the local value of the property
	 *  @param	value	The value
	 */
	virtual void SetValue(T value) = 0;

	/**
	 *  Get the value of this property converted to a strix Object. Gets the local value with GetValue and converts with an ObjectConverter
	 *  @returns	The object value
	 */
	net::object::ObjectPtr GetObjectValue() override
	{
		const T &currentValue = GetValue();

		if (!m_objectValue || !core::util::ComparisonUtil::ApproximatelyEqual(m_lastValue, currentValue))
		{
			m_objectValue = core::util::ObjectConverter::ConvertValueToObject(currentValue);
		}

		return m_objectValue;
	}

	/**
	 *  Set the value of this property converted from a strix Object. Converts with an ObjectConverter and sets the local value with SetValue
	 *  @param	objectValue	The object value
	 */
	void SetObjectValue(net::object::ObjectPtr objectValue) override
	{
		m_objectValue = objectValue;

		if (core::util::ObjectConverter::TryConvertObjectToValue<T>(objectValue, m_lastValue))
		{
			SetValue(m_lastValue);
		}
		else
		{
			STRIX_NET_LOG_WARNING("Received value type does not match the property type");
		}
	}

protected:
	T m_lastValue;
	net::object::ObjectPtr m_objectValue;
};

} } } }
