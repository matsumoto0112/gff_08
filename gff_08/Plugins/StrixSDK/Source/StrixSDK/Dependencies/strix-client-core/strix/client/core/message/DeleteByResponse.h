#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Reponse to a successful delete by condition request
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix response type - Received from server after request made
 */
class DeleteByResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(DeleteByResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DeleteByResponse")
		STRIX_PROPERTY(m_primaryKeys)
	)

	DeleteByResponse() {}

	DeleteByResponse(std::vector<long long> primaryKeys) 
		: m_primaryKeys(std::move(primaryKeys)) { }

	virtual ~DeleteByResponse() {}

	/**
	 *  Get the primary keys of the objects that were deleted
	 *  @returns	A vector of primary keys
	 */
	const std::vector<long long> &GetPrimaryKeys() const {
		return m_primaryKeys;
	}

	/**
	 *  Set the primary keys of the objects that were deleted
	 *  @param	primaryKeys	A vector of primary keys
	 */
	void SetPrimaryKeys(const std::vector<long long> &primaryKeys) {
		m_primaryKeys = primaryKeys;
	}

private:
	std::vector<long long> m_primaryKeys;
};

typedef std::shared_ptr<DeleteByResponse> DeleteByResponsePtr;

} } } }
