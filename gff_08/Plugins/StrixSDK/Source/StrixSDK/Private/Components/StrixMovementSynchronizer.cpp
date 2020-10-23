/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Components/StrixMovementSynchronizer.h"

#include "Movement/StrixLocalMovementController.h"
#include "Movement/StrixRemoteMovementController.h"
#include "Movement/StrixMovementSyncGroup.h"

#include "UELogHandler.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Serialization/UEObjectAdapter.h"
#include "Sync/UESyncProperties.h"
#include "Util/GlmHelper.h"
#include "Util/StrixUtil.h"

#include "TimerManager.h"

#include <strix/client/core/util/Delegates.h>
#include <strix/client/ingame/object/NetworkObject.h>
#include <strix/client/match/MatchRoomClient.h>

using namespace strix::client::ingame::interpolation;
using strix::client::core::util::MethodBinding;
using namespace strix::client::ingame::rpc;

const std::string UStrixMovementSynchronizer::PositionXPropertyName = "StrixMovementSynchronizer.PositionX";
const std::string UStrixMovementSynchronizer::PositionYPropertyName = "StrixMovementSynchronizer.PositionY";
const std::string UStrixMovementSynchronizer::PositionZPropertyName = "StrixMovementSynchronizer.PositionZ";
const std::string UStrixMovementSynchronizer::VelocityXPropertyName = "StrixMovementSynchronizer.VelocityX";
const std::string UStrixMovementSynchronizer::VelocityYPropertyName = "StrixMovementSynchronizer.VelocityY";
const std::string UStrixMovementSynchronizer::VelocityZPropertyName = "StrixMovementSynchronizer.VelocityZ";
const std::string UStrixMovementSynchronizer::RotationXPropertyName = "StrixMovementSynchronizer.RotationX";
const std::string UStrixMovementSynchronizer::RotationYPropertyName = "StrixMovementSynchronizer.RotationY";
const std::string UStrixMovementSynchronizer::RotationZPropertyName = "StrixMovementSynchronizer.RotationZ";
const std::string UStrixMovementSynchronizer::RotationWPropertyName = "StrixMovementSynchronizer.RotationW";

const std::string UStrixMovementSynchronizer::MoveRPCName = "StrixMovementSynchronizer.Move";
const std::string UStrixMovementSynchronizer::MoveRPCDirectName = "StrixMovementSynchronizer.MoveDirect";
const std::string UStrixMovementSynchronizer::JumpRPCName = "StrixMovementSynchronizer.Jump";
const std::string UStrixMovementSynchronizer::RequestDirectMoveRPCName = "StrixMovementSynchronizer.RequestRPC";

UStrixMovementSynchronizer::UStrixMovementSynchronizer()
	: NearDistance(2.0f),
	MaxSpeed(600),
	Acceleration(2048.0f),
	Damping(0.0f),
	SyncPeriodMin(100),
	SyncPeriodMax(500),
	ReachableDistance(400),
	MovementSyncType(EMovementSyncType::SyncProperties),
	SendRPCSpawn(true),
	SyncJump(true),
	SyncXVelocity(true),
	SyncYVelocity(true),
	SyncZVelocity(false),
	InterpolateRotation(true),
	m_replicator(nullptr),
	m_syncGroup(nullptr),
	m_roomJoinNotificationHandle(0),
	m_roomContextInvalidateHandle(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStrixMovementSynchronizer::BeginPlay()
{
	Super::BeginPlay();
	if (!Cast<APawn>(GetOwner()))
	{
		UE_LOG(LogStrix, Warning, TEXT("Strix movement synchronizer has been added to a non-pawn actor. It will not synchronize with smooth velocity"));
	}
	if (!m_pMovementController)
	{
		UStrixReplicatorComponent* replicator = GetOwner()->FindComponentByClass<UStrixReplicatorComponent>();
		if (replicator)
		{
			m_replicator = replicator;
			m_pMovementController = CreateMovementController();
			m_pMovementController->SetSyncPeriodMin(SyncPeriodMin);
			m_pMovementController->SetSyncPeriodMax(SyncPeriodMax);
			m_pMovementController->SetSyncX(SyncXVelocity);
			m_pMovementController->SetSyncY(SyncYVelocity);
			m_pMovementController->SetSyncZ(SyncZVelocity);
			m_pMovementController->SetSyncJump(SyncJump);
			m_pMovementController->SetInterpolateRotation(InterpolateRotation);

			m_replicator->OnSyncBegin.AddDynamic(this, &UStrixMovementSynchronizer::StartSync);

			if (!(MovementSyncType == EMovementSyncType::RPC))
			{
				CreatePropertiesSyncGroup();
			}
		}
	}
}

void UStrixMovementSynchronizer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!(MovementSyncType == EMovementSyncType::RPC) && m_syncGroup)
	{
		m_syncGroup->ClearPostApplyFunction();

		if (m_replicator)
		{
			m_replicator->RemoveSyncGroup(m_syncGroup);
		}
	}

	if (m_roomContextInvalidateHandle)
	{
		RemoveRoomContextInvalidateHandler();
	}

	m_replicator = nullptr;
}

