// Fill out your copyright notice in the Description page of Project Settings.

#include "BoatMover.h"

#include "gff_08/utils/MyLogCategory.h"
#include "gff_08/utils/SpeedConverter.h"
#include "kismet/GamePlayStatics.h"

// Sets default values for this component's properties
UBoatMover::UBoatMover(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBoatMover::BeginPlay() {
	Super::BeginPlay();

	AActor* FieldActor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaterField::StaticClass());
	Field = Cast<AWaterField>(FieldActor);

	if (!Field) {
		UE_LOG(LogBoat, Error, TEXT("Can not find Field Actor!"));
	}
}

void UBoatMover::Init(const FBoatMoverInitStructure& InitStructure) {
	ParentPawn = InitStructure.ParentPawn;
	BoatMesh = InitStructure.BoatMesh;
	SteerForceLocation = InitStructure.SteerForceLocation;
	GenerateWaveLocation = InitStructure.GenerateWaveLocation;
}

// Called every frame
void UBoatMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBoatMover::SetParameter(float MaxMoveSpeed, float Accel, float Control) {
}

void UBoatMover::Move(float MoveValue, float LeftMotorValue, float RightMotorValue) {
	if (!IsOverBoatMaxSpeed()) {
		AddForwardForce(MoveValue);
	}

	AddRightForce(LeftMotorValue, RightMotorValue);
	SettingWaveGenerateTimer();

	const FVector WaveAccelVelocity = GetWaveAccelVelocity();
	const FVector NormalizedWaveAccelVelocity = WaveAccelVelocity.GetSafeNormal();
	BoatMesh->AddForce(NormalizedWaveAccelVelocity * WaveInfluence);
}

bool UBoatMover::IsOverBoatMaxSpeed() const {
	const FVector Velocity = ParentPawn->GetVelocity();
	const float Length = Velocity.Size();
	const float Speed_km_h = USpeedConverter::ToSpeedKilometerPerHour(Length);

	return Speed_km_h >= MoveMaxSpeed;
}

void UBoatMover::AddForwardForce(float MoveValue) {
	//現在速度(cm/s)を取得する
	const FVector Velocity = ParentPawn->GetVelocity();
	const float VelocityLength = Velocity.Size();

	// 現在速度/最大速度を割り出すためにMaxSpeedをcm/sに変換する
	const float MaxSpeed_cm_s = USpeedConverter::ToSpeedCentimeterPerSecond(MoveMaxSpeed);

	//加速する割合を0.0~1.0倍するための係数を計算する
	//最大速度に対して現在速度が小さいほど1.0に近くなる
	const float Coef = FMath::Lerp(1.0f, 0.0f, VelocityLength / MaxSpeed_cm_s);

	const float Mass = BoatMesh->GetMass();
	const float ForcePower = MoveValue * Mass * Acceleration * Coef;

	const FVector ForwardVector = BoatMesh->GetForwardVector();
	BoatMesh->AddForce(ForwardVector * ForcePower);
}

void UBoatMover::AddRightForce(float LeftMotorValue, float RightMotorValue) {
	const float RotateValue = LeftMotorValue - RightMotorValue;
	const float Mass = BoatMesh->GetMass();
	//入力反転指令があるなら反転させるために-1を掛けるか決定する
	const float Coef = bFlipInput ? -1.0 : 1.0;
	const float ForcePower = RotateValue * Mass * AngularAcceleration * Coef;

	const FVector RightVector = SteerForceLocation->GetRightVector();
	const FVector SteerLocation = SteerForceLocation->GetComponentLocation();

	BoatMesh->AddForceAtLocation(RightVector * ForcePower, SteerLocation);
}

void UBoatMover::SettingWaveGenerateTimer() {
	const FVector Velocity = ParentPawn->GetVelocity();
	const float VelocityLength = Velocity.Size();
	const float Speed_km_h = USpeedConverter::ToSpeedKilometerPerHour(VelocityLength);

	//速度が一定値以上なら波の生成タイマーをセットする
	if (Speed_km_h >= WaveSpawnableSpeed) {
		//一度セットしたらループ処理するため、再度無効になったタイミングで改めてセットする
		if (CurrentWaveTimerHandle.IsValid()) {
			return;
		}

		//ラムダ式のほうが呼び出しが簡単なので採用
		TFunction<void(void)> Func = [&]() { GenerateWave(); };
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(CurrentWaveTimerHandle, (TFunction<void(void)> &&) Func, WaveSpawnSeconds, true);

	} else {
		//速度が一定値を下回ったら生成タイマーを消す
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(CurrentWaveTimerHandle);
		CurrentWaveTimerHandle.Invalidate();
	}
}

void UBoatMover::GenerateWave() const {
	const FVector Location = GenerateWaveLocation->GetComponentLocation();
	const FRotator Rotation = GenerateWaveLocation->GetRelativeRotation();
	Field->GenerateAccelWave(Location, Rotation);
}

FVector UBoatMover::GetWaveAccelVelocity() const {
	return Field->GetAccelVelocity(BoatMesh->GetComponentLocation());
}
