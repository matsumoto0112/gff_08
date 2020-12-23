// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "gff_08/field/CheckPoint.h"

#include "LapCounter.generated.h"

class ARaceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapIncrementDispatcher, int32, NextLapCount);

/**
 * ����v���@�\
 * ����v���ƌ����A���ʂ̔���Ɏg���ϐ����������Ă��邽�ߖ������s���ĂɂȂ��Ă���
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GFF_08_API ULapCounter : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULapCounter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * �`�F�b�N�|�C���g��ʉ߂���
	 * @param PassedCheckPoint �ʉ߂����`�F�b�N�|�C���g
	 */
	UFUNCTION(BlueprintCallable, Category = "LapCounter")
	void PassCheckPoint(ACheckPoint* PassedCheckPoint);

	/**
	 * ���񐔂��擾����
	 */
	int32 GetLapCount() const {
		return CurrentLapCount;
	}

	/**
	 * ���݂̃`�F�b�N�|�C���g�C���f�b�N�X���擾����
	 */
	int32 GetCurrentCheckPointIndex() const {
		return CurrentIndex;
	}

	UFUNCTION(BlueprintGetter, Category = "LapCounter")
	int32 GetMostAdvancedLapCount() const {
		return MostAdvancedLapCount;
	}

	UFUNCTION(BlueprintGetter, Category = "LapCounter")
	int32 GetRanking() const {
		return Ranking;
	}
	/**
	 * �����L���O���Z�b�g����
	 */
	UFUNCTION(BlueprintSetter, Category = "LapCounter")
	void SetRanking(int32 Rank) {
		Ranking = Rank;
	}

	/**
	 * �S�̂̃��b�v�^�C�����擾����
	 */
	UFUNCTION(BlueprintCallable, Category = "LapCounter")
	TArray<float> GetLapTimes() const;

	/**
	* ���m�ȃ����L���O���ɍX�V����
	*/
	UFUNCTION()
	void UpdateAccurateRanking();

protected:
	//! �ł��i�񂾎��̃`�F�b�N�|�C���g�̃C���f�b�N�X
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MostAdvancedIndex;

	//! ���݂̃��b�v���i���񐔁j
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetMostAdvancedLapCount, Category = "LapCounter")
	int32 MostAdvancedLapCount;

	//! ���݂̃`�F�b�N�|�C���g�̃C���f�b�N�X
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 CurrentIndex;

	//! ���݂̃��b�v��
	//! �t���ȂǂŖ߂邱�Ƃ����邽��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 CurrentLapCount;
	//�ő�Ői�񂾃`�F�b�N�|�C���g�ԍ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MaxCheckPointIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LapCounter")
	ARaceManager* RaceManager;
	//���݂̃����L���O
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRanking, BlueprintSetter = SetRanking, Category = "LapCounter")
	int32 Ranking;

	//! ���̃Q�[���ɂ�����e�T�̃��b�v�^�C��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	TArray<float> LapTimes;

	//! ���񎞂̃f���Q�[�g
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LapCounter")
	FLapIncrementDispatcher LapIncrementDispatcher;
};
