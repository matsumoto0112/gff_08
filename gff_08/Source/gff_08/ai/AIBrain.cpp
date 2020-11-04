// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBrain.h"

#include "Engine/Engine.h"
#include "kismet/GamePlayStatics.h"

UAIBrain::UAIBrain() {
}

void UAIBrain::Init(ABoat* Boat) {
	Parent = Boat;
}

FInputInfo UAIBrain::Next() {
	FInputInfo Res{0.1f, 0.1f};

	ACheckPoint* NextCheckPoint = Parent->GetNextCheckPoint();
	ACheckPoint* NextNextCheckPoint = NextCheckPoint->GetNextPoint();
	UKismetSystemLibrary::DrawDebugLine(
		GetWorld(), Parent->GetActorLocation(), NextNextCheckPoint->GetActorLocation(), FColor::Red);

	const FVector ForwardVector = Parent->GetActorForwardVector().GetSafeNormal2D();
	UKismetSystemLibrary::DrawDebugLine(
		GetWorld(), Parent->GetActorLocation(), Parent->GetActorLocation() + ForwardVector * 10000.0f, FColor::Green, 0.0f, 2.0f);
	const FVector Dir = (NextNextCheckPoint->GetActorLocation() - Parent->GetActorLocation()).GetSafeNormal2D();
	UKismetSystemLibrary::DrawDebugLine(
		GetWorld(), Parent->GetActorLocation(), Parent->GetActorLocation() + Dir * 10000.0f, FColor::Blue, 0.0f, 2.0f);

	float Angle = FVector2D::CrossProduct(FVector2D(ForwardVector), FVector2D(Dir));
	Angle = FMath::RadiansToDegrees(Angle);

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
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Format(TEXT("{0}"), {Angle}));

	////前方にレイを飛ばし、壁かどうか判定する
	// FHitResult HitResult;
	// const FVector Start = Parent->GetActorLocation();
	// const FVector End = Parent->GetActorLocation() + Parent->GetActorForwardVector() * 3000.0f;
	// FCollisionQueryParams QueryParams;

	// if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel2)) {
	//	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, HitResult.Actor->GetName());
	//	Res.LeftMotorValue = 0.0f;
	//	Res.RightMotorValue = 1.0f;
	//} else {
	//	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("NoHit"));
	//	Res.LeftMotorValue = 1.0f;
	//	Res.RightMotorValue = 1.0f;
	//}

	return Res;
}
