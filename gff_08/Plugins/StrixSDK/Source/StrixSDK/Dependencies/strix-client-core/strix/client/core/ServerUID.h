#pragma once

#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace core {

/**
 *  A UID of a Strix server
 */
class ServerUID : public UID
{
public:
	STRIX_CLASS(ServerUID, UID)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.ServerUID")
		STRIX_PROPERTY(m_id)
	)

	ServerUID() {}

	/**
	 *  Construct a ServerUID
	 *
	 *  @param  id	The id
	 */
	ServerUID(long long id) {
		m_id = id;
	}

	virtual ~ServerUID() {}

	/**
	 *  Get the UID
	 *
	 *  @returns	The UID
	 */
	long long GetId() {
		return m_id;
	}

	/**
	 *  Set the UID
	 *
	 *  @param  id	The UID
	 */
	void SetId(long long id) {
		m_id = id;
	}

	/**
	 *  Compares to the given object
	 *
	 *  @param  rhs	The object to compare
	 *  @returns	1 if this UID > rhs, 2 if rhs > this UID, 0 if rhs == this UID. If rhst is another ServerUID, the difference between the two is returned
	 */
	int Compare(const Object &rhs) const override {
		if(!rhs.InstanceOf<ServerUID>())
			return Object::Compare(rhs);

		const ServerUID &uid = static_cast<const ServerUID&>(rhs);

		return static_cast<int>(m_id - uid.m_id);
	}

	/**
	 *  Write UID out to stream in the form "[ServerUID: id]"
	 *
	 *  @param  os	ostream
	 *  @return The stream
	 */
	std::ostream &WriteTo(std::ostream &os) const override
	{
		return os << "[ServerUID:" << m_id << ']';
	}

private:
	long long m_id;
};

typedef std::shared_ptr<ServerUID> ServerUIDPtr;

} } }
