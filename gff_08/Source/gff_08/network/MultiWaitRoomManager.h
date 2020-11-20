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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MultiWaitRoom")
	TArray<FStrixRoomMember> RoomMemberProperties;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MultiWaitRoom")
	int32 ChannelID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* ����������
	*/
	UFUNCTION(BlueprintCallable, Category = "MultiWaitRoom")
	void Initialize(int32 ID);
    
	/**
	* ���݂̃��[���ɂ��郁���o�[�����Z�b�g����
	*/
	UFUNCTION(BlueprintCallable, Category = "MultiWaitRoom")
	void SetCurrentRoomMembers();

private:
	static constexpr float LIMIT_TIME = 0.25f;
	static constexpr int MAX_ROOM_MEMBER = 4;
	float Timer;

};
