// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "gff_08/boat/BoatDataAsset.h"
#include "gff_08/boat/BoatMover.h"
#include "gff_08/boat/Driver.h"
#include "gff_08/boat/LapCounter.h"
#include "gff_08/field/CheckPoint.h"
#include "gff_08/sound/SoundObject.h"
#include "gff_08/utils/GamePlayData.h"
#include "gff_08/utils/RacersInfo.h"

#include "Boat.generated.h"

/**
 * �{�[�g�̈ړ��\���
 */
UENUM(BlueprintType)
enum class EBoatMovableType : uint8 {
	Default,
	NoMove,
	StraightOnly,
};

/**
 * �{�[�g�N���X
 */
UCLASS()
class GFF_08_API ABoat : public APawn {
	GENERATED_BODY()

public:
	/**
	 * �f�t�H���g�R���X�g���N�^
	 */
	ABoat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * �ړ��ʂ��v�Z����
	 * @param[out] �ړ���
	 * @param[out] ����]��
	 * @param[out] �E��]��
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual void CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * �t���^�]���Ă��邩
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual bool IsReverseDriving() const;

	/**
	 * ���Ɍ������ׂ��`�F�b�N�|�C���g���擾����
	 */
	ACheckPoint* GetNextCheckPoint() const {
		return NextCheckPoint;
	}

	/**
	 * ���[�X����
	 * @param StartCheckPoint �X�^�[�g���̃`�F�b�N�|�C���g
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	void RaceReady(ACheckPoint* StartCheckPoint);
	/**
	 * ���[�X�J�n
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	void RaceStart();

	/**
	 * �v���C���[�̃X�s�[�h
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual float GetPlayerSpeed() const;
	/**
	 * ����v���@�\�̎擾
	 */
	UFUNCTION(BlueprintGetter, Category = "Boat")
	ULapCounter* GetLapCounter() const {
		return LapCounter;
	}

	/**
	 * ���[�T�[�̎�ނ��擾����
	 */
	UFUNCTION(BlueprintGetter, Category = "Boat")
	FRacerInfo GetRacerInfo() const {
		return RacerInfo;
	}
	/**
	 * ���[�T�[�̎�ނ�ݒ肷��
	 */
	UFUNCTION(BlueprintSetter, Category = "Boat")
	void SetRacerInfo(const FRacerInfo& InRacerInfo);

	UFUNCTION(BlueprintCallable, Category = "Boat")
	void ReturnPrevCheckPoint();

private:
	UFUNCTION()
	void PushMovementValue();

protected:
	//! �{�[�g���b�V��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* VisualBoatMesh;
	//! �{�[�g�ړ�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoatMover* BoatMover;
	//! ����v��
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetLapCounter, BlueprintReadOnly, Category = "Components")
	ULapCounter* LapCounter;
	//! ��]�̗͂�������n�_
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SteerForceLocation;
	//! �g�̐����n�_
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UArrowComponent* GenerateWaveLocation;

	//! �{�[�g�̃f�[�^�A�Z�b�g
	UPROPERTY(EditDefaultsOnly, Category = "Boat")
	UBoatDataAsset* BoatDataAsset;

	//! �{�[�g�̌��݂̈ړ��\���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	EBoatMovableType MoveType;
	//! �ړ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
	ASoundObject* MoveSound;
	//! �X�N�����[��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
	ASoundObject* ScrewSound;
	//! ���Ɍ������ׂ��`�F�b�N�|�C���g
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	ACheckPoint* NextCheckPoint;
	//! �^�]��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	TScriptInterface<IDriver> Driver;
	//! ���]���͂��L����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	bool bFlipInput;

	//! ���[�^�[�̉�]�ʂ�ۑ�����^�C�}�[�̃n���h��
	FTimerHandle PrevMotorValueStockHandle;
	//!���[�^�[�̉�]�ʂ�ۑ�����^�C�}�[�̊Ԋu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat")
	float PrevMotorValueStockInterval = 0.1f;
	//! �p�����ێ����Ă���Ƃ��ɍō����ɒB����܂łɂ����鎞��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat")
	float MaxInfluencePostureMaintainingTime = 1.0f;
	//! �ȑO�̃��[�^�[�̉�]�ʂ̒l
	TArray<TPair<float, float>> PrevMotorValues;
	//! �p���ێ�����
	float PostureMaintainingTime;
	//! X����]�ʂ̗���
	TArray<float> RotationXHistory;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetRacerInfo, BlueprintSetter = SetRacerInfo, Category = "Boat")
	FRacerInfo RacerInfo;
};
