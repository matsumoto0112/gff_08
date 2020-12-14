// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "gff_08/ui/UITime.h"

#include "RaceTimer.generated.h"

/**
 * ���[�X�̎��Ԍv���E�\���@�\
 */
UCLASS()
class GFF_08_API URaceTimer : public UUserWidget {
	GENERATED_BODY()
protected:
public:
	/**
	 * Tick����
	 */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	/**
	 * �v���J�n
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceTimer")
	void Start();
	/**
	 * �v���I��
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceTimer")
	void Stop();

	UFUNCTION(BlueprintCallable, Category = "RaceTimer")
	void StopUpdateImages();

	/**
	 * ���݂̎��Ԃ��擾����
	 */
	UFUNCTION(BlueprintGetter, Category = "RaceTimer")
	float GetCurrentTime() const {
		return CurrentTime;
	}

protected:
	//! ���݂̎���
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCurrentTime, Category = "RaceTimer")
	float CurrentTime;
	//! �v���J�n���Ă��邩
	UPROPERTY()
	bool bIsStarted = false;
	UPROPERTY()
	bool bUpdateImagesFlag = true;
};
