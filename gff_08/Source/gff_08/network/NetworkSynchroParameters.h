// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NetworkSynchroParameters.generated.h"

/**
 * �v���C���[�ɔ��������Q�[�����C�x���g
 */
UENUM(BlueprintType)
enum class EGameEvent : uint8 {
	SETUP,		   //! �Z�b�g�A�b�v������
	RACEREADY,	   //! ��������
	START,		   //! ��T��
	LAP_1,		   //! ��T��
	LAP_2,		   //! �O�T��
	GOAL,		   //! �S�[������
	DISCONNECT,	   //! �ؒf����
	NONE
};

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
	//�l�b�g���[�N���ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 PlayerNetworkID = -1;
};

/**
 * ���t���[���X�V�������͏��
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkInputData {
	GENERATED_USTRUCT_BODY()
	// ���͏��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	uint8 CompressionLeftMotorData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	uint8 CompressionRightMotorData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	uint8 CompressionbBackData;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	// float LeftMotorValue;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	// float RightMotorValue;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	// bool bBack;
};

/**
 * ���W�n�f�[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkTransformData {
	GENERATED_USTRUCT_BODY()
	//! ����̃^�C�~���O�œ������邽�߂̍��W�i60�t���[�����Ɉ��X�V����j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FVector FixLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FRotator FixRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FVector FixVelocity;

	//! ���݂̃`�F�b�N�|�C���g�̃C���f�b�N�X�i�����L���O�v�Z�p�j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 CheckPointIndex;
	//! ���݂̎��񐔁i�����L���O�v�Z�p�j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 LapCount;
};

/**
 * ���܂ɍX�V�����C�x���g���s���̃f�[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkEventData {
	GENERATED_USTRUCT_BODY()
	//! �Ō�ɔ��������C�x���g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	EGameEvent CurrentEvent;

	//! ���[�X���J�n���鎞��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FDateTime RaceStartTime;
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
