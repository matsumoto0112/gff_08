#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/node/model/Node.h>

namespace strix { namespace client { namespace match { namespace node { namespace model {

/**
 *  Represents a match server
 */
class MatchServerNode : public strix::client::node::model::Node
{
public:
	STRIX_CLASS(MatchServerNode, Node)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.node.model.MatchServerNode")
		STRIX_PROPERTY(m_primaryKey)
	)

	MatchServerNode() {}

	virtual ~MatchServerNode() {}

	/**
	 *  Get this server's primary key
	 *  @returns	key
	 */
	virtual long long GetPrimaryKey() const {
		return m_primaryKey;
	}

	/**
	 *  Set this server's primary key
	 *  @param	id	key
	 */
	virtual void SetPrimaryKey(long long id) {
		m_primaryKey = id;
	}

private:
	long long m_primaryKey;
};

} } } } }
