/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "StrixBlueprintFunctionLibrary.h"

#include "UELogHandler.h"
#include "Kismet/GameplayStatics.h"
#include "Rpc/UERpcProcedure.h"
#include "Serialization/UEObjectAdapter.h"

#include <strix/client/core/model/manager/filter/builder/ConditionBuilder.h>
#include <strix/client/core/model/manager/Filters.h>
#include <strix/client/ingame/object/NetworkObject.h>
#include <strix/net/util/SuperFastHash.h>

template <typename TWrapperObject>
static bool TryGetProperty(const FStrixPropertyMap& strixStructure, const FString &propertyName, typename TWrapperObject::ValueType& value)
{
	auto mapProperty = strixStructure.m_propertyMap.find(TCHAR_TO_UTF8(*propertyName));
	if (mapProperty == strixStructure.m_propertyMap.end())
		return false;

	if (!mapProperty->second->InstanceOf<TWrapperObject>())
		return false;

	value = std::static_pointer_cast<TWrapperObject>(mapProperty->second)->Get();

	return true;
}

template <typename T>
static FStrixPropertyMap SetProperty(FStrixPropertyMap &strixStructure, const FString &propertyName, const T &value)
{
	std::string convertedPropertyName = TCHAR_TO_UTF8(*propertyName);
	auto obj = strix::net::object::ObjectAdapter(value).Get();
	auto result = strixStructure.m_propertyMap.insert(std::make_pair(convertedPropertyName, obj));

	if (!result.second)
		result.first->second = obj;

	return strixStructure;
}

void UStrixBlueprintFunctionLibrary::InitializeStrixNetwork(const UObject* WorldContextObject, const FString &applicationId)
{
	if (!UStrixNetworkFacade::GetInstance(WorldContextObject))
	{
		UStrixNetworkFacade* strixNetwork = NewObject<UStrixNetworkFacade>();
		UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);

		if (gameInstance)
		{
			strixNetwork->Init(gameInstance, applicationId);
		}
	}
}

void UStrixBlueprintFunctionLibrary::InitializeStrixNetworkWithHttpAccessToken(const UObject* WorldContextObject, const FString &applicationId, const FString &accessToken)
{
	if (!UStrixNetworkFacade::GetInstance(WorldContextObject))
	{
		UStrixNetworkFacade* strixNetwork = NewObject<UStrixNetworkFacade>();
		UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);

		if (gameInstance)
		{
			strixNetwork->InitWithHttpAccessToken(gameInstance, applicationId, accessToken);
		}
	}
}

void UStrixBlueprintFunctionLibrary::StopStrixNetwork(const UObject* WorldContextObject)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
		strixNetwork->Stop(gameInstance);
	}
}

bool UStrixBlueprintFunctionLibrary::IsInitialized(const UObject* WorldContextObject)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->IsInitialized();
	}
	return false;
}

bool UStrixBlueprintFunctionLibrary::IsNetworkObjectManagerPaused(const UObject* WorldContextObject, int32 channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);
	if(strixNetwork)
	{
		return strixNetwork->IsNetworkObjectManagerPaused(channelId);
	}
	return false;
}

void UStrixBlueprintFunctionLibrary::ConnectToMasterServer(const UObject* WorldContextObject, const FString &host, int32 port, const FStrixMasterServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (IsRemoteActor(WorldContextObject))
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::ConnectToMasterServer - Trying to connect on replicated actor, aborting."));
		return;
	}

	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->ConnectToMasterServer(host, port, successCallback, failureCallback);
	}
}

bool UStrixBlueprintFunctionLibrary::IsMasterServerConnected(const UObject* WorldContextObject)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->IsMasterServerConnected();
	}
	return false;
}

void UStrixBlueprintFunctionLibrary::DisconnectMasterServer(const UObject* WorldContextObject)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->DisconnectMasterServer();
	}
}

