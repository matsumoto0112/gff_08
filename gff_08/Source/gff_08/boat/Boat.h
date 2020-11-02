// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "gff_08/boat/BoatMover.h"
#include "gff_08/boat/LapCounter.h"
#include "gff_08/field/CheckPoint.h"
#include "gff_08/sound/SoundObject.h"

#include "Boat.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = "Boat")
	void RaceReady(ACheckPoint* StartCheckPoint, const FVector& StartLocation);

	/**
	 * �v���C���[�̃X�s�[�h
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual float GetPlayerSpeed() const;
	/**
	 * �ړ��ʂ��v�Z����
	 * @param[out] �ړ���
	 * @param[out] ����]��
	 * @param[out] �E��]��
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual void CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const;
	/**
	 * �t���^�]���Ă��邩
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual bool IsReverseDriving() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//! �ړ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
	ASoundObject* MoveSound;
	//! �X�N�����[��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
	ASoundObject* ScrewSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	ACheckPoint* NextCheckPoint;

	//! �����[�^�[�̒l
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	float LeftMotorValue;
	//! �E���[�^�[�̒l
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	float RightMotorValue;
};
