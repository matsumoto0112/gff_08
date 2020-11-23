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
 * �l�b�g���[�N�ڑ����Ɉ�x�����X�V����郆�[�U�[�f�[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkUserData {
	GENERATED_USTRUCT_BODY()

	//! �v���C���[�ԍ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 PlayerIndex = -1;
	//! �v���C���[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FName PlayerName;
	//! �I�������{�[�g�ԍ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 BoatIndex = -1;
};

/**
 * ���t���[���X�V�������͏��
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkInputData {
	GENERATED_USTRUCT_BODY()
	// ���͏��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float LeftMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float RightMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	bool bBack;
};

/**
 * ���܂ɍX�V�����C�x���g���s���̃f�[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkEventData {
	GENERATED_USTRUCT_BODY()
	//! ����̃^�C�~���O�œ������邽�߂̍��W�i60�t���[�����Ɉ��X�V����j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FVector FixLocation;

	//! �Ō�ɔ��������C�x���g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	EGameEvent CurrentEvent;
};

/**
 * ���U���g���ɕK�v�ȃf�[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkResultData {
	GENERATED_USTRUCT_BODY()

	//! �S�[�����ɕK�v�ȏ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_3;
};