void UStrixBlueprintFunctionLibrary::SearchNode(const UObject * WorldContextObject, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixNodeSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->SearchNode(limit, offset, condition, order, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::SearchNodeRoom(const UObject * WorldContextObject, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->SearchNodeRoom(limit, offset, condition, order, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::SearchJoinableNodeRoom(const UObject * WorldContextObject, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->SearchJoinableNodeRoom(limit, offset, condition, order, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::JoinRandomNodeRoom(const UObject * WorldContextObject, int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties, bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (IsRemoteActor(WorldContextObject))
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::JoinRandomNodeRoom - Trying to connect on replicated actor, aborting."));
		return;
	}

	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->JoinRandomNodeRoom(channelId, condition, memberProperties, pauseNetworkObjects, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::JoinNodeRoom(
	const UObject* WorldContextObject, int channelId, const FStrixNodeRoomInfo& roomInfo,
	const FStrixPropertyMap& memberProperties, const FString& password, bool pauseNetworkObjects,
	const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->JoinNodeRoom(channelId, roomInfo, memberProperties, password, pauseNetworkObjects, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::CreateNodeRoom(
	const UObject* WorldContextObject,
	int channelId, 	const FStrixPropertyMap& roomProperties, const FStrixPropertyMap& memberProperties,
	bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->CreateNodeRoom(channelId, roomProperties, memberProperties, pauseNetworkObjects, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::ConnectToRoomServer(const UObject * WorldContextObject, const FString &host, int32 port, const FString &protocol, int channelId, const FStrixRoomServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (IsRemoteActor(WorldContextObject))
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::ConnectToRoomServer - Trying to connect on replicated actor, aborting."));
		return;
	}

	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->ConnectToRoomServer(host, port, protocol, channelId, successCallback, failureCallback);
	}
}

bool UStrixBlueprintFunctionLibrary::IsRoomServerConnected(const UObject* WorldContextObject, int32 channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->IsRoomServerConnected(channelId);
	}
	return false;
}

void UStrixBlueprintFunctionLibrary::DisconnectRoomServer(const UObject* WorldContextObject, int channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->DisconnectRoomServer(channelId);
	}
}

void UStrixBlueprintFunctionLibrary::SearchRoom(const UObject * WorldContextObject, int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->SearchRoom(channelId, limit, offset, condition, order, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::JoinRoom(
	const UObject * WorldContextObject, int32 channelId, int32 roomId, const FStrixPropertyMap& memberProperties, 
	const FString &password, bool pauseNetworkObjects, 
	const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->JoinRoom(channelId, roomId, memberProperties, password, pauseNetworkObjects, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::CreateRoom(
	const UObject * WorldContextObject, int32 channelId, const FStrixPropertyMap& roomProperties,
	const FStrixPropertyMap& memberProperties, bool pauseNetworkObjects, 
	const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->CreateRoom(channelId, roomProperties, memberProperties, pauseNetworkObjects, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::SearchJoinableRoom(const UObject * WorldContextObject, int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->SearchJoinableRoom(channelId, limit, offset, condition, order, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::JoinRandomRoom(
	const UObject * WorldContextObject, int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties,
	bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->JoinRandomRoom(channelId, condition, memberProperties, pauseNetworkObjects, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::LeaveRoom(const UObject * WorldContextObject, int32 channelId, const FStrixRoomLeaveDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->LeaveRoom(channelId, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::DeleteRoom(const UObject * WorldContextObject, int32 channelId, const FStrixRoomDeleteDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->DeleteRoom(channelId, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::SetRoom(const UObject * WorldContextObject, int32 channelId, const FStrixPropertyMap& roomProperties, const FStrixRoomSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->SetRoom(channelId, roomProperties, successCallback, failureCallback);
	}
}

FStrixRoom UStrixBlueprintFunctionLibrary::GetCurrentRoom(const UObject* WorldContextObject, int channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->GetCurrentRoom(channelId);
	}
	return FStrixRoom();
}

void UStrixBlueprintFunctionLibrary::SetRoomMember(const UObject * WorldContextObject, int32 channelId, const FStrixPropertyMap& memberProperties, const FStrixRoomMemberSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->SetRoomMember(channelId, memberProperties, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::KickRoomMember(const UObject * WorldContextObject, int32 channelId, const FStrixRoomMember& member, const FStrixRoomMemberKickDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->KickRoomMember(channelId, member, successCallback, failureCallback);
	}
}

bool UStrixBlueprintFunctionLibrary::IsRoomOwner(const UObject* WorldContextObject, int channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->IsRoomOwner(channelId);
	}
	return false;
}

FStrixRoomMember UStrixBlueprintFunctionLibrary::GetCurrentRoomMember(const UObject* WorldContextObject, int channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->GetCurrentRoomMember(channelId);
	}
	return FStrixRoomMember();
}

FStrixRoomMember UStrixBlueprintFunctionLibrary::GetCurrentRoomMemberById(const UObject* WorldContextObject, int channelId, int32 memberId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->GetCurrentRoomMemberById(channelId, memberId);
	}
	return FStrixRoomMember();
}

TArray<FStrixRoomMember> UStrixBlueprintFunctionLibrary::GetCurrentRoomMembers(const UObject* WorldContextObject, int channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		return strixNetwork->GetCurrentRoomMembers(channelId);
	}
	return TArray<FStrixRoomMember>();
}

void UStrixBlueprintFunctionLibrary::GetNodeCount(const UObject* WorldContextObject, const FStrixNodeGetCountDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);
	if(strixNetwork)
	{
	strixNetwork->GetNodeCount(successCallback, failureCallback);
	}
}


void UStrixBlueprintFunctionLibrary::RelayMessage(const UObject* WorldContextObject, int32 channelId,
	const FStrixRelayArg& message, const FStrixRoomRelayDelegate& successCallback,
	const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->Relay(channelId, message, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::DirectRelayMessage(const UObject* WorldContextObject, int32 channelId,
	const FStrixRelayArg& message, const FStrixRoomMember& member, const FStrixRoomDirectRelayDelegate& successCallback,
	const FStrixErrorCodeFailureDelegate& failureCallback)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->DirectRelay(channelId, message, member, successCallback, failureCallback);
	}
}

void UStrixBlueprintFunctionLibrary::RegisterStrixRpc(const UObject* WorldContextObject, AActor* target, const FString &functionName)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (!strixNetwork)
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::RegisterRpc - Strix network is not initialized."));
		return;
	}

	const auto replicatorComponent = GetStrixReplicatorComponent(target);

	if (replicatorComponent)
	{
		if (!replicatorComponent->GetNetworkObject())
		{
			UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::RegisterRpc - Replicator component doesn't have a network object set."));
			return;
		}

		std::shared_ptr<strix::client::ingame::rpc::UERpcProcedure> rpcProcedure = std::make_shared<strix::client::ingame::rpc::UERpcProcedure>(target, functionName);

		strixNetwork->RegisterRpcProcedure(replicatorComponent->ChannelId, replicatorComponent->GetNetworkObject()->GetNetworkInstanceId(), rpcProcedure);
	}
	else
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::RegisterRpc - Actor does not have a replicator component attached."));
	}
}

void UStrixBlueprintFunctionLibrary::SendRpcToObjectOwner(const UObject* WorldContextObject, const AActor* target, const FString &functionName, const TArray<FStrixRelayArg>& args)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (!strixNetwork)
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpc - Strix network is not initialized."));
		return;
	}

	const auto replicatorComponent = GetStrixReplicatorComponent(target);

	if (replicatorComponent)
	{
		if (!replicatorComponent->GetNetworkObject())
		{
			UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpc - Replicator component doesn't have a network object set."));
			return;
		}

		const int procedureHash = GetRpcProcedureHash(functionName);

		strixNetwork->SendRpc(replicatorComponent->ChannelId, replicatorComponent->GetNetworkObject()->GetOwnerUid(), replicatorComponent->GetNetworkObject()->GetNetworkInstanceId(),
			procedureHash, args);
	}
	else
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpc - Actor does not have a replicator component attached."));
	}
}

void UStrixBlueprintFunctionLibrary::SendRpcToRoomOwner(const UObject* WorldContextObject, const AActor* target,
	const FString &functionName, const TArray<FStrixRelayArg>& args)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (!strixNetwork)
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToRoomOwner - Strix network is not initialized."));
		return;
	}

	const auto replicatorComponent = GetStrixReplicatorComponent(target);

	if (replicatorComponent)
	{
		if (!replicatorComponent->GetNetworkObject())
		{
			UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToRoomOwner - Replicator component doesn't have a network object set."));
			return;
		}

		const int procedureHash = GetRpcProcedureHash(functionName);

		strixNetwork->SendRpcToRoomOwner(replicatorComponent->ChannelId,replicatorComponent->GetNetworkObject()->GetNetworkInstanceId(),
			procedureHash, args);
	}
	else
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToRoomOwner - Actor does not have a replicator component attached."));
	}
}

void UStrixBlueprintFunctionLibrary::SendRpcToOtherMembers(const UObject* WorldContextObject, const AActor* target,
	const FString &functionName, const TArray<FStrixRelayArg>& args)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (!strixNetwork)
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToOtherMembers - Strix network is not initialized."));
		return;
	}

	const auto replicatorComponent = GetStrixReplicatorComponent(target);

	if (replicatorComponent)
	{
		if (!replicatorComponent->GetNetworkObject())
		{
			UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToOtherMembers - Replicator component doesn't have a network object set."));
			return;
		}

		const int procedureHash = GetRpcProcedureHash(functionName);

		strixNetwork->SendRpcToOtherMembers(replicatorComponent->ChannelId, replicatorComponent->GetNetworkObject()->GetNetworkInstanceId(),
			procedureHash, args);
	}
	else
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToOtherMembers - Actor does not have a replicator component attached."));
	}
}

void UStrixBlueprintFunctionLibrary::SendRpcToAll(const UObject* WorldContextObject, const AActor* target,
	const FString &functionName, const TArray<FStrixRelayArg>& args)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (!strixNetwork)
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToAll - Strix network is not initialized."));
		return;
	}

	const auto replicatorComponent = GetStrixReplicatorComponent(target);

	if (replicatorComponent)
	{
		if (!replicatorComponent->GetNetworkObject())
		{
			UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToAll - Replicator component doesn't have a network object set."));
			return;
		}

		const int procedureHash = GetRpcProcedureHash(functionName);

		strixNetwork->SendRpcToAll(replicatorComponent->ChannelId, replicatorComponent->GetNetworkObject()->GetNetworkInstanceId(),
			procedureHash, args);
	}
	else
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToAll - Actor does not have a replicator component attached."));
	}
}

