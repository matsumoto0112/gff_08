// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct GFF_08_API FAccelWaveInfo {
	FAccelWaveInfo(FVector velocity, float length, AActor* waveObject)
		: velocity(velocity), length(length), waveObject(waveObject) {
	}

	FAccelWaveInfo() : FAccelWaveInfo(FVector(), 0.0f,nullptr) {
	}

	FVector velocity;
	float length;
	AActor* waveObject;
};
