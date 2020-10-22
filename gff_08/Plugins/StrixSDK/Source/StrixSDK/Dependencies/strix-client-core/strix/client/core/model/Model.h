#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace model {

/**
 *  Base class of a model
 */
class Model : public strix::net::object::Object
{
public:
	STRIX_ABSTRACT_CLASS(Model, strix::net::object::Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.Model")
	)

    /**
     *  Get the primary key
     *  @returns	The primary key
     */
    virtual long long GetPrimaryKey() const = 0;

    /**
     *  Set the primary key
     *  @param	id	The primary key
     */
    virtual void SetPrimaryKey(long long id) = 0;
};

typedef std::shared_ptr<Model> ModelPtr;

} } } }
