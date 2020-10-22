#pragma once

#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace core {

/**
 *  A shared UID
 */
class SharedUID : public UID
{
public:
	STRIX_CLASS(SharedUID, UID)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.SharedUID")
		STRIX_PROPERTY(m_id)
	)

	SharedUID() {}

	/**
	 *  Construct a SharedUID
	 *  
	 *  @param  id	The id
	 */
	SharedUID(long long id) {
		m_id = id;
	}

	virtual ~SharedUID() {}

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
	 *  @returns	1 if this UID > rhs, 2 if rhs > this UID, 0 if rhs == this UID. If rhs is another SharedUID, the difference between the two is returned
	 */
	int Compare(const Object &rhs) const override {
		if(!rhs.InstanceOf<SharedUID>())
			return Object::Compare(rhs);

		const SharedUID &uid = static_cast<const SharedUID&>(rhs);

		return static_cast<int>(m_id - uid.m_id);
	}

	/**
	 *  Write UID out to stream in the form "[SharedUID: id]"
	 *
	 *  @param  os	ostream
	 *  @return The stream
	 */
	std::ostream &WriteTo(std::ostream &os) const override
	{
		return os << "[SharedUID:" << m_id << ']';
	}

private:
	long long m_id;
};

typedef std::shared_ptr<SharedUID> SharedUIDPtr;

} } }
