#pragma once

#include <strix/net/object/MetaClass.h>
#include <strix/client/core/CoreMessages.h>
#include <strix/client/core/message/DefaultParameterMessageDispatcher.h>
#include <strix/client/core/model/Model.h>
#include <strix/client/core/RequestClient.h>
#include <strix/client/core/request/RequestDispatcher.h>

namespace strix { namespace client { namespace core {

/**
 *  Base client controller for Create, Read, Update, Delete actions
 */
class CRUDClient : public RequestClient {
public:
	CRUDClient() {}

	/**
	 *  Initialize CRUD Client with a parameter class for search operations
	 *  @param	parameterClass	The parameter class to use
	 */
	CRUDClient(const strix::net::object::MetaClass &parameterClass) : m_parameterClass(&parameterClass) {}
	
	virtual ~CRUDClient() {}

	/**
	 *  Return the parameter class used for search operations
	 *  @returns	The parameter class
	 */
	const strix::net::object::MetaClass &GetParameterClass() const {
		return *m_parameterClass;
	}

	/**
	 *  Add the dispatcher to this client
	 *  @param	messageDispatcher	The dispatcher to add
	 */
	virtual void AddMessageHandlers(const strix::client::core::message::DefaultParameterMessageDispatcherPtr &messageDispatcher)
	{
		m_messageDispatcher = messageDispatcher;
	}

	virtual void RemoveMessageHandlers() {}

	virtual void OnCreateResponse(request::RequestResult<message::CreateResponsePtr> result) {}

	virtual void OnCreateFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void OnGetResponse(request::RequestResult<message::GetResponsePtr> result) {}

	virtual void OnGetFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void OnGetCountResponse(request::RequestResult<message::GetCountResponsePtr> result) {}

	virtual void OnGetCountFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void OnSetResponse(request::RequestResult<message::SetResponsePtr> result) {}

	virtual void OnSetFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void OnSetByResponse(request::RequestResult<message::SetByResponsePtr> result) {}

	virtual void OnSetByFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void OnDeleteResponse(request::RequestResult<message::DeleteResponsePtr> result) {}

	virtual void OnDeleteFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void OnDeleteByResponse(request::RequestResult<message::DeleteByResponsePtr> result) {}

	virtual void OnDeleteByFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void OnSearchResponse(request::RequestResult<message::SearchResponsePtr> result) {}

	virtual void OnSearchFailed(request::RequestResult<message::FailureMessagePtr> result) {}

	virtual void Create(message::CreateMessagePtr message, request::RequestResultHandlerT<message::CreateResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void Get(message::GetMessagePtr message, request::RequestResultHandlerT<message::GetResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void GetCount(message::GetCountMessagePtr message, request::RequestResultHandlerT<message::GetCountResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void Set(message::SetMessagePtr message, request::RequestResultHandlerT<message::SetResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void SetBy(message::SetByMessagePtr message, request::RequestResultHandlerT<message::SetByResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void Delete(message::DeleteMessagePtr message, request::RequestResultHandlerT<message::DeleteResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void DeleteBy(message::DeleteByMessagePtr message, request::RequestResultHandlerT<message::DeleteByResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void Search(message::SearchMessagePtr message, request::RequestResultHandlerT<message::SearchResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void Search(int limit, int offset, request::RequestResultHandlerT<message::SearchResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

	virtual void Search(model::manager::filter::ConditionPtr condition, model::manager::filter::OrderPtr order, int limit, int offset, request::RequestResultHandlerT<message::SearchResponse> handler, request::RequestFailureHandler failureHandler, std::shared_ptr<request::RequestConfig> config = nullptr);

protected:
	const strix::net::object::MetaClass * m_parameterClass;
	strix::client::core::message::DefaultParameterMessageDispatcherPtr m_messageDispatcher;
};

} } }