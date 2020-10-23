/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "StrixNetworkFacade.h"
#include "Adapter/StrixPropertyMap.h"
#include "Adapter/StrixCondition.h"
#include "Adapter/StrixOrder.h"
#include "Adapter/StrixRelayArg.h"
#include "Adapter/StrixNetworkId.h"
#include "Components/StrixReplicatorComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "StrixBlueprintFunctionLibrary.generated.h"

/** Class exposing the Strix function definitions to editor blueprints.
 *  Also contains some helper functions (conversions, condition building etc.).
 */
UCLASS()
class STRIXSDK_API UStrixBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Initialize the Strix network
	 *
	 *  The network must be initialized for Strix network functions to work, so this should
	 *  be the first node you call
	 *  @param	applicationId	The unique application ID
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static void InitializeStrixNetwork(const UObject* WorldContextObject, const FString &applicationId);

	/** Initialize the Strix network using HTTP token
	 *
	 *  The network must be initialized for Strix network functions to work, so this should
	 *  be the first node you call. This version takes an HTTP token
	 *  @param	applicationId	The unique application ID
	 *  @param	accessToken	The access token
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static void InitializeStrixNetworkWithHttpAccessToken(const UObject* WorldContextObject, const FString &applicationId, const FString &accessToken);

	/** Stop the Strix network	
	 *
	 *  Stops the network functionality. Use when exiting the game
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static void StopStrixNetwork(const UObject* WorldContextObject);

	/** Check if the Strix network is initialized
	 *  @returns	Whether the Strix network is initialized or not
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool IsInitialized(const UObject* WorldContextObject);

	/** Check if the network object manager is paused
	 *  @param	channelId	The channel to check on
	 *  @returns	True if paused, False if not or uninitialized
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool IsNetworkObjectManagerPaused(const UObject* WorldContextObject, int32 channelId);

	/** Connect to master server
	 *
	 *  Connects to a Strix Cloud master server, allowing you to search and connect to the room servers managed
	 *  by the master server. Required for functions such as JoinRandomNodeRoom
	 *  @param	host	The host url
	 *  @param	port	The port number to connect to
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  
	 *  #### Possible Error codes: ####
	 *  
	 *  
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	 *  StrixUESDKErrorCode::MasterServerAlreadyConnected |	1    | The connection is already established
	 *  StandardErrorCode::InternalError                  | 1    | Internal server error. This can be caused by a bug or some other problem on the server and should be reported to the developers
	 *  StandardErrorCode::RequestTimeout                 | 9    | The request timed out
	 *  AuthErrorCode::InvalidCredentialsType             | 1002 | Credentials type does not match the server authentication configuration
	 *  AuthErrorCode::UnsupportedLibraryVersion          | 1006 | Current client library is not supported by the server. This can happen if the client version is too old. To fix this error, update the Strix SDK to the latest version
	 *  AuthErrorCode::InvalidApplicationToken            | 1007 | Application ID token provided via applicationId does not match the one on the server
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "successCallback, failureCallback"))
	static void ConnectToMasterServer(const UObject* WorldContextObject, const FString &host, int32 port, const FStrixMasterServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Check if there is an open master server connection
	 *  @returns Whether the master server is connected or not
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool IsMasterServerConnected(const UObject* WorldContextObject);

	/** Close the master server connection
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static void DisconnectMasterServer(const UObject* WorldContextObject);

	/** Search for a room server based on given conditions
	 *  @param	limit	The number of values to return
	 *  @param	offset	The offset into the results from which we will return
	 *  @param	condition	The conditions to match to
	 *  @param	order	The order we return results in
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns A list of FStrixNode%s.=20 that matched the condition
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Code                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------
	 *  StrixUESDKErrorCode::MasterServerNotConnected     | 1    | Not connected to the master server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::InvalidPropertySetting         | 7    | The condition or order was not valid
	 *  StandardErrorCode::RequestTimeout                 | 9    | The request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "condition, order, successCallback, failureCallback"))
	static void SearchNode(const UObject* WorldContextObject, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixNodeSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Search for a room based on given conditions (using the master server connection).
	 *  Returns both room server info and room info.
	 *  @param	limit	The number of values to return
	 *  @param	offset	The offset into the results from which we will return
	 *  @param	condition	The conditions to match to
	 *  @param	order	The order we return results in
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns A list of FStrixNodeRoomInfo%s.=20 that matched the condition
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Code                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------
	 *  StrixUESDKErrorCode::MasterServerNotConnected     | 1    | Not connected to the master server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::InvalidPropertySetting         | 7    | The condition or order was not valid
	 *  StandardErrorCode::RequestTimeout                 | 9    | The request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "condition, order, successCallback, failureCallback"))
	static void SearchNodeRoom(const UObject* WorldContextObject, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Search for a joinable room based on given conditions (using the master server connection).
	 *
	 *  You may construct search conditions from FStrixCondition nodes. Useful for matchmaking or filtering
	 *  server lists from user input. Specifically returns rooms that are not full
	 *  Returns both room server and room info.
	 *  @param	limit	The number of values to return
	 *  @param	offset	The offset into the results from which we will return
	 *  @param	condition	The conditions to match to
	 *  @param	order	The order we return results in
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns A list of FStrixNodeRoomInfo%s.=20 that matched the condition
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Code                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------
	 *  StrixUESDKErrorCode::MasterServerNotConnected     | 1    | Not connected to the master server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::InvalidPropertySetting         | 7    | The condition or order was not valid
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "condition, order, successCallback, failureCallback"))
	static void SearchJoinableNodeRoom(const UObject* WorldContextObject, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixNodeRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Join a random room server and room
	 *  @param	channelId	The channel to connect with
	 *  @param	condition	The condition to match results against
	 *  @param	memberProperties	The property map of this member
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::MasterServerNotConnected     | 1    | Not connected to the master server
	 *  StrixUESDKErrorCode::RoomServerAlreadyConnected   | 101  | Already connected to a room server on this channel
	 *  StrixUESDKErrorCode::RoomContextAlreadyExists     | 102  | Already connected to this room on this channel
	 *  RoomErrorCode::RoomFullOfMembers                  | 5003 | The requested room is full
	 *  RoomErrorCode::RoomNotFound                       | 5004 | Could not find the requested room
	 *  RoomErrorCode::AlreadyInRoom                      | 5007 | The member is already in the room on this channel
	 *  RoomErrorCode::WrongRoomPassword                  | 5008 | The password is not correct
	 *  RoomErrorCode::RoomNotJoinable                    | 5009 | The member does not meet the requirements for this room
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrors::NoSuchProperty                    | 6    | An internal error occured. Contact the dev team
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  StandardErrors::ModelNotFound                     | 10   | An internal error occured. Contact the dev team
	 *  AuthErrorCode::InvalidCredentialsType             | 1002 | Credentials type does not match the server authentication configuration
	 *  AuthErrorCode::UnsupportedLibraryVersion          | 1006 | Current client library is not supported by the server. This can happen if the client version is too old. To fix this error, update the Strix SDK to the latest version
	 *  AuthErrorCode::InvalidApplicationToken            | 1007 | Application ID token provided via applicationId does not match the one on the server
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "condition, memberProperties, successCallback, failureCallback"))
	static void JoinRandomNodeRoom(const UObject* WorldContextObject, int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties, bool pauseNetworkObjects,
		const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Connect to a room server and join the specified room
	 *  @param	channelId	The channel to connect with
	 *  @param	roomInfo	Structure containing information about the room to join (always use one received from other Strix functions)
	 *  @param	memberProperties	The map of this member's properties
	 *  @param	password	The password to use
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::MasterServerNotConnected     | 1    | Not connected to the master server
	 *  StrixUESDKErrorCode::RoomServerAlreadyConnected   | 101  | Already connected to a room server on this channel
	 *  StrixUESDKErrorCode::RoomContextAlreadyExists     | 102  | Already connected to this room on this channel
	 *  RoomErrorCode::RoomFullOfMembers                  | 5003 | The requested room is full
	 *  RoomErrorCode::RoomNotFound                       | 5004 | Could not find the requested room
	 *  RoomErrorCode::AlreadyInRoom                      | 5007 | The member is already in the room on this channel
	 *  RoomErrorCode::WrongRoomPassword                  | 5008 | The password is not correct
	 *  RoomErrorCode::RoomNotJoinable                    | 5009 | The member does not meet the requirements for this room
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrors::NoSuchProperty                    | 6    | An internal error occured. Contact the dev team
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  StandardErrors::ModelNotFound                     | 10   | An internal error occured. Contact the dev team
	 *  AuthErrorCode::InvalidCredentialsType             | 1002 | Credentials type does not match the server authentication configuration
	 *  AuthErrorCode::UnsupportedLibraryVersion          | 1006 | Current client library is not supported by the server. This can happen if the client version is too old. To fix this error, update the Strix SDK to the latest version
	 *  AuthErrorCode::InvalidApplicationToken            | 1007 | Application ID token provided via applicationId does not match the one on the server
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "memberProperties, successCallback, failureCallback"))
	static void JoinNodeRoom(const UObject* WorldContextObject, int channelId, const FStrixNodeRoomInfo &roomInfo,
		const FStrixPropertyMap& memberProperties, const FString &password, bool pauseNetworkObjects,
		const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/*  Create a room on a random room server (requires master server connection)
	 *  @param	channelId	The channel to connect with
	 *  @param	roomProperties	The map of properties to assign the new room
	 *  @param	memberProperties	The map of this member's properties
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::MasterServerNotConnected     | 1    | Not connected to the master server
	 *  StrixUESDKErrorCode::RoomServerAlreadyConnected   | 101  | Already connected to a room server on this channel
	 *  StrixUESDKErrorCode::RoomContextAlreadyExists     | 102  | Already connected to this room on this channel
	 *  RoomErrorCode::RoomNotFound                       | 5004 | Could not leave the current room before creating a new one
	 *  RoomErrorCode::MaxRoomCountReached                | 5011 | There are too many rooms already on this server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrors::NoSuchProperty                    | 6    | An internal error occured. Contact the dev team
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  AuthErrorCode::InvalidCredentialsType             | 1002 | Credentials type does not match the server authentication configuration
	 *  AuthErrorCode::UnsupportedLibraryVersion          | 1006 | Current client library is not supported by the server. This can happen if the client version is too old. To fix this error, update the Strix SDK to the latest version
	 *  AuthErrorCode::InvalidApplicationToken            | 1007 | Application ID token provided via applicationId does not match the one on the server
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "memberProperties, roomProperties, successCallback, failureCallback"))
	static void CreateNodeRoom(const UObject* WorldContextObject,
		int channelId, const FStrixPropertyMap& roomProperties, const FStrixPropertyMap& memberProperties, bool pauseNetworkObjects,
		const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Connect to a room server
	 *
	 *  Room servers host rooms to join
	 *  @param	host	The room server hostname
	 *  @param	port	The port number
	 *  @param	protocol	The protocol name to use (ex. TCP)
	 *  @param	channelId	The channel to connect
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerAlreadyConnected   | 101  | Already connected to a room server on this channel
	 *  AuthErrorCode::InvalidCredentialsType             | 1002 | Credentials type does not match the server authentication configuration
	 *  AuthErrorCode::UnsupportedLibraryVersion          | 1006 | Current client library is not supported by the server. This can happen if the client version is too old. To fix this error, update the Strix SDK to the latest version
	 *  AuthErrorCode::InvalidApplicationToken            | 1007 | Application ID token provided via applicationId does not match the one on the server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "successCallback, failureCallback"))
	static void ConnectToRoomServer(const UObject* WorldContextObject, const FString &host, int32 port, const FString &protocol, int channelId,
		const FStrixRoomServerConnectedDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Check if there is an open room server connection
	 *  @param	channelId	The channel to check
	 *  @returns Whether the room server is connected or not
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool IsRoomServerConnected(const UObject* WorldContextObject, int32 channelId = 0);

	/** Close the master server connection
	 *  @param	channelId	The channel to disconnect
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static void DisconnectRoomServer(const UObject* WorldContextObject, int channelId);

	/** Search for a room on the currently connected room server
	 *
	 *  You may construct search conditions from FStrixCondition nodes. Useful for matchmaking or filtering
	 *  server lists from user input.
	 *  @param	channelId	The channel to use
	 *  @param	limit	The number of search results to return
	 *  @param	offset	The offset into the results from which we return
	 *  @param	condition	The conditions of the search
	 *  @param	order	The order in which to return results
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	A list of FStrixRoom%s.=20 that matched the conditions, or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::InvalidPropertySetting         | 7    | The condition or order was not valid
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "condition, order, successCallback, failureCallback"))
	static void SearchRoom(const UObject* WorldContextObject, int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Join a room on the current room server
	 *  @param	channelId	The channel to use
	 *  @param	roomId	The Id of the room to connect to on the current room server
	 *  @param	memberProperties	The map of this member's properties
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *  @param	password	The password to use
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StrixUESDKErrorCode::RoomContextAlreadyExists     | 102  | Already connected to this room on this channel
	 *  RoomErrorCode::RoomFullOfMembers                  | 5003 | The requested room is full
	 *  RoomErrorCode::RoomNotFound                       | 5004 | Could not find the requested room
	 *  RoomErrorCode::AlreadyInRoom                      | 5007 | The member is already in the room on this channel
	 *  RoomErrorCode::WrongRoomPassword                  | 5008 | The password is not correct
	 *  RoomErrorCode::RoomNotJoinable                    | 5009 | The member does not meet the requirements for this room
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrors::NoSuchProperty                    | 6    | An internal error occured. Contact the dev team
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  StandardErrors::ModelNotFound                     | 10   | An internal error occured. Contact the dev team
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "memberProperties, successCallback, failureCallback"))
	static void JoinRoom(const UObject* WorldContextObject, int32 channelId, int32 roomId, const FStrixPropertyMap& memberProperties, const FString &password, bool pauseNetworkObjects,
		const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/*  Create a room on the currently connected room server
	 *  @param	channelId	The channel to use
	 *  @param	roomProperties	The map of properties to assign the new room
	 *  @param	memberProperties	The map of this member's properties
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StrixUESDKErrorCode::RoomContextAlreadyExists     | 102  | Already connected to this room on this channel
	 *  RoomErrorCode::RoomNotFound                       | 5004 | Could not leave the current room before creating a new one
	 *  RoomErrorCode::MaxRoomCountReached                | 5011 | There are too many rooms already on this server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrors::NoSuchProperty                    | 6    | An internal error occured. Contact the dev team
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "roomProperties, memberProperties, successCallback, failureCallback"))
	static void CreateRoom(const UObject* WorldContextObject, int32 channelId, const FStrixPropertyMap& roomProperties, const FStrixPropertyMap& memberProperties, bool pauseNetworkObjects,
		const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/*  Search for a joinable room based on given conditions.
	 *  
	 *  You may construct search conditions from FStrixCondition nodes. Useful for matchmaking or filtering
	 *  server lists from user input. Specifically returns rooms that are not full
	 *  
	 *  @param	channelId	The channel to use
	 *  @param	limit	The number of search results to return
	 *  @param	offset	The offset into the results from which we return
	 *  @param	condition	The conditions of the search
	 *  @param	order	The order in which to return results
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	A list of FStrixRoom%s.=20 that matched the conditions, or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::InvalidPropertySetting         | 7    | The condition or order was not valid
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "condition, order, successCallback, failureCallback"))
	static void SearchJoinableRoom(const UObject* WorldContextObject, int32 channelId, int32 limit, int32 offset, const FStrixCondition& condition, const FStrixOrder& order,
		const FStrixRoomSearchDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Join a random room on the currently connected room server
	 *  @param	channelId	The channel to use
	 *  @param	condition	The condition to match results against
	 *  @param	memberProperties	The map of properties for this member
	 *  @param	pauseNetworkObjects	Should network object manager be paused (no remote objects replication, experimental)
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StrixUESDKErrorCode::RoomContextAlreadyExists     | 102  | Already connected to this room on this channel
	 *  RoomErrorCode::RoomFullOfMembers                  | 5003 | The requested room is full
	 *  RoomErrorCode::RoomNotFound                       | 5004 | Could not find the requested room
	 *  RoomErrorCode::AlreadyInRoom                      | 5007 | The member is already in the room on this channel
	 *  RoomErrorCode::WrongRoomPassword                  | 5008 | The password is not correct
	 *  RoomErrorCode::RoomNotJoinable                    | 5009 | The member does not meet the requirements for this room
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrors::NoSuchProperty                    | 6    | An internal error occured. Contact the dev team
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  StandardErrors::ModelNotFound                     | 10   | An internal error occured. Contact the dev team
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "condition, memberProperties, successCallback, failureCallback"))
	static void JoinRandomRoom(const UObject* WorldContextObject, int32 channelId, FStrixCondition condition, const FStrixPropertyMap& memberProperties, bool pauseNetworkObjects,
		const FStrixRoomContextOpenDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Leave a room
	 *  @param	channelId	The channel to leave
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  RoomErrorCode::RoomNotFound                       | 5004 | Could not find a room to leave, you may not be in a room
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "successCallback, failureCallback"))
	static void LeaveRoom(const UObject* WorldContextObject, int32 channelId, const FStrixRoomLeaveDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Delete a room
	 *  @param	channelId	The channel to use
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  StandardErrorCode::ModelNotFound                  | 10   | Could not find the room to delete
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "successCallback, failureCallback"))
	static void DeleteRoom(const UObject* WorldContextObject, int32 channelId, const FStrixRoomDeleteDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Set room information
	 *  @param	channelId	The channel to use
	 *  @param	roomProperties	Map of room properties
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | -------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::NoSuchProperty                 | 6    | Could not find one of the properties to set
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  StandardErrorCode::ModelNotFound                  | 10   | Could not find the room to set
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "roomProperties, successCallback, failureCallback"))
	static void SetRoom(const UObject* WorldContextObject, int32 channelId, const FStrixPropertyMap& roomProperties,
		const FStrixRoomSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Get the information about the current room.
	 *  Returns an empty structure if there is no active room on this channel.
	 *  @param	channelId	The channel to use
	 *  @returns	The StrixRoom structure containing information about the current room
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static FStrixRoom GetCurrentRoom(const UObject* WorldContextObject, int channelId);

	/** Set room member information
	 *  @param	channelId	The channel to use
	 *  @param	memberProperties	Map of member properties
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | --------------------------------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::NoSuchProperty                 | 6    | Could not find one of the properties to set
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  RoomErrorCode::RoomMemberNotFound                 | 5005 | Could not find the room member to set
	 *  RoomErrorCode::NotAllowedForOtherRoomMember       | 5006 | You do not have permission to set the properties of a member other than your own
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "memberProperties, successCallback, failureCallback"))
	static void SetRoomMember(const UObject* WorldContextObject, int32 channelId, const FStrixPropertyMap& memberProperties,
		const FStrixRoomMemberSetDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Kick room member
	 *  @param	channelId	The channel to use
	 *  @param	member	The room member to kick
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | ------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  RoomErrorCode::NotRoomOwner                       | 5002 | Cannot kick members if you are not room owner
	 *  RoomErrorCode::RoomMemberNotFound                 | 5005 | Could not find the room member to set
	 *  MatchErrorCode::SelfKickProhibited                | 7000 | Cannot kick yourself
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "member, successCallback, failureCallback"))
	static void KickRoomMember(const UObject* WorldContextObject, int32 channelId, const FStrixRoomMember& member,
		const FStrixRoomMemberKickDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Check if this client is the owner of the current active room
	 *  @param	channelId	The channel to use
	 *  @returns	Whether or not this client is the room owner
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool IsRoomOwner(const UObject* WorldContextObject, int channelId);

	/** Get the information about the current room member (self).
	 *  Returns an empty structure if there is no active room on this channel.
	 *  @param	channelId	The channel to use
	 *  @returns	The StrixRoomMember structure containing information about the current room member
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static FStrixRoomMember GetCurrentRoomMember(const UObject* WorldContextObject, int channelId);

	/**
	 *  Gets the room member with the given member ID.
	 *  @param	channelId	The channel ID to search on
	 *  @param	memberId	The ID of the room member
	 *  @returns	The member with the given ID, or an empty member if not found.
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static FStrixRoomMember GetCurrentRoomMemberById(const UObject* WorldContextObject, int channelId, int32 memberId);

	/** Get the information about the current room members.
	 *  Returns an empty array.
	 *  @param	channelId	The channel to use
	 *  @returns	An array of StrixRoomMember structure containing information about the current room members
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static TArray<FStrixRoomMember> GetCurrentRoomMembers(const UObject* WorldContextObject, int channelId);

	/** Get the number of nodes of the connected master server.
	 *  @param  successCallback Called on a successful get node count response
	 *  @param  failureCallback Called on a failed get node count response
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "successCallback, failureCallback"))
	static void GetNodeCount(const UObject* WorldContextObject, const FStrixNodeGetCountDelegate& successCallback,
		const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Relay message to room
	 *  Relay messages can be used to send specific information to players in the room
	 *  @param	channelId	The channel to use
	 *  @param	message	The message to send
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | ------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  RoomErrorCode::MessageLimitReached                | 5000 | The per second message limit has been reached
	 *  RoomErrorCode::NotRoomMember                      | 5001 | Cannot send relay outside of a room
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "member, successCallback, failureCallback"))
	static void RelayMessage(const UObject* WorldContextObject, int32 channelId, const FStrixRelayArg& message,
		const FStrixRoomRelayDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Relay message to member
	 *  Relay messages can be used to send specific information to players in the room. This function sends to a specific player
	 *  @param	channelId	The channel to use
	 *  @param	message	The message to send
	 *  @param	member	The member to send to
	 *  @param	successCallback	Called on success
	 *  @param	failureCallback	Called on failure
	 *  @returns	The channel ID of the connection or an error code
	 *  
	 *  #### Possible Error codes: ####
	 *
	 *  Name                                              | Code | Description
	 *  ------------------------------------------------- | ---- | ------------------------------------------------------
	 *  StrixUESDKErrorCode::RoomServerNotConnected       | 102  | Not connected to a room server
	 *  StandardErrorCode::LockTimeout                    | 4    | The connection failed due to a server resource timeout
	 *  StandardErrorCode::RequestTimeout                 | 9    | The connection request timed out
	 *  RoomErrorCode::MessageLimitReached                | 5000 | The per second message limit has been reached
	 *  RoomErrorCode::NotRoomMember                      | 5001 | Cannot send relay outside of a room
	 *  RoomErrorCode::RoomMemberNotFound                 | 5005 | Could not find the room member to send to
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "member, successCallback, failureCallback"))
	static void DirectRelayMessage(const UObject* WorldContextObject, int32 channelId, const FStrixRelayArg& message, const FStrixRoomMember& member,
		const FStrixRoomDirectRelayDelegate& successCallback, const FStrixErrorCodeFailureDelegate& failureCallback);

	/** Register an RPC on an actor
	 *  Required to use the specified RPC function on this actor. 
	 *  RPCs are used to perform logic on synced clients.
	 *  Register on both the local and remote actor if you want to use on both
	 *  @param	target The actor to register an RPC from
	 *  @param	functionName The name of the function to register
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "target"))
	static void RegisterStrixRpc(const UObject* WorldContextObject, AActor* target, const FString &functionName);

	/** Send RPC to the owner of the given local object. This will call the given function on the 
	 *  owner
	 *  @param	target	The local object whose owner to send to
	 *  @param	functionName	The name of the method on the target to call
	 *  @param	args The arguments to call with
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "target", AutoCreateRefTerm = "args"))
	static void SendRpcToObjectOwner(const UObject* WorldContextObject, const AActor* target, const FString &functionName, const TArray<FStrixRelayArg>& args);

	/** Send an RPC to the current room owner to be called on the target.
	 *  @param	target	The actor to be called on
	 *  @param	functionName	The method to call on the target
	 *  @param	args	The arguments to call with
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "target", AutoCreateRefTerm = "args"))
	static void SendRpcToRoomOwner(const UObject* WorldContextObject, const AActor* target, const FString &functionName, const TArray<FStrixRelayArg>& args);

	/** Send an RPC to all other members in the room. This will call the given function on the 
	 *  instances registered to receive this RPC
	 *  @param	target	The actor to be called on
	 *  @param	functionName	The method to be called
	 *  @param	args	The arguments to call with
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "target", AutoCreateRefTerm = "args"))
	static void SendRpcToOtherMembers(const UObject* WorldContextObject, const AActor* target, const FString &functionName, const TArray<FStrixRelayArg>& args);

	/** Send an RPC to all members in the room. This will call the given function on the 
	 *  instances registered to receive this RPC
	 *  @param	target	The actor to be called on
	 *  @param	functionName	The method to be called
	 *  @param	args	The arguments to call with
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "target", AutoCreateRefTerm = "args"))
	static void SendRpcToAll(const UObject* WorldContextObject, const AActor* target, const FString &functionName, const TArray<FStrixRelayArg>& args);

	/** Send an RPC to a room member. This will call the given function on the
	 *  instances registered to receive this RPC
	 *  @param	target	The local actor to be called on
	 *  @param	member	The member to send the RPC to
	 *  @param	functionName	The method to be called
	 *  @param	args	The arguments to call with
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "target", AutoCreateRefTerm = "args"))
	static void SendRpc(const UObject* WorldContextObject, const AActor* target, const FStrixRoomMember& member, const FString &functionName, const TArray<FStrixRelayArg>& args);

	/**
	 *  Gets the network ID of the given actor.
	 *  @param	target	The actor to get the ID from.
	 *  @returns	The id of the network object of the actor. ID will be -1 if not found.
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "target"))
	static FStrixNetworkId GetNetworkIdFromObject(const UObject* WorldContextObject, const AActor* target);

	/**
	 *  Gets the actor of the given network ID.
	 *  @param	networkId	The id of the network object whose actor will be returned
	 *  @param	channel	The channel ID to search on
	 *  @returns	The actor reference, or null if not a matching actor was not found.
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static AActor* GetObjectFromNetworkId(const UObject* WorldContextObject, FStrixNetworkId networkId, int channel);

	/**
	 *  Gets the actor of the given network ID.
	 *  @param	networkId	The id of the network object whose actor will be returned
	 *  @param	channel	The channel ID to search on
	 *  @returns	The actor reference, or null if not a matching actor was not found.
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static AActor* GetObjectFromNetworkIdString(const UObject* WorldContextObject, FString networkId, int channel);

	/** Pause the network object manager on specified channel, disabling the replication of remote objects
	 *  @param	channelId	The channel to use
	 *  @remark Does not stop the replication of local objects
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static void PauseNetworkObjectManager(const UObject* WorldContextObject, int32 channelId);

	/** Unpause the network object manager on specified channel, enabling the replication of remote objects
	 *  @param	channelId	The channel to use
	 *  @remark Respawns previously stored remote objects
	 */
	UFUNCTION(BlueprintCallable, Category = "StrixBPLibrary", meta = (WorldContext = "WorldContextObject"))
	static void UnpauseNetworkObjectManager(const UObject* WorldContextObject, int32 channelId);

	/** Try to get the value of a byte property from a StrixPropertyMap
	 *  @param	strixStructure	The map to get from
	 *  @param	propertyName	The name of the property
	 *  @param	result	The success output value, true if successful, else false
	 *  @param	value	The output value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static void TryGetByteProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, uint8& value);

	/** Try to get the value of a bool property from a StrixPropertyMap
	 *  @param	strixStructure	The map to get from
	 *  @param	propertyName	The name of the property
	 *  @param	result	The success output value, true if successful, else false
	 *  @param	value	The output value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static void TryGetBoolProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, bool& value);

	/** Try to get the value of an int property from a StrixPropertyMap
	 *  @param	strixStructure	The map to get from
	 *  @param	propertyName	The name of the property
	 *  @param	result	The success output value, true if successful, else false
	 *  @param	value	The output value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static void TryGetIntProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, int32& value);

	/** Try to get the value of a float property from a StrixPropertyMap
	 *  @param	strixStructure	The map to get from
	 *  @param	propertyName	The name of the property
	 *  @param	result	The success output value, true if successful, else false
	 *  @param	value	The output value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static void TryGetFloatProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, float& value);

	/** Try to get the value of a string property from a StrixPropertyMap
	 *  @param	strixStructure	The map to get from
	 *  @param	propertyName	The name of the property
	 *  @param	result	The success output value, true if successful, else false
	 *  @param	value	The output value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static void TryGetStringProperty(const FStrixPropertyMap& strixStructure, FString propertyName, bool& result, FString& value);

	/** Set the value of a byte property in a StrixPropertyMap
	 *  @param	strixStructure	The map to set
	 *  @param	propertyName	The name of the property to set
	 *  @param	value	The value to set
	 *  @returns	The StrixPropertyMap with the property set to specified value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static FStrixPropertyMap SetByteProperty(FStrixPropertyMap strixStructure, FString propertyName, uint8 value);

	/** Set the value of a bool property in a StrixPropertyMap
	 *  @param	strixStructure	The map to set
	 *  @param	propertyName	The name of the property to set
	 *  @param	value	The value to set
	 *  @returns	The StrixPropertyMap with the property set to specified value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static FStrixPropertyMap SetBoolProperty(FStrixPropertyMap strixStructure, FString propertyName, bool value);

	/** Set the value of an int property in a StrixPropertyMap
	 *  @param	strixStructure	The map to set
	 *  @param	propertyName	The name of the property to set
	 *  @param	value	The value to set
	 *  @returns	The StrixPropertyMap with the property set to specified value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static FStrixPropertyMap SetIntProperty(FStrixPropertyMap strixStructure, FString propertyName, int32 value);

	/** Set the value of a float property in a StrixPropertyMap
	 *  @param	strixStructure	The map to set
	 *  @param	propertyName	The name of the property to set
	 *  @param	value	The value to set
	 *  @returns	The StrixPropertyMap with the property set to specified value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static FStrixPropertyMap SetFloatProperty(FStrixPropertyMap strixStructure, FString propertyName, float value);

	/** Set the value of a string property in a StrixPropertyMap
	 *  @param	strixStructure	The map to set
	 *  @param	propertyName	The name of the property to set
	 *  @param	value	The value to set
	 *  @returns	The StrixPropertyMap with the property set to specified value
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter")
	static FStrixPropertyMap SetStringProperty(FStrixPropertyMap strixStructure, FString propertyName, FString value);

	/** Creates a StrixCondition structure that represents an "Equals" condition.
	 *  Accepted value type is bool.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Equals (bool)"))
	static FStrixCondition CreateStrixBoolEqualsCondition(FString fieldName, bool value);

	/** Creates a StrixCondition structure that represents a "Not Equals" condition.
	 *  Accepted value type is bool.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-not equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Not Equals (bool)"))
	static FStrixCondition CreateStrixBoolNotEqualsCondition(FString fieldName, bool value);

	/** Creates a StrixCondition structure that represents an "Equals" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Equals (byte)"))
	static FStrixCondition CreateStrixByteEqualsCondition(FString fieldName, uint8 value);

	/** Creates a StrixCondition structure that represents a "Greater Than" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than (byte)"))
	static FStrixCondition CreateStrixByteGreaterThanCondition(FString fieldName, uint8 value);

	/** Creates a StrixCondition structure that represents a "Greater Than Or Equal To" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than Equals (byte)"))
	static FStrixCondition CreateStrixByteGreaterThanEqualsCondition(FString fieldName, uint8 value);

	/** Creates a StrixCondition structure that represents a "Less Than" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than (byte)"))
	static FStrixCondition CreateStrixByteLessThanCondition(FString fieldName, uint8 value);

	/** Creates a StrixCondition structure that represents a "Less Than Or Equal To" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than Equals (byte)"))
	static FStrixCondition CreateStrixByteLessThanEqualsCondition(FString fieldName, uint8 value);

	/** Creates a StrixCondition structure that represents a "Not Equals" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-not equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Not Equals (byte)"))
	static FStrixCondition CreateStrixByteNotEqualsCondition(FString fieldName, uint8 value);

	/** Creates a StrixCondition structure that represents a "Between Exclusive" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between exclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between (byte, byte)"))
	static FStrixCondition CreateStrixByteBetweenExclusiveCondition(FString fieldName, uint8 left, uint8 right);

	/** Creates a StrixCondition structure that represents a "Between Inclusive" condition.
	 *  Accepted value type is uint8(byte).
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between inclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between Inclusive (byte, byte)"))
	static FStrixCondition CreateStrixByteBetweenInclusiveCondition(FString fieldName, uint8 left, uint8 right);

	/** Creates a StrixCondition structure that represents an "Equals" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Equals (int)"))
	static FStrixCondition CreateStrixIntEqualsCondition(FString fieldName, int32 value);

	/** Creates a StrixCondition structure that represents a "Greater Than" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than (int)"))
	static FStrixCondition CreateStrixIntGreaterThanCondition(FString fieldName, int32 value);

	/** Creates a StrixCondition structure that represents a "Greater Than Or Equal To" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than Equals (int)"))
	static FStrixCondition CreateStrixIntGreaterThanEqualsCondition(FString fieldName, int32 value);

	/** Creates a StrixCondition structure that represents a "Less Than" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than (int)"))
	static FStrixCondition CreateStrixIntLessThanCondition(FString fieldName, int32 value);

	/** Creates a StrixCondition structure that represents a "Less Than Or Equal To" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than Equals (int)"))
	static FStrixCondition CreateStrixIntLessThanEqualsCondition(FString fieldName, int32 value);

	/** Creates a StrixCondition structure that represents a "Not Equals" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-not equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Not Equals (int)"))
	static FStrixCondition CreateStrixIntNotEqualsCondition(FString fieldName, int32 value);

	/** Creates a StrixCondition structure that represents a "Between Exclusive" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between exclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between (int, int)"))
	static FStrixCondition CreateStrixIntBetweenExclusiveCondition(FString fieldName, int32 left, int32 right);

	/** Creates a StrixCondition structure that represents a "Between Inclusive" condition.
	 *  Accepted value type is int.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between inclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between Inclusive (int, int)"))
	static FStrixCondition CreateStrixIntBetweenInclusiveCondition(FString fieldName, int32 left, int32 right);

	/** Creates a StrixCondition structure that represents an "Equals" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Equals (float)"))
	static FStrixCondition CreateStrixFloatEqualsCondition(FString fieldName, float value);

	/** Creates a StrixCondition structure that represents a "Greater Than" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than (float)"))
	static FStrixCondition CreateStrixFloatGreaterThanCondition(FString fieldName, float value);

	/** Creates a StrixCondition structure that represents a "Greater Than Or Equal To" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than Equals (float)"))
	static FStrixCondition CreateStrixFloatGreaterThanEqualsCondition(FString fieldName, float value);

	/** Creates a StrixCondition structure that represents a "Less Than" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than (float)"))
	static FStrixCondition CreateStrixFloatLessThanCondition(FString fieldName, float value);

	/** Creates a StrixCondition structure that represents a "Less Than Or Equal To" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than Equals (float)"))
	static FStrixCondition CreateStrixFloatLessThanEqualsCondition(FString fieldName, float value);

	/** Creates a StrixCondition structure that represents a "Not Equals" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-not equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Not Equals (float)"))
	static FStrixCondition CreateStrixFloatNotEqualsCondition(FString fieldName, float value);

	/** Creates a StrixCondition structure that represents a "Between Exclusive" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between exclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between (float, float)"))
	static FStrixCondition CreateStrixFloatBetweenExclusiveCondition(FString fieldName, float left, float right);

	/** Creates a StrixCondition structure that represents a "Between Inclusive" condition.
	 *  Accepted value type is float.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between inclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between Inclusive (float, float)"))
	static FStrixCondition CreateStrixFloatBetweenInclusiveCondition(FString fieldName, float left, float right);

	/** Creates a StrixCondition structure that represents an "Equals" condition.
	 *  Accepted value type is string.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Equals (string)"))
	static FStrixCondition CreateStrixStringEqualsCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Not Equals" condition.
	 *  Accepted value type is string.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-not equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Not Equals (string)"))
	static FStrixCondition CreateStrixStringNotEqualsCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Contains" condition.
	 *  Accepted value type is string.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-contains-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Contains (string)"))
	static FStrixCondition CreateStrixStringContainsCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents an "Ends With" condition.
	 *  Accepted value type is string.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-ends with-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Ends With (string)"))
	static FStrixCondition CreateStrixStringEndsWithCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Starts With" condition.
	 *  Accepted value type is string.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-starts with-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Starts With (string)"))
	static FStrixCondition CreateStrixStringStartsWithCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents an "Equals" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Equals (field)"))
	static FStrixCondition CreateStrixFieldEqualsCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Greater Than" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than (field)"))
	static FStrixCondition CreateStrixFieldGreaterThanCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Greater Than Or Equal To" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-greater than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Greater Than Equals (field)"))
	static FStrixCondition CreateStrixFieldGreaterThanEqualsCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Less Than" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than (field)"))
	static FStrixCondition CreateStrixFieldLessThanCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Less Than Or Equal To" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-less than equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Less Than Equals (field)"))
	static FStrixCondition CreateStrixFieldLessThanEqualsCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Not Equals" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	value	Value to compare to
	 *  @returns	The StrixCondition structure containing a "field-not equals-value" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Not Equals (field)"))
	static FStrixCondition CreateStrixFieldNotEqualsCondition(FString fieldName, FString value);

	/** Creates a StrixCondition structure that represents a "Between Exclusive" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between exclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between (field, field)"))
	static FStrixCondition CreateStrixFieldBetweenExclusiveCondition(FString fieldName, FString left, FString right);

	/** Creates a StrixCondition structure that represents a "Between Inclusive" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the comparison
	 *  @param	left	Left-hand value to compare to
	 *  @param	right	Right-hand value to compare to
	 *  @returns	The StrixCondition structure containing a "field-between inclusive-left-right" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Between Inclusive (field, field)"))
	static FStrixCondition CreateStrixFieldBetweenInclusiveCondition(FString fieldName, FString left, FString right);

	/** Creates a StrixCondition structure that represents a "Is Null" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the condition
	 *  @returns	The StrixCondition structure containing a "field-is null" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Is Null"))
	static FStrixCondition CreateStrixFieldIsNullCondition(FString fieldName);

	/** Creates a StrixCondition structure that represents a "Is Not Null" condition.
	 *  Accepted value type is a field name.
	 *  @param	fieldName	Field name used for the condition
	 *  @returns	The StrixCondition structure containing a "field-is not null" condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Field Is Not Null"))
	static FStrixCondition CreateStrixFieldIsNotNullCondition(FString fieldName);

	/** Creates a StrixCondition structure that contains other conditions joined by "And".
	 *  Essentially groups the conditions together.
	 *  @param	conditions	Array of conditions used to create the grouping condition
	 *  @returns	The StrixCondition structure containing a "condition1-and-condition2-and..." condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Create And Condition"))
	static FStrixCondition CreateStrixAndCondition(TArray<FStrixCondition> conditions);

	/** Creates a StrixCondition structure that contains other conditions joined by "Or".
	 *  Essentially groups the conditions together.
	 *  @param	conditions	Array of conditions used to create the grouping condition
	 *  @returns	The StrixCondition structure containing a "condition1-or-condition2-or..." condition
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Create Or Condition"))
	static FStrixCondition CreateStrixOrCondition(TArray<FStrixCondition> conditions);

	/** Creates a StrixOrder structure that represents an ascending order of the search results.
	 *  @param	fieldName	Field name used for the order
	 *  @returns	The StrixOrder structure containing a "order by field name ascending" order
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Create Ascending Order"))
	static FStrixOrder CreateStrixAscendingOrder(FString fieldName);

	/** Creates a StrixOrder structure that represents an descending order of the search results.
	 *  @param	fieldName	Field name used for the order
	 *  @returns	The StrixOrder structure containing a "order by field name descending" order
	 */
	UFUNCTION(BlueprintPure, Category = "StrixBPLibrary|Adapter", meta = (DisplayName = "Create Descending Order"))
	static FStrixOrder CreateStrixDescendingOrder(FString fieldName);

	/** Converts an uint8(byte) to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (byte)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_ByteToStrixRelayArg(uint8 val);

	/** Converts a bool to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (bool)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_BoolToStrixRelayArg(bool val);

	/** Converts a int to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (integer)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntToStrixRelayArg(int32 val);

	/** Converts a float to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (float)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_FloatToStrixRelayArg(float val);

	/** Converts a vector to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (vector)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_VectorToStrixRelayArg(FVector val);

	/** Converts a rotator to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (rotator)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_RotatorToStrixRelayArg(FRotator val);

	/** Converts a transform to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (transform)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_TransformToStrixRelayArg(FTransform val);

	/** Converts a quat to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (quat)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_QuatToStrixRelayArg(FQuat val);

	/** Converts a string to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (string)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringToStrixRelayArg(FString val);

	/** Converts a text to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (text)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_TextToStrixRelayArg(FText val);

	/** Converts an array of uint8(byte) values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<byte>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_ByteArrayToStrixRelayArg(TArray<uint8> val);

	/** Converts an array of int values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<int>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntArrayToStrixRelayArg(TArray<int32> val);

	/** Converts an array of float values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<float>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_FloatArrayToStrixRelayArg(TArray<float> val);

	/** Converts an array of vectors to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<vector>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_VectorArrayToStrixRelayArg(TArray<FVector> val);

	/** Converts an array of quats to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<quat>)", CompactNodeTitle = "->", Keywords = "cast convert", BlueprintAutocast), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_QuatArrayToStrixRelayArg(TArray<FQuat> val);

	/** Converts an array of rotators to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<rotator>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_RotatorArrayToStrixRelayArg(TArray<FRotator> val);

	/** Converts an array of transforms to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<transform>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_TransformArrayToStrixRelayArg(TArray<FTransform> val);

	/** Converts an array of string values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<string>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringArrayToStrixRelayArg(TArray<FString> val);

	/** Converts an array of text values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<text>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_TextArrayToStrixRelayArg(TArray<FText> val);

	/** Converts an array of boolean values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (array<bool>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_BoolArrayToStrixRelayArg(TArray<bool> val);

	/** Converts a set of uint8(byte) values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (set<byte>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_ByteSetToStrixRelayArg(TSet<uint8> val);

	/** Converts a set of int values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (set<int>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntSetToStrixRelayArg(TSet<int32> val);

	/** Converts a set of float values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (set<float>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_FloatSetToStrixRelayArg(TSet<float> val);

	/** Converts a set of vectors to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (set<vector>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_VectorSetToStrixRelayArg(TSet<FVector> val);

	/** Converts a set of string values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (set<string>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringSetToStrixRelayArg(TSet<FString> val);

	/** Converts a map of int-uint8(byte) key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<int, byte>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntKeyByteMapToStrixRelayArg(TMap<int32, uint8> val);

	/** Converts a map of int-int key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<int, int>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntKeyIntMapToStrixRelayArg(TMap<int32, int32> val);

	/** Converts a map of int-float key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<int, float>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntKeyFloatMapToStrixRelayArg(TMap<int32, float> val);

	/** Converts a map of int-vector key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<int, vector>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntKeyVectorMapToStrixRelayArg(TMap<int32, FVector> val);

	/** Converts a map of int-rotator key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<int, rotator>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntKeyRotatorMapToStrixRelayArg(TMap<int32, FRotator> val);

	/** Converts a map of int-string key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<int, string>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_IntKeyStringMapToStrixRelayArg(TMap<int32, FString> val);

	/** Converts a map of string-uint8(byte) key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<string, byte>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringKeyByteMapToStrixRelayArg(TMap<FString, uint8> val);

	/** Converts a map of string-int key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<string, int>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringKeyIntMapToStrixRelayArg(TMap<FString, int32> val);

	/** Converts a map of string-float key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<string, float>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringKeyFloatMapToStrixRelayArg(TMap<FString, float> val);

	/** Converts a map of string-vector key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<string, vector>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringKeyVectorMapToStrixRelayArg(TMap<FString, FVector> val);

	/** Converts a map of string-rotator key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<string, rotator>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringKeyRotatorMapToStrixRelayArg(TMap<FString, FRotator> val);

	/** Converts a map of string-string key-values to StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (map<string, string>)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StringKeyStringMapToStrixRelayArg(TMap<FString, FString> val);

	/** Converts an FStrixNetworkId to a StrixRelayArg structure (used for RPC)
	 *  @param	val	The value to convert
	 *  @returns	The StrixRelayArg wrapping the provided value
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToStrixRelayArg (FStrixNetworkId)", CompactNodeTitle = "->", Keywords = "cast convert"), Category = "StrixBPLibrary|Conversions")
	static FStrixRelayArg Conv_StrixNetworkIdToStrixRelayArg(FStrixNetworkId val);

private:
	/** Checks whether the specified actor is remote or local
	 *  @param	WorldContextObject	The actor to check
	 *  @returns	Whether the specified actor was created on the remote client or not
	 */
	static bool IsRemoteActor(const UObject* WorldContextObject);

	/** Gets the StrixReplicator component from the specified actor
	 *  @param	target	The actor to get the replicator component from
	 *  @returns	The StrixReplicator component associated with this actor or nullptr if there is none
	 */
	static UStrixReplicatorComponent* GetStrixReplicatorComponent(const AActor* target);

	/** Generates hash for the specified function name
	 *  @param	functionName	The function name to generate the hash for
	 *  @returns	Hash value generates using the specified functionName
	 */
	static int GetRpcProcedureHash(const FString& functionName);
};
