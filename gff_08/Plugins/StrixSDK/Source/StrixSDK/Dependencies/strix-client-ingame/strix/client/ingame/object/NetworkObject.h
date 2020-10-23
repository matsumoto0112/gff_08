#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/util/Delegates.h>
#include <strix/client/ingame/sync/PropertyMap.h>

#include <functional>
#include <memory>
#include <vector>

namespace strix { namespace client { namespace replica { namespace model {
class Replica;
typedef std::shared_ptr<Replica> ReplicaPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace sync {
class PropertyMap;
class SyncGroup;
typedef std::shared_ptr<SyncGroup> SyncGroupPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace object {
	
class NetworkObject;
typedef std::shared_ptr<NetworkObject> NetworkObjectPtr;

enum InstantiableBy : int;
enum ConnectionClosedBehaviour : int;

/**
 *  An object in the game exposed to the Strix engine
 *  
 *  Network objects are the underlying representation of game objects 
 *  that have been provided network functionality. They can be manipulated and 
 *  replicated by Strix
 */
class NetworkObject : public std::enable_shared_from_this<NetworkObject> {
public:
	NetworkObject();
	virtual ~NetworkObject();

	/**
	 *  Initialize the network object
	 */
	void Init();

	/** Unpauses this network object, forcing the initialization, setting it to replicate and immediately applying stored properties
	 *  @remark	This should be called by the spawner (could contain more engine-specific logic, for example engine object creation)
	 */
	void Unpause();

	/**
	 *  Destroy the network instance. This sets this object to uninitialized and triggers destroy handlers
	 *  @param	originatedFromRemote	True if the destroy command came from the remote object
	 */
	void DestroyNetworkInstance(bool originatedFromRemote);

	/**
	 *  Calls DestroyNetworkInstance(true). Override to provide implementation defined functionality for destroying the object
	 */
	virtual void DestroyObject();

	/**
	 *  Get the type flags for this object (instantiable by and connection closed behaviour)
	 *  @returns	The flags as an int
	 */
	int GetTypeFlags() const;

	/**
	 *  Get the ID of this network instance
	 *  @returns	The instance ID or -1 if this object is not replicated
	 */
	long long GetNetworkInstanceId() const;

	/**
	 *  Get the type ID of this object. Override to define an implementation specific method of getting the type ID
	 *  @returns	The type ID
	 */
	virtual int GetTypeId() const = 0;

	/**
	 *  Check if this object should receive remote destroy events, i.e, if it can be destroyed by commands from it's replicas
	 *  @returns	The value
	 */
	virtual bool GetShouldReceiveRemoteDestroyEvent() const = 0;

	/**
	 *  Get the clients that can instantiate this object. Either the room owner, or anyone
	 *  @returns	The value
	 */
	virtual InstantiableBy GetInstantiableBy() const = 0;

	/**
	 *  Get the behaviour of this object on connection closed. Either change owner, or delete
	 *  @returns	The value
	 */
	virtual ConnectionClosedBehaviour GetConnectionClosedBehaviour() const = 0;

	/**
	 *  Set if the local client is the owner of this network object
	 *  @param	isOwner	The value to set
	 */
	void SetIsOwner(bool isOwner);

	/**
	 *  Get if the local client is the owner of this network object
	 *  @returns	True if owner
	 */
	bool IsOwner() const;

	/**
	 *  Get if this object is being replicated
	 *  @returns	True if replicating
	 */
	bool IsReplicating() const;

	/**
	 *  Get if the local client is the owner of this network object and the object is replicating
	 *  @returns	True if is owner and replicating
	 */
	bool IsOwnerAndReplicating() const;

	/**
	 *  Get if this network object is instantiated 
	 *  @returns	True if instantiated
	 */
	bool IsInstantiated() const;

	/**
	 *  Get this object's owner's UID
	 *  @returns	The owner's UID, or null if this object is not being replicated
	 */
	client::core::UIDPtr GetOwnerUid() const;

	/**
	 *  Set the sync properties of this network object to the new values 
	 *  @param	properties	The map of sync properties
	 *  @param	forceApplyAll	If true, force update all sync groups regardless of whether they set to receive changes
	 */
	virtual void ApplyProperties(const sync::PropertyMap &properties, bool forceApplyAll = false);

	/**
	 *  Get the current properties of this network object
	 *  @param	forceCollectAll	If true, force collect from all sync groups regardless of whether they are set to propagate changes
	 */
	virtual sync::PropertyMap CollectProperties(bool forceCollectAll = false) const;

	/**
	 *  Get the representation of the replica of this object
	 *  @returns	The replica
	 */
	const client::replica::model::ReplicaPtr &GetReplica() const;

	/**
	 *  Set the representation of the replica of this object
	 *  @param	replica	The representation of the replica of this object
	 */
	void SetReplica(client::replica::model::ReplicaPtr replica);

	/**
	 *  Add a sync group to this object
	 *  @param	syncGroup	The sync group
	 */
	void AddSyncGroup(sync::SyncGroupPtr syncGroup);

	/**
	 *  Remove a sync group from this object
	 *  @param	syncGroup	The sync group to remove
	 */
	void RemoveSyncGroup(sync::SyncGroupPtr syncGroup);

	/**
	 *  Add a handler to be called when this object is destroyed
	 *  The handler is a function that takes a NetworkObjectPtr (this object) and a bool (whether the destroy originated from remote)
	 *  @param	onDestroyHandler	The handler
	 *  @returns	The key to the new handler 
	 */
	core::util::DelegateList<>::Handle AddOnDestroyHandler(std::function<void(NetworkObjectPtr, bool)> onDestroyHandler);

	/**
	 *  Remove a handler from the destroy handler list
	 *  @param	delegateHandle	The key to the handler
	 */
	void RemoveOnDestroyHandler(core::util::DelegateList<>::Handle delegateHandle);

protected:

	/**
	 *  Called on initialization. Override to provide the initialization of the object
	 */
	virtual void InitObject() = 0;

	/**
	 *  Called on synchronization. Override to perform actions when the object starts replication
	 */
	virtual void OnSyncObject() = 0;

	/**
	 *  Called when the owner of this object changes. Override to perform action when ownership changes
	 */
	virtual void OnOwnershipReceived() = 0;

	/**
	 *  Trigger destroy handlers
	 *  @param	originatedFromRemote	Whether the destroy command came from the replica
	 */
	void FireOnDestroyEvent(bool originatedFromRemote);

	bool m_isOwner;
	bool m_isInstantiated;

	client::replica::model::ReplicaPtr m_replica;
	std::vector<sync::SyncGroupPtr> m_syncGroups;

	core::util::DelegateList<NetworkObjectPtr, bool> m_onDestroyDelegate;
};

} } } }