void UStrixMovementSynchronizer::SetSyncPeriodMin(int periodMin)
{
	if (m_pMovementController)
	{
		m_pMovementController->SetSyncPeriodMin(periodMin);
	}
}

void UStrixMovementSynchronizer::SetSyncPeriodMax(int periodMax)
{
	if (m_pMovementController)
	{
		m_pMovementController->SetSyncPeriodMax(periodMax);
	}
}

void UStrixMovementSynchronizer::SetSyncJump(bool sync)
{
	if (m_pMovementController)
	{
		m_pMovementController->SetSyncJump(sync);
	}
}

void UStrixMovementSynchronizer::SetSyncXVelocity(bool sync)
{
	if (m_pMovementController)
	{
		m_pMovementController->SetSyncX(sync);
	}
}

void UStrixMovementSynchronizer::SetSyncYVelocity(bool sync)
{
	if (m_pMovementController)
	{
		m_pMovementController->SetSyncY(sync);
	}
}

void UStrixMovementSynchronizer::SetSyncZVelocity(bool sync)
{
	if (m_pMovementController)
	{
		m_pMovementController->SetSyncZ(sync);
	}
}

void UStrixMovementSynchronizer::SetInterpolateRotation(bool interpolate)
{
	if (m_pMovementController)
	{
		m_pMovementController->SetInterpolateRotation(interpolate);
	}
}

std::unique_ptr<movement::StrixMovementController> UStrixMovementSynchronizer::CreateMovementController()
{
	AActor *pActor = GetOwner();

	MovementInterpolator movementInterpolator(util::GlmHelper::Convert(pActor->GetActorLocation()));

	movementInterpolator.SetNearDistance(NearDistance);
	movementInterpolator.SetMaxSpeed(MaxSpeed);
	movementInterpolator.SetAcceleration(Acceleration);
	movementInterpolator.SetDamping(Damping);
	movementInterpolator.SetReachableDistance(ReachableDistance);

	if (m_replicator->GetIsOwner())
	{
		std::unique_ptr<movement::StrixLocalMovementController> pLocalMovementSynchronizer =
			std::make_unique<movement::StrixLocalMovementController>(pActor, movementInterpolator);

		return std::move(pLocalMovementSynchronizer);
	}
	else
	{
		std::unique_ptr<movement::StrixRemoteMovementController> pRemoteMovementSynchronizer =
			std::make_unique<movement::StrixRemoteMovementController>(pActor, movementInterpolator);

		return std::move(pRemoteMovementSynchronizer);
	}
}
void UStrixMovementSynchronizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pMovementController)
	{
		bool shouldSync = false;
		m_pMovementController->UpdateMovement(DeltaTime, shouldSync);
		if (shouldSync)
		{
			if (MovementSyncType == EMovementSyncType::RPC)
			{
				SendMoveRpcMessage();
			}
			else
			{
				PropagateSyncPropertyChanges();
			}
		}
	}
}

