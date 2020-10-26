// Fill out your copyright notice in the Description page of Project Settings.

#include "LapCounter.h"

// Sets default values for this component's properties
ULapCounter::ULapCounter() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULapCounter::BeginPlay() {
	Super::BeginPlay();

	LapCount = 1;
}

// Called every frame
void ULapCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULapCounter::PassCheckPoint(ACheckPoint* PassedCheckPoint) {
	const int32 PassedCheckPointIndex = PassedCheckPoint->GetIndex();

	// �X�^�[�g�n�_�̃`�F�b�N�|�C���g
	if (PassedCheckPointIndex == 0) {
		if (CurrentCheckPointIndex == MaxCheckPointIndex) {
			LapCount++;
			CurrentCheckPointIndex = PassedCheckPointIndex;
		}
	} else {
		if (CurrentCheckPointIndex + 1 == PassedCheckPointIndex) {
			CurrentCheckPointIndex = PassedCheckPointIndex;
		}
	}
}