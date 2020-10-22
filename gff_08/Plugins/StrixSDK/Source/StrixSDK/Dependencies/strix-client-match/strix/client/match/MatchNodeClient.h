#pragma once

#include <strix/client/node/NodeClient.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/client/core/model/manager/filter/Order.h>

#include <memory>

namespace strix { namespace client { namespace match {

/**
 *  Controller class for node operations with match rooms.
 *  Extends NodeClient to provide functionality for match rooms
 */
class MatchNodeClient : public strix::client::node::NodeClient
{
public:
	MatchNodeClient() = default;

	MatchNodeClient(const strix::net::object::MetaClass &nodeClass, const strix::net::object::MetaClass &nodeRoomClass) : NodeClient(nodeClass, nodeRoomClass) {}

	virtual ~MatchNodeClient() = default;

	/**
	 *  Request information on joinable rooms and their data. Limit and offset parameters can be used to
	 *  retrieve pages of rooms from the full list. The callbacks are triggered on a response from the server
	 *  @param	limit	The maximum number of results to retrieve
	 *  @param	offset	The offset into the full list to begin to retrieve from
	 *  @param	handler	Called on success. A function that takes a RequestResult<NodeRoomSearchResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void SearchJoinableRoom(int limit, int offset, core::request::RequestResultHandlerT<strix::client::node::message::NodeRoomSearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request information on joinable rooms and their data with some condition. Limit and offset parameters can be used to
	 *  retrieve pages of rooms from the full list. The callbacks are triggered on a response from the server
	 *  @param	condition	The condition to filter results from
	 *  @param	order	The order with which to display results
	 *  @param	limit	The maximum number of results to retrieve
	 *  @param	offset	The offset into the full list to begin to retrieve from
	 *  @param	handler	Called on success. A function that takes a RequestResult<NodeRoomSearchResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void SearchJoinableRoom(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset, core::request::RequestResultHandlerT<strix::client::node::message::NodeRoomSearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request information on joinable rooms and their data with some condition in the message. Limit and offset parameters in the message can be used to
	 *  retrieve pages of rooms from the full list. The callbacks are triggered on a response from the server
	 *  @param	message	The message to send
	 *  @param	handler	Called on success. A function that takes a RequestResult<NodeRoomSearchResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void SearchJoinableRoom(core::message::SearchMessagePtr message, core::request::RequestResultHandlerT<strix::client::node::message::NodeRoomSearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request the number of joinable rooms. The callbacks are triggered on a response from the server
	 *  @param	handler	Called on success. A function that takes a RequestResult<GetCountResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void GetJoinableRoomCount(core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request the number of joinable rooms with some condition. The callbacks are triggered on a response from the server
	 *  @param	condition	The condition to filter results by
	 *  @param	handler	Called on success. A function that takes a RequestResult<GetCountResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void GetJoinableRoomCount(core::model::manager::filter::ConditionPtr condition, core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request the number of joinable rooms with some condition in a message. The callbacks are triggered on a response from the server
	 *  @param	message	The message to send
	 *  @param	handler	Called on success. A function that takes a RequestResult<GetCountResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void GetJoinableRoomCount(core::message::GetCountMessagePtr message, core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Return a condition that is true when the room is joinable (i.e, there is spare capacity)
	 *  @returns	The joinable condition
	 */
	virtual core::model::manager::filter::ConditionPtr MakeConditionForJoinableMatchRoom();

	/**
	 *  Add the joinable condition (i.e, there is spare capacity) to the given condition and returns
	 *  @param	oldCondition	The existing conditions
	 *  @returns	The existing conditions && the joinable condition
	 */
	virtual core::model::manager::filter::ConditionPtr MakeConditionForJoinableMatchRoom(core::model::manager::filter::ConditionPtr oldCondition);
};

typedef std::shared_ptr<MatchNodeClient> MatchNodeClientPtr;

} } }