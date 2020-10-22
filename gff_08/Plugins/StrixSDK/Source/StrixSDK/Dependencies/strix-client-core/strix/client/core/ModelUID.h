#pragma once

#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace core {

/**
 *  A UID of a model in Strix
 */
class ModelUID : public UID
{
public:
	STRIX_CLASS(ModelUID, UID)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.ModelUID")
		STRIX_PROPERTY(m_modelClass)
		STRIX_PROPERTY(m_primaryKey)
	)

	ModelUID() {}

	virtual ~ModelUID() {}

	/**
	 *  Get the MetaClass of the model this UID belongs to
	 *  
	 *  @returns	The class of the model
	 */
	const strix::net::object::MetaClass &GetModelClass() const {
	return *m_modelClass;
	}

	/**
	 *  Set the MetaClass of the model this UID belongs to
	 *
	 *  @param  modelClass	The class of the model
	 */
	void SetModelClass(const strix::net::object::MetaClass &modelClass) {
	    m_modelClass = &modelClass;
	}

	/**
	 *  Get the primary key (ID)
	 *  
	 *  @returns	The key
	 */
	long long GetPrimaryKey() const	{
		return m_primaryKey;
	}

	/**
	 *  Set the primary key (ID)
	 *
	 *  @param  primaryKey	The key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Compares to the given object
	 *
	 *  @param  rhs	The object to compare
	 *  @returns	1 if this UID > rhs, 2 if rhs > this UID, 0 if rhs == this UID.
	 *		If rhs is a ModelUID of the model class, then returns the difference between the UIDs.
	 *		If rhs is a ModelUID of a different class, returns -1
	 */
	int Compare(const Object &rhs) const override {
		if(!rhs.InstanceOf<ModelUID>())
			return Object::Compare(rhs);

		const ModelUID &uid = static_cast<const ModelUID&>(rhs);

		if(m_modelClass < uid.m_modelClass)
			return -1;
		if(m_modelClass > uid.m_modelClass)
			return -1;

		return m_primaryKey - uid.m_primaryKey;
	}

private:
	const strix::net::object::MetaClass *m_modelClass;
	long long m_primaryKey;
};

} } }
