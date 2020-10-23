#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a search request
 *  
 *  Parameter message that uses parameter classes
 *  
 *  Contains a list of objects of the parameter type representing the found objects
 *  
 *  Strix response type - Received from server after request made
 */
class SearchResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(SearchResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SearchResponse")
		STRIX_PROPERTY(m_modelCollection)
	)

	SearchResponse() {}

	SearchResponse(const MetaClass &parameterClass)
		: ParameterResponseMessage(parameterClass) {}

	SearchResponse(const MetaClass &parameterClass, strix::net::object::ObjectList roomModels)
		: ParameterResponseMessage(parameterClass), m_modelCollection(std::move(roomModels)) {}

	virtual ~SearchResponse() {}

	/**
	 *  Get the list of Objects held by this response
	 *  @returns	A list of Objects
	 */
	strix::net::object::ObjectList &GetModelCollection() {
		return m_modelCollection;
	}

	/**
	 *  Set the list of Objects held by this response
	 *  @param	modelCollection	The list of Objects
	 */
	void SetModelCollection(strix::net::object::ObjectList modelCollection) {
		m_modelCollection = std::move(modelCollection);
	}

private:
	strix::net::object::ObjectList m_modelCollection;
};

typedef std::shared_ptr<SearchResponse> SearchResponsePtr;

} } } }
