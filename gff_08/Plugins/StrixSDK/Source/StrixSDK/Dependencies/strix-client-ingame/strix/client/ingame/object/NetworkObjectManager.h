#pragma once

#include <strix/client/core/NotificationEventArgs.h>
#include <strix/client/core/util/Delegates.h>

#include <memory>
#include <set>

namespace strix {namespace client {namespace match {
class MatchRoomClient;
typedef std::shared_ptr<MatchRoomClient> MatchRoomClientPtr;
} } }

namespace strix {namespace client {namespace replica {
class ReplicaClient;
typedef std::shared_ptr<ReplicaClient> ReplicaClientPtr;
} } }

namespace strix {namespace client {namespace replica {namespace message {
class ReplicaCreateNotification;
class ReplicaSetNotification;
class ReplicaDeleteNotification;
class ReplicaChangeOwnerNotification;
typedef std::shared_ptr<ReplicaCreateNotification> ReplicaCreateNotificationPtr;
typedef std::shared_ptr<ReplicaSetNotification> ReplicaSetNotificationPtr;
typedef std::shared_ptr<ReplicaDeleteNotification> ReplicaDeleteNotificationPtr;
typedef std::shared_ptr<ReplicaChangeOwnerNotification> ReplicaChangeOwnerNotificationPtr;
} } } }

namespace strix {namespace client {namespace replica {namespace model {
class Replica;
typedef std::shared_ptr<Replica> ReplicaPtr;
} } } }

namespace strix {namespace client {namespace ingame {namespace sync {
class PropertyMap;
}}}}

namespace strix { namespace client { namespace ingame { namespace object {

class NetworkObject;
class NetworkObjectSpawner;
typedef std::shared_ptr<NetworkObject> NetworkObjectPtr;
typedef std::shared_ptr<NetworkObjectSpawner> NetworkObjectSpawnerPtr;

enum InstantiableBy : int;
enum ConnectionClosedBehaviour : int;

/**
 *  Controller of network objects. Controls network object creation and property updates
 */
class NetworkObjectManager : public std::enable_shared_from_this<NetworkObjectManager>
{
public:
	NetworkObjectManager(match::MatchRoomClientPtr roomClient, replica::ReplicaClientPtr replicaClient, bool notificationsPaused);
	virtual ~NetworkObjectManager();

	/**
	 *  Process the pending operations of this network object manager
	 */
	void Process();

	/**
	 *  Destroys network objects
	 */
	void CleanUpInstances();

	/**
	 *  Set whether to destroy local objects on cleanup
	 *  @param	destroyLocalObjectsOnCleanUp	value
	 */
	void SetDestroyLocalObjectsOnCleanUp(bool destroyLocalObjectsOnCleanUp);

	/**
	 *  Get whether to destroy local objects on cleanup
	 *  @returns	value
	 */
	bool GetDestroyLocalObjectsOnCleanUp();

	/**
	 *  Set whether to destroy remote objects on cleanup
	 *  @param	destroyRemoteObjectsOnCleanUp	value
	 */
	void SetDestroyRemoteObjectsOnCleanUp(bool destroyRemoteObjectsOnCleanUp);

	/**
	 *  Get whether to destroy remote objects on cleanup
	 *  @returns	value
	 */
	bool GetDestroyRemoteObjectsOnCleanUp();

	/**
	 *  Find the network object spawner of the given object type
	 *  @param	typeId	The type of the object
	 *  @returns	The spawner for the object type
	 */
	NetworkObjectSpawnerPtr FindSpawner(int typeId);

	/**
	 *  Register a spawner as the spawner for the given object type
	 *  @param	typeId	The object type
	 *  @param	type	The object spawner
	 */
	void RegisterSpawner(int typeId, NetworkObjectSpawnerPtr type);

	/**
	 *  Deregister a spawner
	 *  @param	The object type to deregister the spawner of
	 */
	void DeregisterSpawner(int typeId);

	/**
	 *  Check if this client can instantiate objects under the given instantiable by condition
	 *  @param	instantiableBy	Room Owner Only or Anyone
	 *  @returns	True if instantiableBy is Anyone, or if this client is the current room owner and instantiableBy is RoomOwnerOnly
	 */
	bool CanInstantiate(InstantiableBy instantiableBy);

