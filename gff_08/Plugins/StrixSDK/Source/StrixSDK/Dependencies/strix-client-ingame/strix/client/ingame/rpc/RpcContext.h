#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/UID.h>
#include <strix/client/match/room/model/MatchRoomMember.h>

namespace strix { namespace client { namespace ingame { namespace rpc {
	
/**
 *  The context of an RPC. Contains sender information
 */
class RpcContext : public strix::net::object::Object
{
public:
	STRIX_CLASS(RpcContext, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.client.ingame.rpc.RpcContext")
		STRIX_PROPERTY(m_senderUid)
		STRIX_PROPERTY(m_sender)
	)

	RpcContext() {}

	virtual ~RpcContext() {}
	
	/**
	 *  Get the sender's UID
	 *  @returns	The sender's UID
	 */
	const client::core::UIDPtr &GetSenderUid() const {
		return m_senderUid;
	}

	/**
	 *  Set UID of the sender
	 *  @param	senderUid	The UID
	 */
	void SetSenderUid(const client::core::UIDPtr &senderUid) {
		m_senderUid = senderUid;
	}

	/**
	 *  Get the sender
	 *  @returns	The room member that sent the RPC
	 */
	const client::match::room::model::MatchRoomMemberPtr &GetSender() const {
		return m_sender;
	}

	/**
	 *  Set the sender
	 *  @param	sender	The room member that sent the RPC
	 */
	void SetSender(const client::match::room::model::MatchRoomMemberPtr &sender) {
		m_sender = sender;
	}

private:
	client::core::UIDPtr m_senderUid;
	client::match::room::model::MatchRoomMemberPtr m_sender;
};

typedef std::shared_ptr<RpcContext> RpcContextPtr;

} } } }
