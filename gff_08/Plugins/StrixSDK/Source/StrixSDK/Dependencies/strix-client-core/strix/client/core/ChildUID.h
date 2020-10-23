#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/ServerUID.h>

namespace strix { namespace client { namespace core {

/**
 *  A UID of the child of a server
 */
class ChildUID : public UID
{
public:
	STRIX_CLASS(ChildUID, UID)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.ChildUID")
		STRIX_PROPERTY(m_serverUid)
		STRIX_PROPERTY(m_id)
	)
	
	typedef std::shared_ptr<ServerUID> ServerUIDPtr;

	ChildUID() {}

	/**
	 *  Construct a ChildUID
	 *  
	 *  @param  id	The child's id
	 *  @param  serverUid	The parent server's UID
	 */
	ChildUID(short id, ServerUIDPtr &serverUid) {
		m_id = id;
		m_serverUid = serverUid;
	}

	virtual ~ChildUID() {}

	/**
	 *  Get the child UID
	 *  
	 *  @returns	The UID
	 */
	long long GetId() {
		return m_id;
	}

	/**
	 *  Set the child UID
	 *
	 *  @param  id	The UID
	 */
	void SetId(long long id) {
		m_id = id;
	}

	/**
	 *  Get the parent server UID
	 *
	 *  @returns	The UID
	 */
	const ServerUIDPtr &GetServerUID() const {
		return m_serverUid;
	}

	/**
	 *  Set the parent server UID
	 *
	 *  @param  serverUid	The UID
	 */
	void SetServerUID(ServerUIDPtr &serverUid) {
		m_serverUid = serverUid;
	}

	/**
	 *  Compares to the given object
	 *
	 *  @param  rhs	The object to compare
	 *  @returns	1 if this UID > rhs, 2 if rhs > this UID, 0 if rhs == this UID. 
	 *		If rhs is another ChildUID on the same server, the difference between the child ids is returned
	 *		If rhs is another ChildUID on a different server, the server UIDs are compared.
	 *		If this UID has no server UID -1 is returned, if rhs has no server ID, 1 is returned
	 */
	int Compare(const Object &rhs) const override {
		if(!rhs.InstanceOf<ChildUID>())
			return Object::Compare(rhs);

		const ChildUID &uid = static_cast<const ChildUID&>(rhs);

		if(!m_serverUid)
			return -1;
		
		if(!uid.m_serverUid)
			return 1;

		int res = m_serverUid->Compare(*uid.m_serverUid);

		if(res != 0)
			return res;

		return static_cast<int>(m_id - uid.m_id);
	}

	/**
	 *  Write UID out to stream in the form "[ChildUID: server - child]"
	 *
	 *  @param  os	ostream
	 *  @return The stream
	 */
	std::ostream &WriteTo(std::ostream &os) const override
	{
		return os << "[ChildUID:" << m_serverUid->GetId() << '-' << m_id << ']';
	}

private:
	long long m_id;
	ServerUIDPtr m_serverUid;
};

} } }
