// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetworkConnect.generated.h"

UCLASS()
class GFF_08_API ANetworkConnect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetworkConnect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	bool IsConnectToRoom();
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void InitializeMemberProperty(const FString name);
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void InitializeRoomProperty(const int32 capacity,const FString roomName);
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void UpdateMemberProperty(const int32 channelID);
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void SetPlayerIndex(const int32 channelID);

private:
	bool IsPressConnectButton;
};
