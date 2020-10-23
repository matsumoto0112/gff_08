#pragma once

#include <memory>

namespace strix { namespace client { namespace ingame { namespace object {

class NetworkObject;
typedef std::shared_ptr<NetworkObject> NetworkObjectPtr;

/**
 *  Creates replicated instances of ingame objects
 */
class NetworkObjectSpawner : public std::enable_shared_from_this<NetworkObjectSpawner> {
public:
	virtual ~NetworkObjectSpawner();

	/**
	 *  Create a network object using this spawner
	 *  @returns	The created network object
	 */
	virtual NetworkObjectPtr CreateInstance() = 0;

	/**
	 *  Create a network object in 'paused' state using this spawner
	 *  @returns	The created network object
	 */
	virtual NetworkObjectPtr CreatePausedInstance() = 0;

	/**
	 *  Unpause a network object
	 *  @remark Spawner is necessary because in some engines this means recreating the engine-specific object.
	 */
	virtual void UnpauseInstance(NetworkObjectPtr networkObject) = 0;
};

typedef std::shared_ptr<NetworkObjectSpawner> NetworkObjectSpawnerPtr;

} } } }
