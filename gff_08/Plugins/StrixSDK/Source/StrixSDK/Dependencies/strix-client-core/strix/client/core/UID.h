#pragma once

#include <strix/net/object/Object.h>

#include <ostream>

namespace strix { namespace client { namespace core {

/**
 *  Abstract class for unique identifiers
 */
class UID : public strix::net::object::Object
{
public:
	STRIX_ABSTRACT_CLASS(UID, strix::net::object::Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.UID")
	)

	virtual ~UID() {}

	/**
	 *  Write UID out to stream
	 *  
	 *  @param  os	ostream
	 *  @return The stream
	 */
	virtual std::ostream & WriteTo(std::ostream &os) const = 0;

	friend std::ostream & operator<<(std::ostream &os, const UID &obj)
	{
		return obj.WriteTo(os);
	}

protected:
	UID() {}
};

typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

} } }
