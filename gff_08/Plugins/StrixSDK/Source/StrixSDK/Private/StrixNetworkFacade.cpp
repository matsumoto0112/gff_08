/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "StrixNetworkFacade.h"

#include "UELogHandler.h"
#include "Misc/ConfigCacheIni.h"
#include "UEHttpClient.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Serialization/UEObjectsSerializers.h"
#include "Sync/UENetworkObject.h"

#if WITH_EDITOR
#include "Util/PIEHelper.h"
#endif

#include <strix/client/ingame/network/StrixClient.h>
#include <strix/client/ingame/network/MasterServerConnection.h>
#include <strix/client/ingame/network/RoomServerConnection.h>
#include <strix/client/ingame/network/RoomContext.h>
#include "strix/client/ingame/network/node/RandomNodeSelectionStrategy.h"
#include <strix/client/ingame/object/NetworkObjectManager.h>
#include <strix/client/ingame/object/NetworkObject.h>
#include <strix/client/ingame/rpc/RpcManager.h>

#include <strix/client/match/MatchRoomClient.h>
#include <strix/client/room/model/RoomMember.h>
#include <strix/client/match/room/model/MatchRoom.h>
#include <strix/client/core/auth/ApplicationIdCredentials.h>

#include <strix/client/ingame/network/data/NodeRoomInfo.h>
#include <strix/net/logging/Logger.h>
#include "strix/client/core/auth/UIDCredentials.h"

UStrixNetworkFacade* UStrixNetworkFacade::SingleInstance = nullptr;
std::map<int32, UStrixNetworkFacade*> UStrixNetworkFacade::PIEInstances = std::map<int32, UStrixNetworkFacade*>();

void UStrixNetworkFacade::Init(UGameInstance* gameInstance, const FString &applicationId)
{
	m_strixClient = strix::client::ingame::network::StrixClient::CreateWithApplicationIdAuth(TCHAR_TO_UTF8(*applicationId));
	InitBase(gameInstance);
}

void UStrixNetworkFacade::InitWithHttpAccessToken(UGameInstance* gameInstance, const FString &applicationId, const FString &accessToken)
{
	m_strixClient = strix::client::ingame::network::StrixClient::CreateWithHttpAccessTokenAuth(TCHAR_TO_UTF8(*applicationId), TCHAR_TO_UTF8(*accessToken), std::make_shared<UEHttpClient>());
	InitBase(gameInstance);
}

void UStrixNetworkFacade::BeginDestroy()
{
	UObject::BeginDestroy();

	StopBase();
}

void UStrixNetworkFacade::Stop(UGameInstance * gameInstance)
{
#if ENGINE_MINOR_VERSION < 20
	if (gameInstance)
		gameInstance->GetWorld()->ExtraReferencedObjects.Remove(this);
#else
	if (gameInstance)
		gameInstance->UnregisterReferencedObject(this);
#endif

	StopBase();
}

bool UStrixNetworkFacade::IsInitialized()
{
#if WITH_EDITOR
	return PIEInstances.find(m_PIEInstanceId) != PIEInstances.end();
#else
	return SingleInstance != nullptr;
#endif
}

bool UStrixNetworkFacade::IsNetworkObjectManagerPaused(int channelId)
{
    const auto roomContext = GetRoomContextByChannelId(channelId);
    if (roomContext)
    {
	auto networkObjectManager = roomContext->GetNetworkObjectManager();

	if (networkObjectManager)
	{
	    return networkObjectManager->IsPaused();
	}					
    }
    return false;
}

strix::client::ingame::network::RoomContextPtr UStrixNetworkFacade::GetRoomContextByChannelId(int channelId)
{
	auto it = m_roomContextsByChannelId.find(channelId);
	if (it != m_roomContextsByChannelId.end())
	{
		return it->second;
	}
	return nullptr;
}

