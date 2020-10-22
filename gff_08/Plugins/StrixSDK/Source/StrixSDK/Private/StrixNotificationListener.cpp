/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "StrixNotificationListener.h"

#include "StrixNetworkFacade.h"
#include "UELogHandler.h"

#include <strix/client/ingame/network/RoomContext.h>
#include <strix/client/ingame/network/StrixNetworkEvents.h>
#include <strix/client/match/MatchMessages.h>
#include <strix/client/room/RoomMessages.h>
#include "strix/client/match/CustomizableMatchRoomClient.h"

void UStrixNotificationListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UActorComponent::EndPlay(EndPlayReason);

	StopNotificationListener();
}

void UStrixNotificationListener::StopNotificationListener()
{
	if (!m_isActive)
	{
		return;
	}

	auto roomContext = m_roomContext.lock();
	if (roomContext && roomContext->GetMatchRoomClient())
	{
		roomContext->GetMatchRoomClient()->RemoveRoomJoinNotifiedHandler(m_roomJoinNotificationHandle);
		roomContext->GetMatchRoomClient()->RemoveRoomLeaveNotifiedHandler(m_roomLeaveNotificationHandle);
		roomContext->GetMatchRoomClient()->RemoveRoomSetNotifiedHandler(m_roomSetNotificationHandle);
		roomContext->GetMatchRoomClient()->RemoveRoomSetMemberNotifiedHandler(m_roomSetMemberNotificationHandle);
		roomContext->GetMatchRoomClient()->RemoveMatchRoomKickNotifiedHandler(m_roomKickNotificationHandle);
		roomContext->GetMatchRoomClient()->RemoveRoomDeleteNotifiedHandler(m_roomDeleteNotificationHandle);
		roomContext->GetMatchRoomClient()->RemoveRoomChangeOwnerNotifiedHandler(m_roomOwnerChangedNotificationHandle);

		roomContext->RemoveRoomContextInvalidateHandler(m_roomContextOpenHandle);

		StrixRoomContextClosed.Broadcast(ChannelId);

		m_isActive = false;
	}
}

void UStrixNotificationListener::BeginPlay()
{
	UActorComponent::BeginPlay();

	if (m_isActive)
	{
		UE_LOG(LogStrix, Log, TEXT("StrixNotificationListener::Start - Strix notification listener is already active."));
		return;
	}

	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(this);

	if (strixNetwork)
	{
		auto roomContext = strixNetwork->GetRoomContextByChannelId(ChannelId);

		if (roomContext && roomContext->GetMatchRoomClient())
		{
			StartNotificationListenerBase(roomContext);
		}
		else
		{
			m_roomContextOpenHandle = strixNetwork->AddRoomContextOpenHandler(
				strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomContextOpen));
		}
	}
	else
	{
		UE_LOG(LogStrix, Log, TEXT("StrixNotificationListener::Start - Strix network is not initialized."));
	}
}

void UStrixNotificationListener::OnRoomJoinNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomJoinNotificationPtr> args)
{
	auto roomMember = args.m_data->GetNewlyJoinedMember();
	if (roomMember->InstanceOf<strix::client::match::room::model::CustomizableMatchRoomMember>())
	{
		auto customizableMatchRoomMember = std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(roomMember);
		StrixRoomJoinNotificationArrived.Broadcast(ChannelId, FStrixRoomMember(customizableMatchRoomMember));
	}
}

void UStrixNotificationListener::OnRoomLeaveNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomLeaveNotificationPtr> args)
{
	auto roomMember = args.m_data->GetGoneMember();
	if (roomMember->InstanceOf<strix::client::match::room::model::CustomizableMatchRoomMember>())
	{
		auto customizableMatchRoomMember = std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(roomMember);
		StrixRoomLeaveNotificationArrived.Broadcast(ChannelId, FStrixRoomMember(customizableMatchRoomMember));
	}
}

void UStrixNotificationListener::OnRoomSetNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomSetNotificationPtr> args)
{
	auto room = args.m_data->GetRoom();
	if (room->InstanceOf<strix::client::match::room::model::CustomizableMatchRoom>())
	{
		auto customizableMatchRoom = std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoom>(room);
		StrixRoomSetNotificationArrived.Broadcast(ChannelId, FStrixRoom(customizableMatchRoom));
	}
}

