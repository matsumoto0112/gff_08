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
	* �}�X�^�[�T�[�o�[�Ȃǂɐڑ�����Ă���̂��ǂ���
	* @return true: �ڑ����Ă��Ȃ� false: �ڑ��ς�
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	bool IsConnectToRoom();

	/**
	* MemberProperty�̏���������
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void InitializeMemberProperty(const FString name);

	/**
	* RoomProperty�̏���������
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void InitializeRoomProperty(const int32 capacity, const FString roomName);

	/**
	* �V�[���ύX�O��MemberProperty�̍X�V
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void UpdateMemberProperty(const int32 channelID);

	/**
	* �v���C���[�ԍ��̃Z�b�g
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkConnect")
	void SetPlayerIndex(const int32 memberCount, const int32 channelID);
};
