// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DirectoryInfo.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UDirectoryInfo : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "MyBPLibrary")
	static FString HelloWorld();

	UFUNCTION(BlueprintCallable, Category = "FragCounter")
	static bool WriteFragCount(FString fileName, TArray<int> counter);
};