#if WITH_EDITOR

bool UStrixMovementSynchronizer::CanEditChange(const UProperty* InProperty) const
{
	const bool superValue = Super::CanEditChange(InProperty);

	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UStrixMovementSynchronizer, SendRPCSpawn))
		return superValue && MovementSyncType == EMovementSyncType::RPC;
	else
		return superValue;
}

#endif

void UStrixMovementSynchronizer::StartSync()
{
	const long long id = m_replicator->GetNetworkObject()->GetNetworkInstanceId();
	UStrixNetworkFacade* facade = UStrixNetworkFacade::GetInstance(this);

	if (facade)
	{
		if (MovementSyncType == EMovementSyncType::RPC)
		{
			facade->RegisterRpcProcedure(m_replicator->ChannelId, id, StrixUtil::MakeRpcProcedure(MoveRPCName, MethodBinding::BindRaw(this, &UStrixMovementSynchronizer::OnRpcMove)));
			facade->RegisterRpcProcedure(m_replicator->ChannelId, id, StrixUtil::MakeRpcProcedure(MoveRPCDirectName, MethodBinding::BindRaw(this, &UStrixMovementSynchronizer::OnRpcMoveDirect)));
			facade->RegisterRpcProcedure(m_replicator->ChannelId, id, StrixUtil::MakeRpcProcedure(RequestDirectMoveRPCName, MethodBinding::BindRaw(this, &UStrixMovementSynchronizer::RequestDirectMoveMessage)));

			if (SendRPCSpawn)
			{
				auto roomContext = facade->GetRoomContextByChannelId(m_replicator->ChannelId);
				if (roomContext)
				{
					m_roomJoinNotificationHandle = roomContext->GetMatchRoomClient()->AddRoomJoinNotifiedHandler(
						strix::client::core::util::MethodBinding::BindRaw(this, &UStrixMovementSynchronizer::OnRoomJoinNotification));

					m_roomContextInvalidateHandle = roomContext->AddRoomContextInvalidateHandler(
						[this](strix::client::ingame::network::RoomContextInvalidateEventArgs args) {
						RemoveRoomJoinNotificationHandler(args.GetRoomContext().lock());
					}
					);
				}

				if (m_replicator->GetIsOwnerAndReplicating())
				{
					SendDirectMoveRpcMessage();
				}
				else
				{
					facade->SendRpc(m_replicator->ChannelId, m_replicator->GetNetworkObject()->GetOwnerUid(), id, StrixUtil::GetHashValue(RequestDirectMoveRPCName), TArray<FStrixRelayArg>());
				}
			}
		}

		if (SyncJump)
		{
			facade->RegisterRpcProcedure(m_replicator->ChannelId, id, StrixUtil::MakeRpcProcedure(JumpRPCName, MethodBinding::BindRaw(this, &UStrixMovementSynchronizer::OnRpcJump)));

			if (m_replicator->GetIsOwner())
			{
				ACharacter* character = Cast<ACharacter>(GetOwner());
				if (character != nullptr)
				{
					character->MovementModeChangedDelegate.AddDynamic(this, &UStrixMovementSynchronizer::SendJumpRpcIfNecessary);
				}
			}
		}
	}
}

void UStrixMovementSynchronizer::SendJumpRpcIfNecessary(ACharacter* character, EMovementMode mode, uint8 v)
{
	if (m_replicator == nullptr || m_replicator->GetNetworkObject() == nullptr || !m_replicator->GetIsOwner())
	{
		return;
	}

	mode = character->GetCharacterMovement()->MovementMode;
	if (mode == EMovementMode::MOVE_Falling && character->bPressedJump)
	{
		auto strixNetwork = UStrixNetworkFacade::GetInstance(this);

		if (strixNetwork && m_replicator)
		{
			strixNetwork->SendRpcToOtherMembers(m_replicator->ChannelId, m_replicator->GetNetworkObject()->GetNetworkInstanceId(), StrixUtil::GetHashValue(JumpRPCName), TArray<FStrixRelayArg>());
		}
	}
}