void UStrixNotificationListener::OnRoomChangeOwnerNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomSetNotificationPtr> args)
{
	auto room = args.m_data->GetRoom();
	if(auto matchRoom = std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoom>(room))
	{
		auto strixNetwork = UStrixNetworkFacade::GetInstance(this);
		if(!strixNetwork)
		{
			UE_LOG(LogStrix, Warning, TEXT("Network not initialized for OnRoomChangeOwnerNotification"));
			return;
		}

		auto members = strixNetwork->GetRoomContextByChannelId(ChannelId)->GetRoomData()->GetRoomMembers();

		const auto roomOwner = std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(members[matchRoom->GetOwnerUid()]);

		const auto previousRoomOwner = std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(members[
		    std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoom>(
			    strixNetwork->GetRoomContextByChannelId(ChannelId)->GetRoomData()->GetRoom())->GetOwnerUid()
		]);

		if(roomOwner && previousRoomOwner)
		{
		    StrixRoomOwnerChanged.Broadcast(ChannelId, FStrixRoomMember(roomOwner), FStrixRoomMember(previousRoomOwner));
		}
	}
}

void UStrixNotificationListener::OnRoomSetMemberNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomSetMemberNotificationPtr> args)
{
	auto roomMember = args.m_data->GetMember();
	if (roomMember->InstanceOf<strix::client::match::room::model::CustomizableMatchRoomMember>())
	{
		auto customizableMatchRoomMember = std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(roomMember);
		StrixRoomSetMemberNotificationArrived.Broadcast(ChannelId, FStrixRoomMember(customizableMatchRoomMember));
	}
}

void UStrixNotificationListener::OnRoomKickNotification(strix::client::core::NotificationEventArgs<strix::client::match::room::message::MatchRoomKickNotificationPtr> args)
{
	StrixRoomKickNotificationArrived.Broadcast(ChannelId);
}

void UStrixNotificationListener::OnRoomDeleteNotification(strix::client::core::NotificationEventArgs<strix::client::room::message::RoomDeleteNotificationPtr> args)
{
	StrixRoomDeleteNotificationArrived.Broadcast(ChannelId);
}

void UStrixNotificationListener::OnRoomContextOpen(int channelId, strix::client::ingame::network::RoomContextPtr roomContext)
{
	if (channelId == ChannelId)
	{
		StartNotificationListenerBase(roomContext);
		StrixRoomContextOpen.Broadcast(channelId);

		roomContext->RemoveRoomContextInvalidateHandler(m_roomContextOpenHandle);
	}
}

void UStrixNotificationListener::StartNotificationListenerBase(strix::client::ingame::network::RoomContextPtr roomContext)
{
	if (!roomContext->GetMatchRoomClient())
	{
		UE_LOG(LogStrix, Log, TEXT("StrixNotificationListener::OnRoomContextOpen - Match room client not initialized."));
		return;
	}

	m_roomJoinNotificationHandle = roomContext->GetMatchRoomClient()->AddRoomJoinNotifiedHandler(
		strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomJoinNotification));

	m_roomLeaveNotificationHandle = roomContext->GetMatchRoomClient()->AddRoomLeaveNotifiedHandler(
		strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomLeaveNotification));

	m_roomSetNotificationHandle = roomContext->GetMatchRoomClient()->AddRoomSetNotifiedHandler(
		strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomSetNotification));

	m_roomSetMemberNotificationHandle = roomContext->GetMatchRoomClient()->AddRoomSetMemberNotifiedHandler(
		strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomSetMemberNotification));

	m_roomKickNotificationHandle = roomContext->GetMatchRoomClient()->AddMatchRoomKickNotifiedHandler(
		strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomKickNotification));

	m_roomDeleteNotificationHandle = roomContext->GetMatchRoomClient()->AddRoomDeleteNotifiedHandler(
		strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomDeleteNotification));

	m_roomOwnerChangedNotificationHandle = roomContext->GetMatchRoomClient()->AddRoomChangeOwnerNotifiedHandler(
		strix::client::core::util::MethodBinding::BindRaw(this, &UStrixNotificationListener::OnRoomChangeOwnerNotification));

	roomContext->AddRoomContextInvalidateHandler(
		[this](strix::client::ingame::network::RoomContextInvalidateEventArgs args) {
			StopNotificationListener();
		}
	);

	m_roomContext = roomContext;
	m_isActive = true;
}