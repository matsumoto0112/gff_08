// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NetworkSynchroParameters.generated.h"

/**
 * �v���C���[�ɔ��������Q�[�����C�x���g
 */
UENUM(BlueprintType)
enum class EGameEvent : uint8 { START, LAP_1, LAP_2, GOAL, DISCONNECT, NONE };

/**
 * ��������p�����[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkSynchroParameters {
	GENERATED_USTRUCT_BODY()

	//! �v���C���[�ԍ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 PlayerIndex;
	//! �v���C���[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FName PlayerName;
	//! �I�������{�[�g�ԍ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 BoatIndex;

	//! ����̃^�C�~���O�œ������邽�߂̍��W�i60�t���[�����Ɉ��X�V����j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FVector FixLocation;

	// ���͏��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float LeftMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float RightMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	bool bBack;

	//! �Ō�ɔ��������C�x���g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	EGameEvent CurrentEvent;

	//! �S�[�����ɕK�v�ȏ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_3;
};