void UStrixNetworkFacade::ConnectToMasterServer(const FString &host, int32 port, const FStrixMasterServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (IsMasterServerConnected())
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerAlreadyConnected, EStrixErrorCategory::StrixUESDK);
		return;
	}

	if (m_strixClient)
	{
		m_strixClient->ConnectToMasterServer(TCHAR_TO_UTF8(*host), port,
			[=](strix::client::ingame::network::MasterServerConnectEventArgs args) {
				if (IsMasterServerConnected())
				{
					failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerAlreadyConnected, EStrixErrorCategory::StrixUESDK);
					return;
				}

				m_masterServerConnection = args.GetConnection();
				m_masterServerConnectionClosedHandle = m_masterServerConnection->AddMasterServerConnectionClosedHandler(
					[=](strix::client::ingame::network::MasterServerConnectionClosedEventArgs removeEventArgs) {
						RemoveMasterServerConnection();
					}
				);
				successCallback.ExecuteIfBound();
			}, [failureCallback](strix::client::ingame::network::ServerConnectFailedEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
}

bool UStrixNetworkFacade::IsMasterServerConnected()
{
	if (m_masterServerConnection)
	{
		return m_masterServerConnection->IsOpen();
	}
	return false;
}

bool UStrixNetworkFacade::IsMasterServerConnectionValid()
{
	return m_masterServerConnection != nullptr;
}

void UStrixNetworkFacade::DisconnectMasterServer()
{
	if (m_masterServerConnection)
	{
		m_masterServerConnection->Disconnect();
		m_masterServerConnection = nullptr;
	}
}

void UStrixNetworkFacade::SearchNode(int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
	const FStrixNodeSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (IsMasterServerConnectionValid())
	{
		m_masterServerConnection->SearchNode(condition.m_condition, order.m_order, limit, offset,
			[=](strix::client::ingame::network::NodeSearchEventArgs args) {
				TArray<FStrixNode> nodes;
				for (auto node : args.GetNodeInfoCollection())
				{
					nodes.Add(FStrixNode(node));
				}
				successCallback.ExecuteIfBound(nodes);
			}, [failureCallback](strix::client::ingame::network::MasterServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::SearchNodeRoom(int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (IsMasterServerConnectionValid())
	{
		m_masterServerConnection->SearchNodeRoom(condition.m_condition, order.m_order, limit, offset,
			[=](strix::client::ingame::network::NodeRoomSearchEventArgs args) {
				TArray<FStrixNodeRoomInfo> nodeRooms;
				for (auto nodeRoomInfo : args.GetRoomInfoCollection())
				{
					nodeRooms.Add(FStrixNodeRoomInfo(nodeRoomInfo->GetNode(), nodeRoomInfo->GetRoom()));
				}
				successCallback.ExecuteIfBound(nodeRooms);
			}, [failureCallback](strix::client::ingame::network::MasterServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::SearchJoinableNodeRoom(int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (IsMasterServerConnectionValid())
	{
		m_masterServerConnection->SearchJoinableNodeRoom(condition.m_condition, order.m_order, limit, offset,
			[=](strix::client::ingame::network::NodeRoomSearchEventArgs args) {
				TArray<FStrixNodeRoomInfo> nodeRooms;
				for (auto nodeRoomInfo : args.GetRoomInfoCollection())
				{
					nodeRooms.Add(FStrixNodeRoomInfo(nodeRoomInfo->GetNode(), nodeRoomInfo->GetRoom()));
				}
				successCallback.ExecuteIfBound(nodeRooms);
			}, [failureCallback](strix::client::ingame::network::MasterServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::JoinRandomNodeRoom(int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties,
	bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (GetRoomServerConnectionByChannelId(channelId))
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerAlreadyConnected, EStrixErrorCategory::StrixUESDK);
		return;
	}

	if (IsMasterServerConnectionValid())
	{
		m_masterServerConnection->JoinRandomNodeRoom(FStrixPropertyMap::CreateNetworkPropertyMap(memberProperties, FStrixRoomMember::KnownNetworkFieldNames),
		       condition.m_condition,
			pauseNetworkObjects,
			[=](strix::client::ingame::network::RoomServerConnectEventArgs args) {
				TryAddRoomConnection(channelId, args.GetConnection());
			},
			[=](strix::client::ingame::network::RoomContextOpenEventArgs args) {
				auto contextRoomConnection = args.GetRoomContext()->GetConnection().lock();
				auto storedRoomConnextion = GetRoomServerConnectionByChannelId(channelId);

				if (contextRoomConnection != storedRoomConnextion)
				{
					failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerAlreadyConnected, EStrixErrorCategory::StrixUESDK);
					return;
				}
				
				if (TryAddRoomContext(channelId, args.GetRoomContext()))
				{
					successCallback.ExecuteIfBound(channelId);
				}
				else
				{
					failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
				}			
			}, [failureCallback](strix::client::ingame::network::MasterServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}, nullptr, nullptr
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::JoinNodeRoom(int channelId, const FStrixNodeRoomInfo &roomInfo, const FStrixPropertyMap& memberProperties,
	const FString &password, bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{

	std::string host = TCHAR_TO_UTF8(*roomInfo.Node.Host);
	int port = roomInfo.Node.Port;
	strix::net::channel::Protocol protocol = strix::net::channel::ProtocolStringConverter::FromString(TCHAR_TO_UTF8(*roomInfo.Node.Protocol),
		strix::net::channel::Protocol::TCP);
	long long roomId = roomInfo.NodeRoom.Id;
	std::string pw = TCHAR_TO_UTF8(*password);

	auto currentRoomConnection = GetRoomServerConnectionByChannelId(channelId);
	if (currentRoomConnection)
	{
		if (CompareRoomConnections(currentRoomConnection, host, port, protocol))
		{
			JoinRoom(channelId, roomId, memberProperties, password, pauseNetworkObjects, successCallback, failureCallback);
		}
		else
		{
			failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerAlreadyConnected, EStrixErrorCategory::StrixUESDK);
		}

		return;
	}

	if (IsMasterServerConnectionValid())
	{
		m_strixClient->ConnectToRoomServer(host, port, protocol,
			[=](strix::client::ingame::network::RoomServerConnectEventArgs args)
			{
				TryAddRoomConnection(channelId, args.GetConnection());
				std::shared_ptr<strix::client::ingame::network::RoomServerConnection> connection = GetRoomServerConnectionByChannelId(channelId);
				connection->JoinRoom(roomId,
					FStrixPropertyMap::CreateNetworkPropertyMap(memberProperties, FStrixRoomMember::KnownNetworkFieldNames),
					pw,
					pauseNetworkObjects,
					[=](strix::client::ingame::network::RoomContextOpenEventArgs open)
					{
						if (TryAddRoomContext(channelId, open.GetRoomContext()))
						{
							successCallback.ExecuteIfBound(channelId);
						}
						else
						{
							failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
						}
					},
					[=](strix::client::ingame::network::RoomServerConnectionFailureEventArgs failed)
					{
						failureCallback.ExecuteIfBound(failed.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(failed.GetErrorCategory()));
					}
				);
			},
			[=](strix::client::ingame::network::ServerConnectFailedEventArgs failed)
			{
				failureCallback.ExecuteIfBound(failed.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(failed.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::CreateNodeRoom(int channelId,	const FStrixPropertyMap& roomProperties, const FStrixPropertyMap& memberProperties,
	bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto currentRoomConnection = GetRoomServerConnectionByChannelId(channelId);
	if (currentRoomConnection)
	{
		CreateRoom(channelId, roomProperties, memberProperties, pauseNetworkObjects, successCallback, failureCallback);
		return;
	}

	strix::client::ingame::network::node::NodeSelectionStrategyPtr strategy =
		std::make_shared<strix::client::ingame::network::node::RandomNodeSelectionStrategy>();

	if (IsMasterServerConnectionValid())
	{
		m_masterServerConnection->SetNodeSelectionStrategy(strategy);

		m_masterServerConnection->ConnectToRoomServer(
			[=](strix::client::ingame::network::RoomServerConnectEventArgs args)
			{
				TryAddRoomConnection(channelId, args.GetConnection());
				std::shared_ptr<strix::client::ingame::network::RoomServerConnection> connection = GetRoomServerConnectionByChannelId(channelId);

				connection->CreateRoom(FStrixPropertyMap::CreateNetworkPropertyMap(roomProperties, FStrixRoom::KnownNetworkFieldNames),
					FStrixPropertyMap::CreateNetworkPropertyMap(memberProperties, FStrixRoomMember::KnownNetworkFieldNames),
					pauseNetworkObjects,
					[=](strix::client::ingame::network::RoomContextOpenEventArgs open)
					{
						if (TryAddRoomContext(channelId, open.GetRoomContext()))
						{
							successCallback.ExecuteIfBound(channelId);
						}
						else
						{
							failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
						}
					},
					[&](strix::client::ingame::network::RoomServerConnectionFailureEventArgs failed)
					{
						failureCallback.ExecuteIfBound(failed.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(failed.GetErrorCategory()));
					}
				);
			},
			[&](strix::client::ingame::network::ServerConnectFailedEventArgs failed)
			{
				failureCallback.ExecuteIfBound(failed.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(failed.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::ConnectToRoomServer(const FString &host, int32 port, const FString &protocol, int channelId, const FStrixRoomServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (GetRoomServerConnectionByChannelId(channelId))
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerAlreadyConnected, EStrixErrorCategory::StrixUESDK);
		return;
	}

	if (m_strixClient)
	{
		strix::net::channel::Protocol strixProtocol = strix::net::channel::ProtocolStringConverter::FromString(TCHAR_TO_UTF8(*protocol), strix::net::channel::Protocol::TCP);

		m_strixClient->ConnectToRoomServer(TCHAR_TO_UTF8(*host), port, strixProtocol,
			[=](strix::client::ingame::network::RoomServerConnectEventArgs args) {
				if(TryAddRoomConnection(channelId, args.GetConnection()))
				{
					successCallback.ExecuteIfBound(channelId);
				}
				else
				{
					failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerAlreadyConnected, EStrixErrorCategory::StrixUESDK);
				}
			}, [failureCallback](strix::client::ingame::network::ServerConnectFailedEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
}

bool UStrixNetworkFacade::IsRoomServerConnected(int32 channelId)
{
	auto connection = m_roomConnectionsByChannelId.find(channelId);
	if (connection != m_roomConnectionsByChannelId.end())
	{
		return connection->second->IsOpen();
	}
	return false;
}

void UStrixNetworkFacade::DisconnectRoomServer(int channelId)
{
	strix::client::ingame::network::RoomServerConnectionPtr connection = GetRoomServerConnectionByChannelId(channelId);
	if (connection)
	{
		connection->Disconnect();
	}
}


void UStrixNetworkFacade::JoinRoom(int32 channelId, int32 roomId, const FStrixPropertyMap& memberProperties, const FString &password,
	bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto existingRoomContext = GetRoomContextByChannelId(channelId);
	if (existingRoomContext)
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
		return;
	}

	auto roomConnection = GetRoomServerConnectionByChannelId(channelId);
	if (roomConnection && roomConnection->IsOpen())
	{
		std::string convertedPassword = TCHAR_TO_UTF8(*password);

		roomConnection->JoinRoom((long long)roomId, FStrixPropertyMap::CreateNetworkPropertyMap(memberProperties, FStrixRoomMember::KnownNetworkFieldNames),
			convertedPassword, pauseNetworkObjects,
			[=](strix::client::ingame::network::RoomContextOpenEventArgs args) {
				if (TryAddRoomContext(channelId, args.GetRoomContext()))
				{
					successCallback.ExecuteIfBound(channelId);
				}
				else
				{
					failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
				}			
			}, [failureCallback](strix::client::ingame::network::RoomServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::CreateRoom(int32 channelId, const FStrixPropertyMap& roomProperties, const FStrixPropertyMap& memberProperties,
	bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto existingRoomContext = GetRoomContextByChannelId(channelId);
	if (existingRoomContext)
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
		return;
	}

	auto roomConnection = GetRoomServerConnectionByChannelId(channelId);
	if (roomConnection && roomConnection->IsOpen())
	{
		roomConnection->CreateRoom(FStrixPropertyMap::CreateNetworkPropertyMap(roomProperties, FStrixRoom::KnownNetworkFieldNames),
			FStrixPropertyMap::CreateNetworkPropertyMap(memberProperties, FStrixRoomMember::KnownNetworkFieldNames), pauseNetworkObjects,
			[=](strix::client::ingame::network::RoomContextOpenEventArgs args) {
				if (TryAddRoomContext(channelId, args.GetRoomContext()))
				{
					successCallback.ExecuteIfBound(channelId);
				}
				else
				{
					failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
				}			
			}, [failureCallback](strix::client::ingame::network::RoomServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::SearchRoom(int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomConnection = GetRoomServerConnectionByChannelId(channelId);
	if (roomConnection && roomConnection->IsOpen())
	{
		roomConnection->SearchRoom(condition.m_condition, order.m_order, limit, offset,
			[=](strix::client::ingame::network::RoomSearchEventArgs args) {
				TArray<FStrixRoom> rooms;
				for (auto room : args.GetRoomInfoCollection())
				{
					rooms.Add(FStrixRoom(room));
				}
				successCallback.ExecuteIfBound(rooms);
			}, [failureCallback](strix::client::ingame::network::RoomServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::SearchJoinableRoom(int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order, const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomConnection = GetRoomServerConnectionByChannelId(channelId);
	if (roomConnection && roomConnection->IsOpen())
	{
		roomConnection->SearchJoinableRoom(condition.m_condition, order.m_order, limit, offset,
			[=](strix::client::ingame::network::RoomSearchEventArgs args) {
				TArray<FStrixRoom> rooms;
				for (auto room : args.GetRoomInfoCollection())
				{
					rooms.Add(FStrixRoom(room));
				}
				successCallback.ExecuteIfBound(rooms);
			}, [failureCallback](strix::client::ingame::network::RoomServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::JoinRandomRoom(int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties,
	bool pauseNetworkObjects, const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomConnection = GetRoomServerConnectionByChannelId(channelId);
	if (roomConnection && roomConnection->IsOpen())
	{
		roomConnection->JoinRandomRoom(FStrixPropertyMap::CreateNetworkPropertyMap(memberProperties, FStrixRoomMember::KnownNetworkFieldNames), condition.m_condition, pauseNetworkObjects,
			[=](strix::client::ingame::network::RoomContextOpenEventArgs args) {
				if (TryAddRoomContext(channelId, args.GetRoomContext()))
				{
					successCallback.ExecuteIfBound(channelId);
				}
				else
				{
					failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextAlreadyExists, EStrixErrorCategory::StrixUESDK);
				}			
			}, [failureCallback](strix::client::ingame::network::RoomServerConnectionFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomServerNotConnected, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::LeaveRoom(int32 channelId, const FStrixRoomLeaveDelegate & successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->Leave(
			[=](strix::client::ingame::network::RoomLeaveEventArgs args) {
				successCallback.ExecuteIfBound(channelId);
			}, [failureCallback](strix::client::ingame::network::RoomContextFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextDoesNotExist, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::DeleteRoom(int32 channelId, const FStrixRoomDeleteDelegate & successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->DeleteRoom(
			[=](strix::client::ingame::network::RoomDeleteEventArgs args) {
				successCallback.ExecuteIfBound(channelId);
			}, [failureCallback](strix::client::ingame::network::RoomContextFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextDoesNotExist, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::SetRoom(int32 channelId, const FStrixPropertyMap& roomProperties, const FStrixRoomSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->SetRoom(FStrixPropertyMap::CreateNetworkPropertyMap(roomProperties, FStrixRoom::KnownNetworkFieldNames),
			[=](strix::client::ingame::network::RoomSetEventArgs args) {
				successCallback.ExecuteIfBound(channelId);
			}, [failureCallback](strix::client::ingame::network::RoomContextFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextDoesNotExist, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::SetRoomMember(int32 channelId, const FStrixPropertyMap& memberProperties, const FStrixRoomMemberSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->SetRoomMember(FStrixPropertyMap::CreateNetworkPropertyMap(memberProperties, FStrixRoomMember::KnownNetworkFieldNames),
			[=](strix::client::ingame::network::RoomMemberSetEventArgs args) {
				successCallback.ExecuteIfBound(channelId);
			}, [failureCallback](strix::client::ingame::network::RoomContextFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextDoesNotExist, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::KickRoomMember(int32 channelId, const FStrixRoomMember& member, const FStrixRoomMemberKickDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->KickRoomMember(member.m_roomMember->GetUid(),
			[=](strix::client::ingame::network::RoomMemberKickEventArgs args) {
				successCallback.ExecuteIfBound(channelId);
			}, [failureCallback](strix::client::ingame::network::RoomContextFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextDoesNotExist, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::Relay(int32 channelId, const FStrixRelayArg& message,
	const FStrixRoomRelayDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->SendRoomRelay(message.m_objectPtr,
			[=](strix::client::ingame::network::RoomRelayEventArgs args) {
				successCallback.ExecuteIfBound(channelId);
			}, [failureCallback](strix::client::ingame::network::RoomContextFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextDoesNotExist, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::DirectRelay(int32 channelId, const FStrixRelayArg& message, const FStrixRoomMember& to,
	const FStrixRoomDirectRelayDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->SendRoomDirectRelay(to.m_roomMember->GetUid(), message.m_objectPtr,
			[=](strix::client::ingame::network::RoomDirectRelayEventArgs args) {
				successCallback.ExecuteIfBound(channelId);
			}, [failureCallback](strix::client::ingame::network::RoomContextFailureEventArgs args) {
				failureCallback.ExecuteIfBound(args.GetErrorCode(), StrixErrorCodeConverter::ConvertStrixErrorCategoryToUEEnum(args.GetErrorCategory()));
			}
		);
	}
	else
	{
		failureCallback.ExecuteIfBound(StrixUESDKErrorCode::RoomContextDoesNotExist, EStrixErrorCategory::StrixUESDK);
	}
}

void UStrixNetworkFacade::RegisterRpcProcedure(int32 channelId, long long networkInstanceId, strix::client::ingame::rpc::RpcProcedurePtr rpcProcedure)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->GetRpcManager()->RegisterRpc(networkInstanceId, rpcProcedure);
	}
}

void UStrixNetworkFacade::DeregisterRpcProcedures(int32 channelId, long long networkInstanceId)
{
	auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		roomContext->GetRpcManager()->DeregisterRpc(networkInstanceId);
	}
}

void UStrixNetworkFacade::SendRpc(int32 channelId, strix::client::core::UIDPtr to, long long networkObjectId,
	int procedureHash, const TArray<FStrixRelayArg>& args)
{
	const auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		auto rpcManager = roomContext->GetRpcManager();

		if (rpcManager)
		{
			strix::net::object::ObjectVector rpcArgs;
			for (const auto& rpcArg : args)
			{
				rpcArgs.Get().push_back(rpcArg.m_objectPtr);
			}

			rpcManager->SendRpc(to, networkObjectId, procedureHash, rpcArgs);
		}
	}
}

void UStrixNetworkFacade::SendRpcToRoomOwner(int32 channelId, long long networkObjectId, int procedureHash,
	const TArray<FStrixRelayArg>& args)
{
	const auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		auto rpcManager = roomContext->GetRpcManager();

		if (rpcManager)
		{
			strix::net::object::ObjectVector rpcArgs;
			for (const auto& rpcArg : args)
			{
				rpcArgs.Get().push_back(rpcArg.m_objectPtr);
			}

			rpcManager->SendRpcToRoomOwner(networkObjectId, procedureHash, rpcArgs);
		}
	}
}

void UStrixNetworkFacade::SendRpcToOtherMembers(int32 channelId, long long networkObjectId, int procedureHash,
	const TArray<FStrixRelayArg>& args)
{
	const auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		auto rpcManager = roomContext->GetRpcManager();

		if (rpcManager)
		{
			strix::net::object::ObjectVector rpcArgs;
			for (const auto& rpcArg : args)
			{
				rpcArgs.Get().push_back(rpcArg.m_objectPtr);
			}

			rpcManager->SendRpcToOtherMembers(networkObjectId, procedureHash, rpcArgs);
		}
	}
}

void UStrixNetworkFacade::SendRpcToAll(int32 channelId, long long networkObjectId, int procedureHash,
	const TArray<FStrixRelayArg>& args)
{
	const auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		auto rpcManager = roomContext->GetRpcManager();

		if (rpcManager)
		{
			strix::net::object::ObjectVector rpcArgs;
			for (const auto& rpcArg : args)
			{
				rpcArgs.Get().push_back(rpcArg.m_objectPtr);
			}

			rpcManager->SendRpcToAll(networkObjectId, procedureHash, rpcArgs);
		}
	}
}

void UStrixNetworkFacade::PauseNetworkObjectManager(int32 channelId)
{
	const auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		auto networkObjectManager = roomContext->GetNetworkObjectManager();

		if (networkObjectManager)
		{
			networkObjectManager->Pause();
		}
	}
}

void UStrixNetworkFacade::UnpauseNetworkObjectManager(int32 channelId)
{
	const auto roomContext = GetRoomContextByChannelId(channelId);
	if (roomContext)
	{
		auto networkObjectManager = roomContext->GetNetworkObjectManager();

		if (networkObjectManager)
		{
			networkObjectManager->Unpause();
		}
	}
}

strix::client::core::util::DelegateList<>::Handle UStrixNetworkFacade::AddRoomContextOpenHandler(RoomContextOpenHandler handler)
{
	return m_roomContextOpenDelegate.Add(std::move(handler));
}

void UStrixNetworkFacade::RemoveRoomContextOpenHandler(strix::client::core::util::DelegateList<>::Handle handle)
{
	m_roomContextOpenDelegate.Remove(handle);
}

UStrixNetworkFacade * UStrixNetworkFacade::GetInstance(const UObject* worldContextObject)
{
#if WITH_EDITOR
#if ENGINE_MINOR_VERSION > 21
	int32 PIEId = PIEHelper::GetPIEIdFromWorldContextObject(worldContextObject);
#else
	int32 PIEId = (GPlayInEditorID != -1) ? GPlayInEditorID : PIEHelper::GetPIEIdFromWorldContextObject(worldContextObject);
#endif
	auto it = PIEInstances.find(PIEId);

	if (it != PIEInstances.end())
		return it->second;
	return nullptr;
#else
	return SingleInstance;
#endif
}

void UStrixNetworkFacade::RemoveInstance(UStrixNetworkFacade* instance)
{
	if (instance->GetPIEInstanceId() != -1)
	{
		PIEInstances.erase(instance->GetPIEInstanceId());
	}
	else
	{
		SingleInstance = nullptr;
	}
}

void UStrixNetworkFacade::OnActorsInitialized(const UWorld::FActorsInitializedParams &params)
{
#if WITH_EDITOR
	int32 PIEInstanceId = (GPlayInEditorID != -1) ? GPlayInEditorID : PIEHelper::GetPIEIdFromGameInstance(params.World->GetGameInstance());
	if (GetPIEInstanceId() != PIEInstanceId)
		return;
#endif
	
	SetTicker(params.World);
}

void UStrixNetworkFacade::SetTicker(UWorld* world)
{
	if (IsValid(world))
	{
		world->OnTickDispatch().AddUObject(this, &UStrixNetworkFacade::OnTick);
	}
}

void UStrixNetworkFacade::InitBase(UGameInstance* gameInstance)
{
	SetTicker(gameInstance->GetWorld());
	m_actorsInitializedDelegate = FWorldDelegates::OnWorldInitializedActors.AddUObject(this, &UStrixNetworkFacade::OnActorsInitialized);

	strix::net::logging::LogManager::GetInstance().SetHandler(new strix::net::logging::UELogHandler(), true);
	for (auto entry : strix::net::logging::LogManager::GetInstance().GetLoggerMap())
	{
		entry.second->SetLogLevel(strix::net::logging::LogLevel::Trace);
	}

	SetInstance(gameInstance);

	// Load ini file for Strix types
	TypeIdConfigFilename = UETypeRegistry::DefaultConfigFilename;
	FConfigCacheIni::LoadGlobalIniFile(TypeIdConfigFilename, TEXT("Game"), 0, true, false, true, *FPaths::ProjectConfigDir());

	// Load old ini file for Strix types
	TypeIdConfigFilename = UETypeRegistry::BackwardsCompatibleConfigFilename;
	FConfigCacheIni::LoadGlobalIniFile(TypeIdConfigFilename, TEXT("Game"), 0, true, false, true, *FPaths::ProjectConfigDir());

	m_typeRegistry = std::make_shared<UETypeRegistry>();
	m_typeRegistry->Init(gameInstance);

	for (auto entry : m_typeRegistry->GetRegisteredSpawners())
	{
		m_spawnerClasses.Add(entry.second->GetActorClass());
	}

	UEObjectsSerializers::Init();
}

void UStrixNetworkFacade::SetInstance(UGameInstance* gameInstance)
{
#if ENGINE_MINOR_VERSION < 20
	gameInstance->GetWorld()->ExtraReferencedObjects.Add(this);
#else
	gameInstance->RegisterReferencedObject(this);
#endif

#if WITH_EDITOR
#if ENGINE_MINOR_VERSION > 21
	int32 PIEInstanceId = PIEHelper::GetPIEIdFromGameInstance(gameInstance);
#else
	int32 PIEInstanceId = (GPlayInEditorID != -1) ? GPlayInEditorID : PIEHelper::GetPIEIdFromGameInstance(gameInstance);
#endif
	this->SetPIEInstanceId(PIEInstanceId);
	PIEInstances.insert(std::make_pair(PIEInstanceId, this));
#else
	this->SetPIEInstanceId(-1);
	SingleInstance = this;
#endif
}

void UStrixNetworkFacade::OnTick(float deltaTime)
{
	if (m_strixClient)
		m_strixClient->Process();
}

void UStrixNetworkFacade::StopBase()
{
	// Check this is the real instance in the map before removing
	if (PIEInstances.end() != PIEInstances.find(GetPIEInstanceId()) && PIEInstances.at(GetPIEInstanceId()) == this)
	{
		UStrixNetworkFacade::RemoveInstance(this);
	}
	else
	{
		// Log if this instance has been removed already
		UE_LOG(LogTemp, Warning, TEXT("Tried to remove instance from PIE map but instance already removed"));
	}

	if (m_actorsInitializedDelegate.IsValid())
	{
		FWorldDelegates::OnWorldInitializedActors.Remove(m_actorsInitializedDelegate);
	}

	if (m_strixClient)
	{
		if (m_masterServerConnection)
		{
			m_masterServerConnection->RemoveMasterServerConnectionClosedHandler(m_masterServerConnectionClosedHandle);
			m_masterServerConnection = nullptr;
		}

		for (const auto& entry : m_roomConnectionsByChannelId)
		{
			if (entry.second)
			{
				auto handleIt = m_roomServerConnectionClosedHandles.find(entry.first);
				if (handleIt != m_roomServerConnectionClosedHandles.end())
				{
					entry.second->RemoveRoomServerConnectionClosedHandler(handleIt->second);
				}
			}
		}

		for (const auto& entry : m_roomContextsByChannelId)
		{
			if (entry.second)
			{
				auto handleIt = m_roomContextInvalidateHandles.find(entry.first);
				if (handleIt != m_roomContextInvalidateHandles.end())
				{
					entry.second->RemoveRoomContextInvalidateHandler(handleIt->second);
				}
			}
		}

		m_strixClient = nullptr;
	}
	m_spawnerClasses.Empty();
}

void UStrixNetworkFacade::RemoveMasterServerConnection()
{
	m_masterServerConnection = nullptr;

	UE_LOG(LogStrix, Log, TEXT("Master server connection closed."));
}

bool UStrixNetworkFacade::TryAddRoomConnection(int32 channelId,	strix::client::ingame::network::RoomServerConnectionPtr roomConnection)
{
	auto it = m_roomConnectionsByChannelId.find(channelId);
	if (it != m_roomConnectionsByChannelId.end())
	{
		UE_LOG(LogStrix, Warning, TEXT("Room connection with id %d already exists."), channelId);
		return false;
	}

	m_roomConnectionsByChannelId.insert(std::make_pair(channelId, roomConnection));

	m_roomServerConnectionClosedHandles.emplace(std::make_pair(channelId, roomConnection->AddRoomServerConnectionClosedHandler(
		[=](strix::client::ingame::network::RoomServerConnectionClosedEventArgs args) {
			RemoveRoomServerConnection(channelId);
		}
	)));

	return true;
}

strix::client::ingame::network::RoomServerConnectionPtr UStrixNetworkFacade::GetRoomServerConnectionByChannelId(int channelId)
{
	auto it = m_roomConnectionsByChannelId.find(channelId);
	if (it != m_roomConnectionsByChannelId.end())
	{
		return it->second;
	}
	return nullptr;
}

void UStrixNetworkFacade::RemoveRoomServerConnection(int channelId)
{
	m_roomConnectionsByChannelId.erase(channelId);
	UE_LOG(LogStrix, Log, TEXT("Room server connection closed on channel %d."), channelId);
}

bool UStrixNetworkFacade::TryAddRoomContext(int32 channelId, strix::client::ingame::network::RoomContextPtr roomContext)
{
	auto it = m_roomContextsByChannelId.find(channelId);
	if (it != m_roomContextsByChannelId.end())
	{
		UE_LOG(LogStrix, Warning, TEXT("Room context with id %d already exists."), channelId);
		return false;
	}

	m_roomContextsByChannelId.insert(std::make_pair(channelId, roomContext));

	m_roomContextInvalidateHandles.emplace(std::make_pair(channelId, roomContext->AddRoomContextInvalidateHandler(
		[=](strix::client::ingame::network::RoomContextInvalidateEventArgs args) {
			RemoveRoomContext(channelId);
		}
	)));

	RegisterObjectTypesOnRoomContext(roomContext);
	m_roomContextOpenDelegate(channelId, roomContext);

	return true;
}

void UStrixNetworkFacade::RemoveRoomContext(int32 channelId)
{
	m_roomContextsByChannelId.erase(channelId);

	UE_LOG(LogStrix, Log, TEXT("Room context removed on channel %d."), channelId);
}

void UStrixNetworkFacade::RegisterObjectTypesOnRoomContext(strix::client::ingame::network::RoomContextPtr roomContext)
{
	strix::client::ingame::object::NetworkObjectManagerPtr networkObjectManager = roomContext->GetNetworkObjectManager();

	if (networkObjectManager)
	{
		for (auto spawner : m_typeRegistry->GetRegisteredSpawners())
		{
			networkObjectManager->RegisterSpawner(spawner.first, spawner.second);
		}
	}
}

bool UStrixNetworkFacade::CompareRoomConnections(strix::client::ingame::network::RoomServerConnectionPtr roomConnection,
	const std::string& host, int32 port, const strix::net::channel::Protocol &protocol)
{
	return (roomConnection->GetHost().compare(host) == 0 && roomConnection->GetPortNumber() == port && roomConnection->GetProtocol() == protocol);
}

bool UStrixNetworkFacade::IsRoomOwner(int channelId)
{
	auto context = m_roomContextsByChannelId.find(channelId);
	if(context != m_roomContextsByChannelId.end())
	{
		return context->second->IsRoomOwner();
	}
	return false;
}

FStrixRoom UStrixNetworkFacade::GetCurrentRoom(int channelId)
{
	auto context = m_roomContextsByChannelId.find(channelId);
	if(context != m_roomContextsByChannelId.end())
	{
		auto matchRoomClient = context->second->GetMatchRoomClient();
		if(matchRoomClient)
		{
			auto roomData = matchRoomClient->GetMatchRoomData();
			if(roomData)
			{
				return FStrixRoom(std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoom>(
					roomData->GetMatchRoom()));
			}
		}
	}
	return FStrixRoom();
}

FStrixRoomMember UStrixNetworkFacade::GetCurrentRoomMember(int channelId)
{
	auto context = m_roomContextsByChannelId.find(channelId);
	if (context != m_roomContextsByChannelId.end())
	{
		auto matchRoomClient = context->second->GetMatchRoomClient();
		if (matchRoomClient)
		{
			auto roomData = matchRoomClient->GetMatchRoomData();
			if (roomData)
			{
				return FStrixRoomMember(std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(
					roomData->GetSelfMatchRoomMember()));
			}
		}
	}
	return FStrixRoomMember();
}

FStrixRoomMember UStrixNetworkFacade::GetCurrentRoomMemberById(int channelId, int32 memberId)
{
	strix::client::room::model::RoomMemberMap members;
	auto context = m_roomContextsByChannelId.find(channelId);
	if (context != m_roomContextsByChannelId.end())
	{
		auto matchRoomClient = context->second->GetMatchRoomClient();
		if (matchRoomClient)
		{
			auto roomData = matchRoomClient->GetMatchRoomData();
			if (roomData)
			{
				members = roomData->GetRoomMembers();
			}
		}
	}
	if (members.size() > 0)
	{
		for (auto it = members.begin(); it != members.end(); ++it)
		{
			if(it->second->GetPrimaryKey() == memberId)
			{
				return FStrixRoomMember(std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(
					it->second));
			}
		}
	}
	return FStrixRoomMember();
}

TArray<FStrixRoomMember> UStrixNetworkFacade::GetCurrentRoomMembers(int channelId)
{
	strix::client::room::model::RoomMemberMap members;
	auto context = m_roomContextsByChannelId.find(channelId);
	if (context != m_roomContextsByChannelId.end())
	{
		auto matchRoomClient = context->second->GetMatchRoomClient();
		if (matchRoomClient)
		{
			auto roomData = matchRoomClient->GetMatchRoomData();
			if (roomData)
			{
				members = roomData->GetRoomMembers();
			}
		}
	}
	TArray<FStrixRoomMember> fMembers;
	if(members.size() > 0)
	{
		for (auto it = members.begin(); it != members.end(); ++it)
		{
			fMembers.Emplace(FStrixRoomMember(std::static_pointer_cast<strix::client::match::room::model::CustomizableMatchRoomMember>(
				it->second)));
		}
	}
	return fMembers;
}

void UStrixNetworkFacade::GetNodeCount(const FStrixNodeGetCountDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback)
{
	if (!IsMasterServerConnectionValid())
	{
        failureCallback.ExecuteIfBound(StrixUESDKErrorCode::MasterServerNotConnected, EStrixErrorCategory::StrixUESDK);
        return;
    }

    m_masterServerConnection->GetNodeCount(
		[=](strix::client::core::request::RequestResult<strix::client::core::message::GetCountResponsePtr> result) {
			int count = result.m_result->GetCount();
			successCallback.ExecuteIfBound((int32)count);
		},
		[=](strix::client::core::request::RequestResult<strix::client::core::message::FailureMessagePtr> result) {
			failureCallback.ExecuteIfBound(result.m_result->GetErrorCode(), EStrixErrorCategory::StrixClient);
		}
	);
}

AActor* UStrixNetworkFacade::GetObjectFromNetworkId(int64 networkId, int channel)
{
	auto context = m_roomContextsByChannelId.find(channel);
	if(context != m_roomContextsByChannelId.end())
	{
		auto networkObject = context->second->GetNetworkObjectManager()->FindInstance(networkId);
		if(networkObject)
		{
			std::shared_ptr<UENetworkObject> ueNetworkObject = std::static_pointer_cast<UENetworkObject>(networkObject);
			return ueNetworkObject->GetActor();
		}
	}

	return nullptr;
}

