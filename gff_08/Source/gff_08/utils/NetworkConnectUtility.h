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
	* プレイヤーがオーナー(操作しているもの)かどうか
	* @param [target] 調べるアクタ
	* @return オーナーかどうか
	*/
	UFUNCTION(BlueprintCallable, Category = "StrixSDKUtility")
	static bool IsOwner(const AActor* target);

	/**
	* シングルプレイかどうか
	* @param [worldContextObject]
	* @return true:マルチプレイ false:シングルプレイ
	*/
	UFUNCTION(BlueprintCallable, Category = "StrixSDKUtility")
	static bool IsMultiGame(const UObject* worldContextObject);
};
