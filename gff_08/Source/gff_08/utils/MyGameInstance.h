// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "gff_08/sound/SoundDataAsset.h"
#include "gff_08/sound/SoundSystem.h"

#include "MyGameInstance.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()

private:
	UMyGameInstance();

public:
	virtual void Init() override;

	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	static UMyGameInstance* GetInstance();

public:
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	USoundSystem* GetSoundSystem() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundDataAsset* SoundDataAsset;

	UPROPERTY()
	USoundSystem* SoundSystem;
};