void UStrixBlueprintFunctionLibrary::SendRpc(const UObject* WorldContextObject, const AActor* target, const FStrixRoomMember& member, const FString& functionName, const TArray<FStrixRelayArg>& args)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (!strixNetwork)
	{
	UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpcToMember - Strix network is not initialized."));
	return;
	}

	const auto replicatorComponent = GetStrixReplicatorComponent(target);

	if (replicatorComponent)
	{
	if (!replicatorComponent->GetNetworkObject())
	{
		UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpc - Replicator component doesn't have a network object set."));
		return;
	}

	const int procedureHash = GetRpcProcedureHash(functionName);
	
	strixNetwork->SendRpc(replicatorComponent->ChannelId, member.m_roomMember->GetUid(), replicatorComponent->GetNetworkObject()->GetNetworkInstanceId(),
		procedureHash, args);
	}
	else
	{
	UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::SendRpc - Actor does not have a replicator component attached."));
	}
}

void UStrixBlueprintFunctionLibrary::PauseNetworkObjectManager(const UObject* WorldContextObject, int32 channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->PauseNetworkObjectManager(channelId);
	}
}

void UStrixBlueprintFunctionLibrary::UnpauseNetworkObjectManager(const UObject* WorldContextObject, int32 channelId)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		strixNetwork->UnpauseNetworkObjectManager(channelId);
	}
}

