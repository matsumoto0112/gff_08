#pragma once

#include <strix/client/core/UID.h>
#include <iomanip>

namespace strix { namespace client { namespace core {

/**
 *  UID for a user of Strix
 */
class UserUID : public UID
{
public:
	STRIX_CLASS(UserUID, UID)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.UserUID")
		STRIX_PROPERTY(m_id)
	)

	UserUID() {}

	/**
	 *  Create UID from bytes
	 *  
	 *  @param  id	bytes representing the ID
	 */
	UserUID(std::vector<uint8_t> id) : m_id(std::move(id)) {}

	virtual ~UserUID() {}

	/**
	 *  Get the UID as bytes
	 *  
	 *  @returns	The bytes of this UID
	 */
	const std::vector<uint8_t> &GetId() const {
		return m_id;
	}

	/**
	 *  Set the UID from bytes
	 *
	 *  @param  id	The bytes of this UID
	 */
	void SetId(const std::vector<uint8_t> &id) {
		m_id = id;
	}

	/**
	 *  Compares to the given object
	 *  
	 *  @param  rhs	The object to compare
	 *  @returns	1 if this UID > rhs, 2 if rhs > this UID, 0 if rhs == this UID 
	 */
	int Compare(const Object &rhs) const override {
		if(!rhs.InstanceOf<UserUID>())
			return Object::Compare(rhs);

		const UserUID &uid = static_cast<const UserUID&>(rhs);

		if(m_id < uid.m_id)
			return -1;
		else if(m_id > uid.m_id)
			return 1;

		return 0;
	}

	/**
	 *  Write UID out to stream in the form "[UserUID: id]"
	 *
	 *  @param  os	ostream
	 *  @return The stream
	 */
	std::ostream &WriteTo(std::ostream &os) const override
	{
		std::ostream::fmtflags prevFlags(os.flags());

		os << "[UserUID:" << std::hex << std::noshowbase << std::setfill('0');
		for (uint8_t digit : m_id)
		{
			os << std::setw(2) << static_cast<int>(digit);
		}

		os.flags(prevFlags);
		return os << ']';
	}

private:
	std::vector<uint8_t> m_id;
};

} } }
