/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "StrixNetworkFacade.h"
#include "Adapter/StrixRoom.h"
#include "Adapter/StrixRoomMember.h"
#include "Components/ActorComponent.h"

#include <strix/client/core/NotificationEventArgs.h>
#include <strix/client/core/util/Delegates.h>

#include "StrixNotificationListener.generated.h"

namespace strix { namespace client { namespace room { namespace message {
class RoomJoinNotification;
class RoomLeaveNotification;
class RoomDeleteNotification;
class RoomSetNotification;
class RoomSetMemberNotification;
class RoomRelayNotification;
class RoomDirectRelayNotification;
typedef std::shared_ptr<RoomJoinNotification> RoomJoinNotificationPtr;
typedef std::shared_ptr<RoomLeaveNotification> RoomLeaveNotificationPtr;
typedef std::shared_ptr<RoomDeleteNotification> RoomDeleteNotificationPtr;
typedef std::shared_ptr<RoomSetNotification> RoomSetNotificationPtr;
typedef std::shared_ptr<RoomSetMemberNotification> RoomSetMemberNotificationPtr;
typedef std::shared_ptr<RoomRelayNotification> RoomRelayNotificationPtr;
typedef std::shared_ptr<RoomDirectRelayNotification> RoomDirectRelayNotificationPtr;
} } } }

namespace strix { namespace client { namespace match { namespace room { namespace message {
class MatchRoomKickNotification;
typedef std::shared_ptr<MatchRoomKickNotification> MatchRoomKickNotificationPtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace network {
class RoomContext;
typedef std::shared_ptr<RoomContext> RoomContextPtr;
} } } }

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStrixNotifierRoomContextOpenDelegate, int32, channelId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStrixNotifierRoomJoinNotificationDelegate, int32, channelId, const FStrixRoomMember&, roomMember);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStrixNotifierRoomLeaveNotificationDelegate, int32, channelId, const FStrixRoomMember&, roomMember);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStrixNotifierRoomSetNotificationDelegate, int32, channelId, const FStrixRoom&, roomMember);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStrixNotifierRoomSetMemberNotificationDelegate, int32, channelId, const FStrixRoomMember&, roomMember);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStrixNotifierRoomKickNotificationDelegate, int32, channelId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStrixNotifierRoomDeleteNotificationDelegate, int32, channelId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStrixNotifierRoomContextClosedDelegate, int32, channelId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStrixNotifierRoomOwnerChangedNotificationDelegate, int32, channelId, const FStrixRoomMember&, newOwner, const FStrixRoomMember&, previousOwner);

/** Component used for easy management of the callbacks (functions)
 *  executed when a notification arrives on the specified channel.
 *  
 *  Does not have to be attached to a replicator for use.
 */
 /// \cond
UCLASS(ClassGroup = (Strix), meta = (BlueprintSpawnableComponent))
/// \endcond
class STRIXSDK_API UStrixNotificationListener : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Delegate called when room context was opened
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomContextOpenDelegate StrixRoomContextOpen;

	/** Delegate called when room join notification was received
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomJoinNotificationDelegate StrixRoomJoinNotificationArrived;

	/** Delegate called when room leave notification was received
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomLeaveNotificationDelegate StrixRoomLeaveNotificationArrived;

	/** Delegate called when room set notification was received
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomSetNotificationDelegate StrixRoomSetNotificationArrived;

	/** Delegate called when room set member notification was received
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomSetMemberNotificationDelegate StrixRoomSetMemberNotificationArrived;

	/** Delegate called when room kick notification was received
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomKickNotificationDelegate StrixRoomKickNotificationArrived;

	/** Delegate called when room delete notification was received
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomDeleteNotificationDelegate StrixRoomDeleteNotificationArrived;

	/** Delegate called when room context was closed
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomContextClosedDelegate StrixRoomContextClosed;

	/** Delegate called when the room owner changes
	 */
	UPROPERTY(BlueprintAssignable, Category = "Strix|Notifications")
	FStrixNotifierRoomOwnerChangedNotificationDelegate StrixRoomOwnerChanged;

	/** Channel Id to use
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "Strix Notifier")
	int32 ChannelId;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Stops this notification listener, removing the registered callbacks
	 *  so that the delegates won't be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Strix|Notifications")
	void StopNotificationListener();

protected:
	void BeginPlay() override;

private:
	/** Callback executed when room join notification is received.
	 *  Propagates the received event to blueprints.
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomJoinNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomJoinNotificationPtr> args);

	/** Callback executed when room leave notification is received.
	 *  Propagates the received event to blueprints.
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomLeaveNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomLeaveNotificationPtr> args);

	/** Callback executed when room set notification is received.
	 *  Propagates the received event to blueprints.
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomSetNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomSetNotificationPtr> args);

	/** Callback executed when room set notification is received
	 *  Propagates the received event to blueprints if the room owner has changed
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomChangeOwnerNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomSetNotificationPtr> args);

	/** Callback executed when room set member notification is received.
	 *  Propagates the received event to blueprints.
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomSetMemberNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomSetMemberNotificationPtr> args);

	/** Callback executed when match room kick notification is received.
	 *  Propagates the received event to blueprints.
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomKickNotification(strix::client::core::NotificationEventArgs<strix::client::match::room::message::MatchRoomKickNotificationPtr> args);

	/** Callback executed when room delete notification is received.
	 *  Propagates the received event to blueprints.
	 *  @param	args	Notification event arguments, containing the received notification
	 */
	void OnRoomDeleteNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomDeleteNotificationPtr> args);

	/** Callback executed when room context is opened.
	 *  Registers other callbacks on the newly opened context.
	 *  Only executes if the received channel id matches the one used
	 *  by this listener.
	 *  @param	channelId	Channel Id of the opened room context
	 *  @param	roomContext	Opened room context
	 */
	void OnRoomContextOpen(int channelId, strix::client::ingame::network::RoomContextPtr roomContext);

	/** Register event callbacks on the specified room context and
	 *  store the room context on this listener.
	 *  @param	roomContext	Room context to register the callbacks on
	 */
	void StartNotificationListenerBase(strix::client::ingame::network::RoomContextPtr roomContext);

	strix::client::core::util::DelegateList<>::Handle m_roomJoinNotificationHandle;
	strix::client::core::util::DelegateList<>::Handle m_roomLeaveNotificationHandle;
	strix::client::core::util::DelegateList<>::Handle m_roomSetNotificationHandle;
	strix::client::core::util::DelegateList<>::Handle m_roomSetMemberNotificationHandle;
	strix::client::core::util::DelegateList<>::Handle m_roomKickNotificationHandle;
	strix::client::core::util::DelegateList<>::Handle m_roomDeleteNotificationHandle;
	strix::client::core::util::DelegateList<>::Handle m_roomOwnerChangedNotificationHandle;

	strix::client::core::util::DelegateList<>::Handle m_roomContextOpenHandle;

	std::weak_ptr<strix::client::ingame::network::RoomContext> m_roomContext;

	bool m_isActive = false;
};
