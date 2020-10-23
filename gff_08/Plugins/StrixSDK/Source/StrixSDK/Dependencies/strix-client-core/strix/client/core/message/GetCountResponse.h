#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a get model count request. Contains the count number. 
 *
 *  Strix response type - Received from server after request made
 */
class GetCountResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(GetCountResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.GetCountResponse")
		STRIX_PROPERTY(m_count)
	)

	GetCountResponse() {}

	/**
	 *  Construct a GetCountResponse for the given parameterClass
	 *  @param	parameterClass	The parameter class
	 */
	GetCountResponse(const MetaClass &parameterClass) : ParameterResponseMessage(parameterClass) {}

	/**
	 *  Construct a GetCountResponse for the given parameterClass and a count
	 *  @param	parameterClass	The parameter class
	 *  @param	count	The count
	 */
	GetCountResponse(const MetaClass &parameterClass, long long count) : ParameterResponseMessage(parameterClass), m_count(count) {}

	virtual ~GetCountResponse() {}

	/**
	 *  Get the count number
	 *  @returns	The count
	 */
	const long long GetCount() const {
		return m_count;
	}

	/**
	 *  Set the count number
	 *  @param	count	The count
	 */
	void SetCount(long long count) {
		m_count = count;
	}

private:
	long long m_count;
};

typedef std::shared_ptr<GetCountResponse> GetCountResponsePtr;

} } } }
