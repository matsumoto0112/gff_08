// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Adapter\StrixRoomMember.h>

#include "MultiWaitRoomManager.generated.h"

UCLASS()
class GFF_08_API AMultiWaitRoomManager : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMultiWaitRoomManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * 初期化処理
	 */
	UFUNCTION(BlueprintCallable, Category = "MultiWaitRoom")
	void Initialize();

	/**
	 * 現在のルームにいるメンバー情報をセットする
	 */
	UFUNCTION(BlueprintCallable, Category = "MultiWaitRoom")
	void SetCurrentRoomMembers();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MultiWaitRoom")
	TArray<FStrixRoomMember> RoomMemberProperties;

private:
	static constexpr float LIMIT_TIME = 0.5f;
	static constexpr int MAX_ROOM_MEMBER = 4;
	float Timer;
};
