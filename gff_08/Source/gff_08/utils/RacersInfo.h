// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RacersInfo.generated.h"

/**
 * ���[�T�[�̎��
 * Player��AI���AAI�̎�ނ��܂�
 */
UENUM(BlueprintType)
enum class ERacerType : uint8 {
	Player,	   //! �v���C���[����
	AI,		   //! AI����
};

/**
 * ���[�T�[�l�̏��
 */
USTRUCT(BlueprintType)
struct GFF_08_API FRacerInfo {
	GENERATED_USTRUCT_BODY()

	//! ���[�T�[��ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	int32 RacerID;
	//! ���[�T�[�̎��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	ERacerType RacerType;
};

/**
 * ���[�T�[�S�̂̌l���
 */
USTRUCT(BlueprintType)
struct GFF_08_API FAllRacerInfo {
	GENERATED_USTRUCT_BODY()

	//! ���[�T�[�����̏��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	TArray<FRacerInfo> Racers;
};
