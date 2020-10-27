// Fill out your copyright notice in the Description page of Project Settings.

#include "RankingCalculator.h"

#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
URankingCalculator::URankingCalculator() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URankingCalculator::BeginPlay() {
	Super::BeginPlay();

	// ...
	TArray<AActor*> Boats;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BoatClass, Boats);

	LapCounters.Reserve(Boats.Num());
	for (auto&& Boat : Boats) {
		LapCounters.Emplace(Cast<ULapCounter>(Boat->GetComponentByClass(ULapCounter::StaticClass())));
	}

	AActor* ManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACheckPointManager::StaticClass());
	CheckPointManager = Cast<ACheckPointManager>(ManagerActor);
}

// Called every frame
void URankingCalculator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//�{�[�g�����[���ɂ���ă\�[�g���A���ʂ�ݒ肷��
	LapCounters.Sort([&](const ULapCounter& A, const ULapCounter& B) {
		// ���b�v���ł̍~��
		if (A.GetLapCounter() != B.GetLapCounter()) {
			return A.GetLapCounter() > B.GetLapCounter();
		}
		// �`�F�b�N�|�C���g�C���f�b�N�X�ł̍~��
		if (A.GetCurrentCheckPointIndex() != B.GetCurrentCheckPointIndex()) {
			return A.GetCurrentCheckPointIndex() > B.GetCurrentCheckPointIndex();
		}

		//�`�F�b�N�|�C���g�܂ł̋������ōŏI����
		ACheckPoint* CheckPoint_A = CheckPointManager->GetNextPoint(A.GetCurrentCheckPointIndex());
		float Distance_A_NextCheckPoint = FVector::Distance(CheckPoint_A->GetActorLocation(), A.GetOwner()->GetActorLocation());

		ACheckPoint* CheckPoint_B = CheckPointManager->GetNextPoint(B.GetCurrentCheckPointIndex());
		float Distance_B_NextCheckPoint = FVector::Distance(CheckPoint_B->GetActorLocation(), B.GetOwner()->GetActorLocation());
		return Distance_A_NextCheckPoint < Distance_B_NextCheckPoint;
	});

	for (int32 i = 0; i < LapCounters.Num(); i++) {
		LapCounters[i]->SetRanking(i + 1);
	}
}