FStrixNetworkId UStrixBlueprintFunctionLibrary::GetNetworkIdFromObject(const UObject* WorldContextObject, const AActor* target)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	if (strixNetwork)
	{
		const auto replicatorComponent = GetStrixReplicatorComponent(target);

		if (replicatorComponent)
		{
			if (!replicatorComponent->GetNetworkObject())
			{
				UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::GetNetworkIdFromObject - Replicator component doesn't have a network object set."));
				return FStrixNetworkId(-1);
			}

			return FStrixNetworkId(replicatorComponent->GetNetworkObject()->GetNetworkInstanceId());
		}
		else
		{
			UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::GetNetworkIdFromObject - Actor does not have a replicator component attached."));
		}
	}
	return FStrixNetworkId(-1);
}

AActor* UStrixBlueprintFunctionLibrary::GetObjectFromNetworkId(const UObject* WorldContextObject, FStrixNetworkId networkId, int channel)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	AActor* object = nullptr;
	if (strixNetwork)
	{
		auto idString = std::string(TCHAR_TO_UTF8(*networkId.StringId));
		object = strixNetwork->GetObjectFromNetworkId(strtoll(idString.c_str(), nullptr, 10), channel);
	}
	if (!object)
	{
		UE_LOG(LogStrix, Log, TEXT("Object not found with id: %s"), *networkId.StringId);
	}
	return object;
}

