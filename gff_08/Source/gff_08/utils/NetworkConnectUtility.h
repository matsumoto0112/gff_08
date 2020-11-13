// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrixBlueprintFunctionLibrary.h"

#include "NetworkConnectUtility.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UNetworkConnectUtility : public UStrixBlueprintFunctionLibrary {
	GENERATED_BODY()

	/**
	* �v���C���[���I�[�i�[(���삵�Ă������)���ǂ���
	* @param [target] ���ׂ�A�N�^
	* @return �I�[�i�[���ǂ���
	*/
	UFUNCTION(BlueprintCallable, Category = "StrixSDKUtility")
	static bool IsOwner(const AActor* target);

	/**
	* �V���O���v���C���ǂ���
	* @param [worldContextObject]
	* @return true:�}���`�v���C false:�V���O���v���C
	*/
	UFUNCTION(BlueprintCallable, Category = "StrixSDKUtility")
	static bool IsMultiGame(const UObject* worldContextObject);
};
