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

	MostAdvancedIndex = 0;
	MostAdcancedLapCount = 1;
	CurrentIndex = 0;
	CurrentLapCount = 1;
}

// Called every frame
void ULapCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentLapTime += DeltaTime;
}

// �`�F�b�N�|�C���g��ʉ߂���
void ULapCounter::PassCheckPoint(ACheckPoint* PassedCheckPoint) {
	const int32 PassedCheckPointIndex = PassedCheckPoint->GetIndex();
	constexpr int32 START_CHECKPOINT_INDEX = 0;

	// �X�^�[�g�n�_�̃`�F�b�N�|�C���g
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// ���܂łɐi�񂾍ő�̃`�F�b�N�|�C���g���R�[�X�̍Ō�̃C���f�b�N�X�Ȃ�1�T���Ă����Ƃ�������
		if (MostAdvancedIndex == MaxCheckPointIndex) {
			MostAdcancedLapCount++;
			LapTimes.Add(CurrentLapTime);
			CurrentLapTime = 0.0f;
			MostAdvancedIndex = PassedCheckPointIndex;
		}

	} else {
		// ���̃`�F�b�N�|�C���g�ɐG�ꂽ�炻�̏��ōX�V
		if (MostAdvancedIndex + 1 == PassedCheckPointIndex) {
			MostAdvancedIndex = PassedCheckPointIndex;
		}
	}

	// ���ʌ���p�̃C���f�b�N�X�̍X�V����
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// ���񂵂��^�C�~���O�ŉ��Z
		if (CurrentIndex == MaxCheckPointIndex) {
			CurrentLapCount++;
		}
	} else if (PassedCheckPointIndex == MaxCheckPointIndex) {
		// �߂����^�C�~���O�Ō��Z
		if (CurrentIndex == START_CHECKPOINT_INDEX) {
			CurrentLapCount = FMath::Max(CurrentLapCount - 1, 1);
		}
	}
	CurrentIndex = PassedCheckPointIndex;
}

float ULapCounter::GetTotalLapTime() const {
	float TotalTime = 0.0f;
	for (auto&& Time : LapTimes) {
		TotalTime += Time;
	}
	return TotalTime;
}