AActor* UStrixBlueprintFunctionLibrary::GetObjectFromNetworkIdString(const UObject* WorldContextObject, FString networkId, int channel)
{
	UStrixNetworkFacade* strixNetwork = UStrixNetworkFacade::GetInstance(WorldContextObject);

	AActor* object = nullptr;
	if (strixNetwork)
	{
		auto idString = std::string(TCHAR_TO_UTF8(*networkId));
		object = strixNetwork->GetObjectFromNetworkId(strtoll(idString.c_str(), nullptr, 10), channel);
	}
	if (!object)
	{
		UE_LOG(LogStrix, Log, TEXT("Object not found with id: %s"), *networkId);
	}
	return object;
}

void UStrixBlueprintFunctionLibrary::TryGetByteProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, uint8& value)
{
	result = TryGetProperty<strix::net::object::ByteObject>(strixStructure, propertyName, reinterpret_cast<int8&>(value));
}

void UStrixBlueprintFunctionLibrary::TryGetBoolProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, bool& value)
{
	result = TryGetProperty<strix::net::object::BooleanObject>(strixStructure, propertyName, value);
}

void UStrixBlueprintFunctionLibrary::TryGetIntProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, int32& value)
{
	result = TryGetProperty<strix::net::object::IntegerObject>(strixStructure, propertyName, value);
}

void UStrixBlueprintFunctionLibrary::TryGetFloatProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, float& value)
{
	result = TryGetProperty<strix::net::object::FloatObject>(strixStructure, propertyName, value);
}

void UStrixBlueprintFunctionLibrary::TryGetStringProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, FString& value)
{
	auto mapProperty = strixStructure.m_propertyMap.find(TCHAR_TO_UTF8(*propertyName));
	if (mapProperty == strixStructure.m_propertyMap.end())
	{
		result = false;
		return;
	}

	if (!mapProperty->second->InstanceOf<strix::net::object::StringObject>())
	{
		result = false;
		return;
	}

	auto obj = std::static_pointer_cast<strix::net::object::StringObject>(mapProperty->second);

	value = FString(UTF8_TO_TCHAR(obj->Get().c_str()));
	result = true;
}

FStrixPropertyMap UStrixBlueprintFunctionLibrary::SetByteProperty(FStrixPropertyMap strixStructure, FString propertyName, uint8 value)
{
	return SetProperty(strixStructure, propertyName, static_cast<int8>(value));
}

FStrixPropertyMap UStrixBlueprintFunctionLibrary::SetBoolProperty(FStrixPropertyMap strixStructure, FString propertyName, bool value)
{
	return SetProperty(strixStructure, propertyName, value);
}

FStrixPropertyMap UStrixBlueprintFunctionLibrary::SetIntProperty(FStrixPropertyMap strixStructure, FString propertyName, int32 value)
{
	return SetProperty(strixStructure, propertyName, value);
}

FStrixPropertyMap UStrixBlueprintFunctionLibrary::SetFloatProperty(FStrixPropertyMap strixStructure, FString propertyName, float value)
{
	return SetProperty(strixStructure, propertyName, value);
}