void UStrixMovementSynchronizer::SendMoveRpcMessage()
{
	auto strixNetwork = UStrixNetworkFacade::GetInstance(this);

	if (strixNetwork && m_replicator && m_replicator->GetIsOwnerAndReplicating())
	{
		TArray<FStrixRelayArg> relayArgs;
		FillMoveRelayArguments(relayArgs);

		strixNetwork->SendRpcToOtherMembers(m_replicator->ChannelId, m_replicator->GetNetworkObject()->GetNetworkInstanceId(), StrixUtil::GetHashValue(MoveRPCName), relayArgs);
	}
}

void UStrixMovementSynchronizer::SendDirectMoveRpcMessage()
{
	auto strixNetwork = UStrixNetworkFacade::GetInstance(this);

	if (strixNetwork && m_replicator && m_replicator->GetIsOwnerAndReplicating())
	{
		TArray<FStrixRelayArg> relayArgs;
		FillMoveRelayArguments(relayArgs);

		strixNetwork->SendRpcToOtherMembers(m_replicator->ChannelId, m_replicator->GetNetworkObject()->GetNetworkInstanceId(), StrixUtil::GetHashValue(MoveRPCDirectName), relayArgs);
	}
}


void UStrixMovementSynchronizer::RequestDirectMoveMessage()
{
	SendDirectMoveRpcMessage();
}


void UStrixMovementSynchronizer::PropagateSyncPropertyChanges()
{
	if (m_syncGroup && m_replicator && m_replicator->GetIsOwnerAndReplicating())
	{
		m_syncGroup->SetShouldPropagate(true);
	}
}

void UStrixMovementSynchronizer::OnRoomJoinNotification(
	strix::client::core::NotificationEventArgs<strix::client::room::message::RoomJoinNotificationPtr> args)
{
	auto strixNetwork = UStrixNetworkFacade::GetInstance(this);

	if (strixNetwork && m_replicator && m_replicator->GetIsOwnerAndReplicating())
	{
		TArray<FStrixRelayArg> relayArgs;
		FillMoveRelayArguments(relayArgs);

		strixNetwork->SendRpc(m_replicator->ChannelId, args.m_data->GetNewlyJoinedMember()->GetUid(), m_replicator->GetNetworkObject()->GetNetworkInstanceId(), StrixUtil::GetHashValue(MoveRPCName), relayArgs);
	}
}

void UStrixMovementSynchronizer::RemoveRoomJoinNotificationHandler(strix::client::ingame::network::RoomContextPtr context)
{
	UStrixNetworkFacade* facade = UStrixNetworkFacade::GetInstance(this);

	if (facade)
	{
		auto roomContext = context;
		if (roomContext)
		{
			roomContext->GetMatchRoomClient()->RemoveRoomJoinNotifiedHandler(m_roomJoinNotificationHandle);
			m_roomJoinNotificationHandle = 0;
		}
	}
}

void UStrixMovementSynchronizer::RemoveRoomContextInvalidateHandler()
{
	UStrixNetworkFacade* facade = UStrixNetworkFacade::GetInstance(this);

	if (facade)
	{
		auto roomContext = facade->GetRoomContextByChannelId(m_replicator->ChannelId);
		if (roomContext)
		{
			RemoveRoomJoinNotificationHandler(roomContext);
			roomContext->RemoveRoomContextInvalidateHandler(m_roomContextInvalidateHandle);
			m_roomContextInvalidateHandle = 0;
		}
	}
}

