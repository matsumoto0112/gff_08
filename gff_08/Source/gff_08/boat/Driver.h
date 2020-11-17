// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Driver.generated.h"

/**
 * �{�[�g�ɑ΂�����͏��
 * ���̒l�����ƂɃ{�[�g�𐧌䂷��
 */
USTRUCT(BlueprintType)
struct FInputInfo {
	GENERATED_USTRUCT_BODY()

public:
	FInputInfo() : LeftMotorValue(0.0f), RightMotorValue(0.0f), bBack(false) {
	}
	FInputInfo(float LeftMotorValue, float RightMotorValue, bool bBack)
		: LeftMotorValue(LeftMotorValue), RightMotorValue(RightMotorValue), bBack(bBack) {
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	float LeftMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	float RightMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	bool bBack;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UDriver : public UInterface {
	GENERATED_BODY()
};

/**
 *
 */
class GFF_08_API IDriver {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * ���݂̈ړ����͂��擾����
	 * �����񓯈�t���[���ŌĂ΂�邱�Ƃ��l�����A�擾�ƍX�V�����𕪊�
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Driver")
	FInputInfo CurrentInputInfo() const;

	/**
	 * ���͏�Ԃ��X�V����
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Driver")
	void UpdateInputInfo();
};