FStrixPropertyMap UStrixBlueprintFunctionLibrary::SetStringProperty(FStrixPropertyMap strixStructure, FString propertyName, FString value)
{
	std::string convertedValue = TCHAR_TO_UTF8(*value);
	return SetProperty(strixStructure, propertyName, convertedValue);
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixBoolEqualsCondition(FString fieldName, bool value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->EqualTo(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixBoolNotEqualsCondition(FString fieldName, bool value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->NotEqualTo(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteEqualsCondition(FString fieldName, uint8 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->EqualTo(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteGreaterThanCondition(FString fieldName, uint8 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThan(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteGreaterThanEqualsCondition(FString fieldName, uint8 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThanEquals(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteLessThanCondition(FString fieldName, uint8 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThan(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteLessThanEqualsCondition(FString fieldName, uint8 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThanEquals(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteNotEqualsCondition(FString fieldName, uint8 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->NotEqualTo(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteBetweenExclusiveCondition(FString fieldName, uint8 left, uint8 right)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenExclusive(strix::net::object::ObjectAdapter(left), strix::net::object::ObjectAdapter(right))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixByteBetweenInclusiveCondition(FString fieldName, uint8 left, uint8 right)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenInclusive(strix::net::object::ObjectAdapter(left), strix::net::object::ObjectAdapter(right))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntEqualsCondition(FString fieldName, int32 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->EqualTo(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntGreaterThanCondition(FString fieldName, int32 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThan(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntGreaterThanEqualsCondition(FString fieldName, int32 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThanEquals(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntLessThanCondition(FString fieldName, int32 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThan(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntLessThanEqualsCondition(FString fieldName, int32 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThanEquals(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntNotEqualsCondition(FString fieldName, int32 value)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->NotEqualTo(strix::net::object::ObjectAdapter(value))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntBetweenExclusiveCondition(FString fieldName, int32 left, int32 right)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenExclusive(strix::net::object::ObjectAdapter(left), strix::net::object::ObjectAdapter(right))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixIntBetweenInclusiveCondition(FString fieldName, int32 left, int32 right)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenInclusive(strix::net::object::ObjectAdapter(left), strix::net::object::ObjectAdapter(right))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatEqualsCondition(FString fieldName, float value)
{
	double castedValue = (double)value;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->EqualTo(strix::net::object::ObjectAdapter(castedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatGreaterThanCondition(FString fieldName, float value)
{
	double castedValue = (double)value;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThan(strix::net::object::ObjectAdapter(castedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatGreaterThanEqualsCondition(FString fieldName, float value)
{
	double castedValue = (double)value;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThanEquals(strix::net::object::ObjectAdapter(castedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatLessThanCondition(FString fieldName, float value)
{
	double castedValue = (double)value;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThan(strix::net::object::ObjectAdapter(castedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatLessThanEqualsCondition(FString fieldName, float value)
{
	double castedValue = (double)value;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThanEquals(strix::net::object::ObjectAdapter(castedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatNotEqualsCondition(FString fieldName, float value)
{
	double castedValue = (double)value;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->NotEqualTo(strix::net::object::ObjectAdapter(castedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatBetweenExclusiveCondition(FString fieldName, float left, float right)
{
	double castedValueLeft = (double)left;
	double castedValueRight = (double)right;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenExclusive(strix::net::object::ObjectAdapter(castedValueLeft), strix::net::object::ObjectAdapter(castedValueRight))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFloatBetweenInclusiveCondition(FString fieldName, float left, float right)
{
	double castedValueLeft = (double)left;
	double castedValueRight = (double)right;
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenInclusive(strix::net::object::ObjectAdapter(castedValueLeft), strix::net::object::ObjectAdapter(castedValueRight))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixStringEqualsCondition(FString fieldName, FString value)
{
	std::string convertedValue = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->EqualTo(strix::net::object::ObjectAdapter(convertedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixStringNotEqualsCondition(FString fieldName, FString value)
{
	std::string convertedValue = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->NotEqualTo(strix::net::object::ObjectAdapter(convertedValue))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixStringContainsCondition(FString fieldName, FString value)
{
	std::string convertedValue = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->Contains(convertedValue)->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixStringEndsWithCondition(FString fieldName, FString value)
{
	std::string convertedValue = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->EndsWith(convertedValue)->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixStringStartsWithCondition(FString fieldName, FString value)
{
	std::string convertedValue = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->StartsWith(convertedValue)->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldEqualsCondition(FString fieldName, FString value)
{
	std::string convertedFieldName = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->EqualTo(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedFieldName))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldGreaterThanCondition(FString fieldName, FString value)
{
	std::string convertedFieldName = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThan(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedFieldName))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldGreaterThanEqualsCondition(FString fieldName, FString value)
{
	std::string convertedFieldName = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->GreaterThanEquals(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedFieldName))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldLessThanCondition(FString fieldName, FString value)
{
	std::string convertedFieldName = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThan(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedFieldName))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldLessThanEqualsCondition(FString fieldName, FString value)
{
	std::string convertedFieldName = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->LessThanEquals(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedFieldName))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldNotEqualsCondition(FString fieldName, FString value)
{
	std::string convertedFieldName = TCHAR_TO_UTF8(*value);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->NotEqualTo(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedFieldName))->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldBetweenExclusiveCondition(FString fieldName, FString left, FString right)
{
	std::string convertedLeftFieldName = TCHAR_TO_UTF8(*left);
	std::string convertedRightFieldName = TCHAR_TO_UTF8(*right);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenExclusive(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedLeftFieldName), std::make_shared<strix::client::core::model::manager::filter::Field>(convertedRightFieldName))
		->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldBetweenInclusiveCondition(FString fieldName, FString left, FString right)
{
	std::string convertedLeftFieldName = TCHAR_TO_UTF8(*left);
	std::string convertedRightFieldName = TCHAR_TO_UTF8(*right);
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->BetweenInclusive(std::make_shared<strix::client::core::model::manager::filter::Field>(convertedLeftFieldName), std::make_shared<strix::client::core::model::manager::filter::Field>(convertedRightFieldName))
		->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldIsNullCondition(FString fieldName)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->IsNull()->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixFieldIsNotNullCondition(FString fieldName)
{
	FStrixCondition condition(strix::client::core::model::manager::filter::builder::ConditionBuilder::Builder()
		->Field(TCHAR_TO_UTF8(*fieldName))->IsNotNull()->Build());
	return condition;
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixAndCondition(TArray<FStrixCondition> conditions)
{
	std::shared_ptr<strix::client::core::model::manager::filter::And> andCondition = std::make_shared<strix::client::core::model::manager::filter::And>();

	for (const auto& innerCondition : conditions)
	{
		andCondition->GetConditions().push_back(innerCondition.m_condition);
	}

	return FStrixCondition(andCondition);
}

FStrixCondition UStrixBlueprintFunctionLibrary::CreateStrixOrCondition(TArray<FStrixCondition> conditions)
{
	std::shared_ptr<strix::client::core::model::manager::filter::Or> orCondition = std::make_shared<strix::client::core::model::manager::filter::Or>();

	for (const auto& innerCondition : conditions)
	{
		orCondition ->GetConditions().push_back(innerCondition.m_condition);
	}

	return FStrixCondition(orCondition );
}

FStrixOrder UStrixBlueprintFunctionLibrary::CreateStrixAscendingOrder(FString fieldName)
{
	return FStrixOrder(std::make_shared<strix::client::core::model::manager::filter::Order>
		(TCHAR_TO_UTF8(*fieldName), strix::client::core::model::manager::filter::OrderType::Ascending)
	);
}

FStrixOrder UStrixBlueprintFunctionLibrary::CreateStrixDescendingOrder(FString fieldName)
{
	return FStrixOrder(std::make_shared<strix::client::core::model::manager::filter::Order>
		(TCHAR_TO_UTF8(*fieldName), strix::client::core::model::manager::filter::OrderType::Descending)
	);
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_ByteToStrixRelayArg(uint8 val)
{
	FStrixRelayArg arg(strix::net::object::ObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_BoolToStrixRelayArg(bool val)
{
	FStrixRelayArg arg(strix::net::object::ObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntToStrixRelayArg(int32 val)
{
	FStrixRelayArg arg(strix::net::object::ObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_FloatToStrixRelayArg(float val)
{
	FStrixRelayArg arg(strix::net::object::ObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_VectorToStrixRelayArg(FVector val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_RotatorToStrixRelayArg(FRotator val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_TransformToStrixRelayArg(FTransform val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_QuatToStrixRelayArg(FQuat val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringToStrixRelayArg(FString val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_TextToStrixRelayArg(FText val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_ByteArrayToStrixRelayArg(TArray<uint8> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntArrayToStrixRelayArg(TArray<int32> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_FloatArrayToStrixRelayArg(TArray<float> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_VectorArrayToStrixRelayArg(TArray<FVector> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_QuatArrayToStrixRelayArg(TArray<FQuat> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_RotatorArrayToStrixRelayArg(TArray<FRotator> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_TransformArrayToStrixRelayArg(TArray<FTransform> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringArrayToStrixRelayArg(TArray<FString> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_TextArrayToStrixRelayArg(TArray<FText> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_BoolArrayToStrixRelayArg(TArray<bool> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_ByteSetToStrixRelayArg(TSet<uint8> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntSetToStrixRelayArg(TSet<int32> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_FloatSetToStrixRelayArg(TSet<float> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_VectorSetToStrixRelayArg(TSet<FVector> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringSetToStrixRelayArg(TSet<FString> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntKeyByteMapToStrixRelayArg(TMap<int32, uint8> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntKeyIntMapToStrixRelayArg(TMap<int32, int32> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntKeyFloatMapToStrixRelayArg(TMap<int32, float> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntKeyVectorMapToStrixRelayArg(TMap<int32, FVector> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntKeyRotatorMapToStrixRelayArg(TMap<int32, FRotator> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_IntKeyStringMapToStrixRelayArg(TMap<int32, FString> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringKeyByteMapToStrixRelayArg(TMap<FString, uint8> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringKeyIntMapToStrixRelayArg(TMap<FString, int32> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringKeyFloatMapToStrixRelayArg(TMap<FString, float> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringKeyVectorMapToStrixRelayArg(TMap<FString, FVector> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringKeyRotatorMapToStrixRelayArg(TMap<FString, FRotator> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StringKeyStringMapToStrixRelayArg(TMap<FString, FString> val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

FStrixRelayArg UStrixBlueprintFunctionLibrary::Conv_StrixNetworkIdToStrixRelayArg(FStrixNetworkId val)
{
	FStrixRelayArg arg(strix::net::object::UEObjectAdapter(val).Get());

	return arg;
}

bool UStrixBlueprintFunctionLibrary::IsRemoteActor(const UObject* WorldContextObject)
{
	const auto actor = Cast<AActor>(WorldContextObject);
	if (actor)
	{
		const auto replicatorComponent = actor->FindComponentByClass<UStrixReplicatorComponent>();

		if (replicatorComponent)
			return !replicatorComponent->GetIsOwner();
	}

	return false;
}

UStrixReplicatorComponent* UStrixBlueprintFunctionLibrary::GetStrixReplicatorComponent(const AActor* target)
{
	if (target)
	{
		const auto replicatorComponent = target->FindComponentByClass<UStrixReplicatorComponent>();

		if (!replicatorComponent)
		{
			UE_LOG(LogStrix, Log, TEXT("StrixBlueprintFunctionLibrary::GetStrixReplicatorComponent - Actor does not have a replicator component attached."));
		}

		return replicatorComponent;
	}
	return nullptr;
}

int UStrixBlueprintFunctionLibrary::GetRpcProcedureHash(const FString& functionName)
{
	// ToDo: add predefined hash storage
	return strix::net::util::SuperFastHash::Fast(TCHAR_TO_UTF8(*functionName));
}