	/**
	 *  Add a local network object instance. This requests the object be replicated on other clients
	 *  @param	networkObject	The network object to add
	 */
	void AddLocalInstance(NetworkObjectPtr networkObject);

	/**
	 *  Add a remote network object instance. This is a replicated object that this manager should create on this client.
	 *  This requires a network object spawner be registered for this object type
	 *  @param	replica	The replica to add
	 */
	void AddRemoteInstance(client::replica::model::ReplicaPtr replica);

	/**
	 *  Get the network object with the given network instance ID
	 *  @param	networkInstanceId	The network instance ID
	 *  @returns	The network object
	 */
	NetworkObjectPtr FindInstance(long long networkInstanceId);

	/**
	 *  Called when the server has responded that the network object create request succeeded
	 *  @param	networkObject	The network object that was replicated
	 *  @param	replica	The representation of the replica
	 */
	void OnNetworkObjectCreateResponse(NetworkObjectPtr networkObject, replica::model::ReplicaPtr replica);
	/**
	 *  Called when the network object given has had its properties changed and these changes need to be replicated on this client
	 *  @param	networkObject	The network object that changed
	 *  @param	changedProperties	The properties that changed
	 */
	void OnNetworkObjectPropertiesChanged(NetworkObjectPtr networkObject, const sync::PropertyMap &changedProperties);

	/**
	 *  Called when a network object was destroyed
	 *  @param	networkObject	The network object that was destroyed
	 *  @param	originatedFromRemote	Whether the destroy command came from remote
	 */
	void OnNetworkObjectDestroyed(NetworkObjectPtr networkObject, bool originatedFromRemote);

	/**
	 *  Called when a replica was created on another client. Adds a remote instance on this client
	 *  @param	eventArgs	The event information
	 */
	void OnReplicaCreateNotification(core::NotificationEventArgs<client::replica::message::ReplicaCreateNotificationPtr> eventArgs);

	/**
	 *  Called when a replica's properties were set on another client. Updates this clients replicas
	 *  @param	eventArgs	The event information
	 */
	void OnReplicaSetNotification(core::NotificationEventArgs<client::replica::message::ReplicaSetNotificationPtr> eventArgs);

	/**
	 *  Called when a replica was deleted on another client. Deletes the remote instance on this client
	 *  @param	eventArgs	The event information
	 */
	void OnReplicaDeleteNotification(core::NotificationEventArgs<client::replica::message::ReplicaDeleteNotificationPtr> eventArgs);

	/**
	 *  Called when a replica changed ownership on another client. Updates the ownership of the replica on this client
	 *  @param	eventArgs	The event information
	 */
	void OnReplicaChangeOwnerNotification(core::NotificationEventArgs<client::replica::message::ReplicaChangeOwnerNotificationPtr> eventArgs);

	/**
	 *  Pause the network object manager events (but keeps track of the objects)
	 *  @remark Experimental, use with care.
	 */
	void Pause();

	/**
	 *  Unpause the network object manager events (respawning the stored objects)
	 *  @remark Experimental, use with care.
	 */
	void Unpause();

	/**
	 *  Checks the paused state of this network object manager
	 *  @returns	True if paused, else False
	 */
	bool IsPaused();

private:
	void RegisterEventHandlers();
	void DeregisterEventHandlers();

	bool m_destroyLocalObjectsOnCleanUp;
	bool m_destroyRemoteObjectsOnCleanUp;
	bool m_isCleanupInProgress;
	bool m_isPaused;

    std::weak_ptr<match::MatchRoomClient> m_roomClient;
    std::weak_ptr<replica::ReplicaClient> m_replicaClient;
	std::map<long long, NetworkObjectPtr> m_networkObjects;
	std::map<int, NetworkObjectSpawnerPtr> m_networkObjectSpawners;

	std::set<NetworkObjectPtr> m_pendingLocalObjects;

	core::util::DelegateList<>::Handle m_replicaCreateDelegateHandle;
	core::util::DelegateList<>::Handle m_replicaDeleteDelegateHandle;
	core::util::DelegateList<>::Handle m_replicaSetDelegateHandle;
	core::util::DelegateList<>::Handle m_replicaChangeOwnerDelegateHandle;
};

} } } }
