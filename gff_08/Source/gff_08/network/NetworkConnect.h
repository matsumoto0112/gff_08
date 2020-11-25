// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NetworkConnect.generated.h"

UCLASS()
class GFF_08_API ANetworkConnect : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANetworkConnect();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NetworkConnect")
	bool IsPressConnectButton;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* マスターサーバーなどに接続されているのかどうか
	* @return true: 接続していない false: 接続済み
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	bool IsConnectToRoom();

	/**
	* MemberPropertyの初期化処理
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void InitializeMemberProperty(const FString name);

	/**
	* RoomPropertyの初期化処理
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void InitializeRoomProperty(const int32 capacity, const FString roomName);

	/**
	* シーン変更前のMemberPropertyの更新
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void UpdateMemberProperty(const int32 channelID);

	/**
	* プレイヤー番号のセット
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void SetPlayerIndex(const int32 memberCount, const int32 channelID);
};