void UStrixMovementSynchronizer::FillMoveRelayArguments(TArray<FStrixRelayArg>& args)
{
	FVector currentPosition = m_pMovementController->GetPositionAsVector();
	FVector currentVelocity = m_pMovementController->GetVelocityAsVector();
	FQuat currentRotation = m_pMovementController->GetRotationAsQuat();

	args.Add(FStrixRelayArg(strix::net::object::UEObjectAdapter(currentPosition)));
	args.Add(FStrixRelayArg(strix::net::object::UEObjectAdapter(currentVelocity)));
	args.Add(FStrixRelayArg(strix::net::object::UEObjectAdapter(currentRotation)));
}

void UStrixMovementSynchronizer::CreatePropertiesSyncGroup()
{
	if (m_replicator)
	{
		m_syncGroup = std::make_shared<StrixMovementSyncGroup>(nullptr);

		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(PositionXPropertyName, m_pMovementController->GetPositionXRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(PositionYPropertyName, m_pMovementController->GetPositionYRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(PositionZPropertyName, m_pMovementController->GetPositionZRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(VelocityXPropertyName, m_pMovementController->GetVelocityXRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(VelocityYPropertyName, m_pMovementController->GetVelocityYRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(VelocityZPropertyName, m_pMovementController->GetVelocityZRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(RotationXPropertyName, m_pMovementController->GetRotationXRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(RotationYPropertyName, m_pMovementController->GetRotationYRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(RotationZPropertyName, m_pMovementController->GetRotationZRef()));
		m_syncGroup->AddProperty(std::make_shared<UESyncProperty<float>>(RotationWPropertyName, m_pMovementController->GetRotationWRef()));

		if (m_replicator->IsOwner)
		{
			m_syncGroup->SetPostApplyFunction([&]()
			{
				m_replicator->GetOwner()->SetActorLocationAndRotation(m_pMovementController->GetPositionAsVector(), m_pMovementController->GetRotationAsQuat());
				m_replicator->GetOwner()->GetRootComponent()->ComponentVelocity = m_pMovementController->GetVelocityAsVector();

				OnPropertiesSyncFinished();
				m_syncGroup->SetPostApplyFunction(std::bind(&UStrixMovementSynchronizer::OnPropertiesSyncFinished, this));
			});
		}

		m_replicator->AddSyncGroup(m_syncGroup);
	}
}

void UStrixMovementSynchronizer::OnRpcJump()
{
	if (m_replicator->GetIsReplicating())
	{
		if (!m_replicator->GetIsOwner())
		{
			if (!SyncJump)
				return;

			ACharacter* character = Cast<ACharacter>(GetOwner());
			UPawnMovementComponent *pMovementComponent = character->GetMovementComponent();
			if (!pMovementComponent->IsFalling())
			{
				character->Jump();
			}
		}
	}
}

void UStrixMovementSynchronizer::OnRpcMove(FVector position, FVector velocity, FQuat rotation)
{
	if (m_replicator->GetIsReplicating())
	{
		if (!m_replicator->GetIsOwner())
		{
			m_pMovementController->UpdateStoredValues(position, velocity, rotation);
			m_pMovementController->Refresh();
		}
	}
}

void UStrixMovementSynchronizer::OnRpcMoveDirect(FVector position, FVector velocity, FQuat rotation)
{
	if (m_replicator->GetIsReplicating())
	{
		if (!m_replicator->GetIsOwner())
		{
			GetOwner()->SetActorLocationAndRotation(position, rotation);
			m_pMovementController->UpdateStoredValues(position, velocity, rotation);
			m_pMovementController->Refresh();
		}
	}
}

void UStrixMovementSynchronizer::OnPropertiesSyncFinished()
{
	if (!m_replicator->GetIsOwner())
	{
		m_pMovementController->Refresh();
	}
}

void UStrixMovementSynchronizer::ResetSynchronizer()
{
	m_pMovementController = CreateMovementController();
}