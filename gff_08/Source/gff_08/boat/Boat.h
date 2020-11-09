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

UCLASS()
class GFF_08_API ABoat : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
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

	UFUNCTION(BlueprintCallable, Category = "Boat")
	void ChangeBoat(int32 BoatID);
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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoatMover* BoatMover;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	ULapCounter* LapCounter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SteerForceLocation;
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
};
