#pragma once

#include <map>
#include <memory>

namespace strix { namespace client { namespace replica { namespace model {

class Replica;
typedef std::shared_ptr<Replica> ReplicaPtr;

} } } }

namespace strix { namespace client { namespace replica {

/**
 *  Holds a map of replica ids to replicas
 */
class ReplicaData
{
public:
	virtual ~ReplicaData() = default;

	/**
	 *  Clear the internal map
	 */
	virtual void Reset() = 0;

	/**
	 *  Set a replica in the map with the given key
	 *  @param	id	The key
	 *  @param	replica	The replica to add
	 */
	virtual void SetReplicaById(long long id, model::ReplicaPtr replica) = 0;

	/**
	 *  Get a replica given an id
	 *  @param	id	The key
	 *  @returns	The replica with that id
	 */
	virtual model::ReplicaPtr GetReplicaById(const long long &id) = 0;

	/**
	 *  Remove a replica with the given id
	 *  @param	id	The key
	 */
	virtual void RemoveReplicaById(const long long &id) = 0;

	/**
	 *  Get the internal map of ids to replicas
	 *  @returns	The map of ids (long long) to replicas (ReplicaPtr)
	 */
	virtual std::map<long long, model::ReplicaPtr> &GetReplicaByIdMap() = 0;
};

/**
 *  The default implementation of ReplicaData
 */
class DefaultReplicaData : public ReplicaData
{
public:
	DefaultReplicaData();

	/**
	 *  Clear the internal map
	 */
	virtual void Reset() override;

	/**
	 *  Set a replica in the map with the given key
	 *  @param	id	The key
	 *  @param	replica	The replica to add
	 */
	virtual void SetReplicaById(long long id, model::ReplicaPtr replica) override;

	/**
	 *  Get a replica given an id
	 *  @param	id	The key
	 *  @returns	The replica with that id
	 */
	virtual model::ReplicaPtr GetReplicaById(const long long &id) override;

	/**
	 *  Remove a replica with the given id
	 *  @param	id	The key
	 */
	virtual void RemoveReplicaById(const long long &id) override;

	/**
	 *  Get the internal map of ids to replicas
	 *  @returns	The map of ids (long long) to replicas (ReplicaPtr)
	 */
	virtual std::map<long long, model::ReplicaPtr> &GetReplicaByIdMap() override;

private:
	std::map<long long, model::ReplicaPtr> m_replicaById;
};

typedef std::shared_ptr<ReplicaData> ReplicaDataPtr;

} } }	