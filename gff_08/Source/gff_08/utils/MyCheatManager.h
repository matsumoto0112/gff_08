// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"

#include "MyCheatManager.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UMyCheatManager : public UCheatManager {
	GENERATED_BODY()

public:
	UFUNCTION(exec)
	void MyCheatCommand();
};
