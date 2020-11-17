// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBrain.h"

#include "Engine/Engine.h"
#include "kismet/GamePlayStatics.h"

namespace {
float GetVectorAngle2D(const FVector& A, const FVector& B) {
	float Angle = FVector2D::CrossProduct(FVector2D(A.GetSafeNormal2D()), FVector2D(B.GetSafeNormal2D()));
	Angle = FMath::RadiansToDegrees(Angle);
	return Angle;
}
}	 // namespace

UAIBrain::UAIBrain() {
}

void UAIBrain::Init(ABoat* Boat) {
	Parent = Boat;
	CurrentTargetCheckPointIndex = -1;
}

FInputInfo UAIBrain::Next() {
	FInputInfo Res{0.1f, 0.1f, false};

	ACheckPoint* NextCheckPoint = Parent->GetNextCheckPoint();
	if (NextCheckPoint == nullptr) {
		return Res;
	}
	if (NextCheckPoint->GetIndex() != CurrentTargetCheckPointIndex) {
		UpdateTargetPoint();
	}
	const FVector ForwardVector = Parent->GetActorForwardVector().GetSafeNormal2D();
	const FVector Dir = (CurrentTargetPoint - Parent->GetActorLocation()).GetSafeNormal2D();
	// UKismetSystemLibrary::DrawDebugLine(
	//	GetWorld(), Parent->GetActorLocation(), Parent->GetActorLocation() + ForwardVector * 10000.0f, FColor::Green, 0.0f, 2.0f);
	// UKismetSystemLibrary::DrawDebugLine(
	//	GetWorld(), Parent->GetActorLocation(), Parent->GetActorLocation() + Dir * 10000.0f, FColor::Blue, 0.0f, 2.0f);
	const float Angle = GetVectorAngle2D(ForwardVector, Dir);

	//曲がりたい方向に全力で傾ける
	//曲がりたくない方向の回転量を調整することで曲がりやすさを考える
	if (Angle < -5.0f) {
		Res.LeftMotorValue = 1.0f;
		Res.RightMotorValue = FMath::Lerp(0.6f, 0.0f, (Angle * -1.0f) / 45.0f);
	} else if (Angle > 5.0f) {
		Res.LeftMotorValue = FMath::Lerp(0.6f, 0.0f, (Angle * 1.0f) / 45.0f);
		Res.RightMotorValue = 1.0f;
	} else {
		Res.LeftMotorValue = 1.0f;
		Res.RightMotorValue = 1.0f;
	}

	return Res;
}

FInputInfo UAIBrain::CurrentInputInfo_Implementation() const {
	return InputInfo;
}

void UAIBrain::UpdateInputInfo_Implementation() {
	InputInfo = Next();
}

void UAIBrain::UpdateTargetPoint() {
	const ACheckPoint* NextCheckPoint = Parent->GetNextCheckPoint();
	const ACheckPoint* NextNextCheckPoint = NextCheckPoint->GetNextPoint();
	CurrentTargetPoint = NextNextCheckPoint->GetActorLocation();
	CurrentTargetCheckPointIndex = NextCheckPoint->GetIndex();
}
