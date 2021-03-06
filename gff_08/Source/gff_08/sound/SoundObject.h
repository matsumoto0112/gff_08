// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Components/AudioComponent.h>
#include <Sound/SoundBase.h>

#include "SoundObject.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API ASoundObject : public AActor {
	GENERATED_BODY()
public:
	ASoundObject();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Init(USoundBase* Sound, bool bAutoDelete = true);
	virtual void Init(USoundBase* Sound, USoundAttenuation* SoundAttenuation, AActor* OwnerActor, bool bAutoDelete = true);
	virtual void Init(USoundBase* Sound, USoundAttenuation* SoundAttenuation, const FVector& Location, bool bAutoDelete = true);
	UFUNCTION(BlueprintCallable, Category = "SoundObject")
	virtual void Stop();
	UFUNCTION(Category = "SoundObject")
	void AudioPlayFinished();
	UFUNCTION(BlueprintCallable, Category = "SoundObject")
	virtual bool IsFinished() const;
	UAudioComponent* GetAudioComponent() const {
		return AudioComponent;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* AudioComponent;
	UPROPERTY()
	bool bAutoDelete;
	UPROPERTY()
	bool bAudioPlayFinished;
};
