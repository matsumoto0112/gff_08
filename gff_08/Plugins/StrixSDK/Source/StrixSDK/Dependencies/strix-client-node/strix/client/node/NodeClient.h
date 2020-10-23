#pragma once

#include <strix/client/core/CRUDClient.h>
#include <strix/client/node/message/NodeRoomSearchResponse.h>

namespace strix { namespace client { namespace node {

/**
 *  Abstract controller class for Node operations
 */
class NodeClient : public core::CRUDClient
{
public:
	NodeClient() = default;

	NodeClient(const strix::net::object::MetaClass &roomClass, const strix::net::object::MetaClass &nodeRoomClass) : CRUDClient(roomClass), m_nodeRoomClass(&nodeRoomClass) {}

	virtual ~NodeClient() = default;

	/**
	 *  Get the class of the room for this client
	 *  @returns	The meta class 
	 */
	const strix::net::object::MetaClass &GetNodeRoomClass() const {
		return *m_nodeRoomClass;
	}

	/**
	 *  Create a node and room on that node. The success or failure handlers are called on response from the server
	 *  @param	message	The message to send
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<CreateResponse> as input.
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void CreateNodeRoom(core::message::CreateMessagePtr message, core::request::RequestResultHandlerT<core::message::CreateResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Get a node room representing a server and room. The success or failure handlers are called on response from the server
	 *  @param	message	The message to send
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<GetResponse> as input. A function that takes a RequestResult<> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void GetNodeRoom(core::message::GetMessagePtr message, core::request::RequestResultHandlerT<core::message::GetResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Get the count of node rooms (servers with an existing room). The success or failure handlers are called on response from the server
	 *  @param	message	The message to send
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<GetCountResponse> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void GetNodeRoomCount(core::message::GetCountMessagePtr message, core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set a node room representing a server and room. The success or failure handlers are called on response from the server
	 *  @param	message	The message to send
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<SetResponse> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void SetNodeRoom(core::message::SetMessagePtr message, core::request::RequestResultHandlerT<core::message::SetResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set all node rooms (servers with a room) that match a condition
	 *  @param	message	The message to send (set condition specified here)
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<SetByResponse> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void SetByNodeRoom(core::message::SetByMessagePtr message, core::request::RequestResultHandlerT<core::message::SetByResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Delete a node room (a server and room). The success or failure handlers are called on response from the server
	 *  @param	message	The message to send
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<DeleteResponse> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void DeleteNodeRoom(core::message::DeleteMessagePtr message, core::request::RequestResultHandlerT<core::message::DeleteResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Delete all node rooms (servers with a room) that match a condition
	 *  @param	message	The message to send (delete condition specified here)
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<DeleteByResponse> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void DeleteByNodeRoom(core::message::DeleteByMessagePtr message, core::request::RequestResultHandlerT<core::message::DeleteByResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for node rooms (servers with a room) with a condition
	 *  @param	message	The message to send, containing the search parameters
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<NodeRoomSearchResponse> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void SearchNodeRoom(core::message::SearchMessagePtr message, core::request::RequestResultHandlerT<message::NodeRoomSearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for node rooms (servers with a room) with the given condition and parameters. The limit and offset
	 *  parameters can be used to return pages of results from a larger matching list
	 *  @param	condition	The condition to match
	 *  @param	order	The order in which to receive the list of node rooms
	 *  @param	limit	The maximum size of the list of node rooms
	 *  @param	offset	Where to begin the received list of matching node rooms from all matching node rooms
	 *  @param	handler	The handler called when successful. A function that takes a RequestResult<NodeRoomSearchResponse> as input
	 *  @param	failureHandler	The handler called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional optional parameters for the request (timeouts, etc)
	 */
	virtual void SearchNodeRoom(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset, core::request::RequestResultHandlerT<message::NodeRoomSearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Called when a successful create node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnCreateNodeRoomResponse(core::request::RequestResult<core::message::CreateResponsePtr> result) {}

	/**
	 *  Called when a failed create node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnCreateNodeRoomFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called when a successful get node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnGetNodeRoomResponse(core::request::RequestResult<core::message::GetResponsePtr> result) {}

	/**
	 *  Called when a failed get node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnGetNodeRoomFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called when a successful get node room count response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnGetNodeRoomCountResponse(core::request::RequestResult<core::message::GetCountResponsePtr> result) {}

	/**
	 *  Called when a failed get node room count response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnGetNodeRoomCountFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called when a successful set node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnSetNodeRoomResponse(core::request::RequestResult<core::message::SetResponsePtr> result) {}

	/**
	 *  Called when a failed set node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnSetNodeRoomFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called when a successful set by node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnSetByNodeRoomResponse(core::request::RequestResult<core::message::SetByResponsePtr> result) {}

	/**
	 *  Called when a failed set by node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnSetByNodeRoomFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called when a successful delete node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnDeleteNodeRoomResponse(core::request::RequestResult<core::message::DeleteResponsePtr> result) {}

	/**
	 *  Called when a failed delete node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnDeleteNodeRoomFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called when a successful delete by node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnDeleteByNodeRoomResponse(core::request::RequestResult<core::message::DeleteByResponsePtr> result) {}

	/**
	 *  Called when a failed delete by node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnDeleteByNodeRoomFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

	/**
	 *  Called when a successful search node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnSearchNodeRoomResponse(core::request::RequestResult<message::NodeRoomSearchResponsePtr> result) {}

	/**
	 *  Called when a failed search node room response is received
	 *  @param	result	The result from the server
	 */
	virtual void OnSearchNodeRoomFailed(core::request::RequestResult<core::message::FailureMessagePtr> result) {}

protected:
	const strix::net::object::MetaClass * m_nodeRoomClass;
};

} } }
