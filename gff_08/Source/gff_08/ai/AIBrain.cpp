// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBrain.h"

#include "Engine/Engine.h"

UAIBrain::UAIBrain() {
}

void UAIBrain::Init(ABoat* Boat) {
	Parent = Boat;
}

FInputInfo UAIBrain::Next() {
	FInputInfo Res{1.0, 1.0};

	//‘O•û‚ÉƒŒƒC‚ð”ò‚Î‚µA•Ç‚©‚Ç‚¤‚©”»’è‚·‚é
	FHitResult HitResult;
	const FVector Start = Parent->GetActorLocation();
	const FVector End = Parent->GetActorLocation() + Parent->GetActorForwardVector() * 3000.0f;
	FCollisionQueryParams QueryParams;

	const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	QueryParams.TraceTag = TraceTag;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel2, QueryParams)) {
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, HitResult.Actor->GetName());
		Res.LeftMotorValue = 0.0f;
		Res.RightMotorValue = 1.0f;
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("NoHit"));
		Res.LeftMotorValue = 1.0f;
		Res.RightMotorValue = 1.0f;
	}
	return Res;
}
