// Fill out your copyright notice in the Description page of Project Settings.

#include "SetupRacers.h"

#include "gff_08/utils/MyLogCategory.h"

// Sets default values for this component's properties
USetupRacers::USetupRacers() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void USetupRacers::BeginPlay() {
	Super::BeginPlay();

	// ...
}

// Called every frame
void USetupRacers::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<ABoat*> USetupRacers::Setup(const FAllRacerInfo& RacersInfo) {
	if (RacersInfo.Racers.Num() > StartPoints.Num()) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("���[�T�[�̐����X�^�[�g�n�_�̐���葽���ݒ肳��Ă��܂��B"));
		UE_LOG(LogRace, Error, TEXT("���[�T�[�̐����X�^�[�g�n�_�̐���葽���ݒ肳��Ă��܂��B"));
		return TArray<ABoat*>();
	}

	const int32 RacersNum = RacersInfo.Racers.Num();
	TArray<ABoat*> Res;
	for (int32 i = 0; i < RacersNum; i++) {
		const FRacerInfo& Racer = RacersInfo.Racers[i];
		const ATargetPoint* Point = StartPoints[i];
		const FVector Location = Point->GetActorLocation();
		const FRotator Rotation = Point->GetActorRotation();

		ABoat* Boat = GetWorld()->SpawnActor<ABoat>(BoatClasses[Racer.RacerType].Get(), Location, Rotation);

		//�v���C���[�Ȃ�v���C���[�R���g���[�����Z�b�g���Ă�����
		//�������Ȃ��Ɠ��͂��󂯎��Ȃ�����
		if (Racer.RacerType == ERacerType::Player) {
			GetWorld()->GetFirstPlayerController()->Possess(Boat);
		} else {
			Boat->SpawnDefaultController();
		}
		Res.Push(Boat);
	}

	return Res;
}
