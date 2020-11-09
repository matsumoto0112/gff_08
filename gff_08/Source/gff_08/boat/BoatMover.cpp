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

	//フィールドをワールドから探す
	AActor* FieldActor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaterField::StaticClass());
	Field = Cast<AWaterField>(FieldActor);

	if (!Field) {
		UE_LOG(LogBoat, Error, TEXT("Can not find Field Actor!"));
	}
}

//初期化
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

//パラメータ設定
void UBoatMover::SetParameter(float MaxMoveSpeed, float Accel, float Control) {
}

//移動処理
void UBoatMover::Move(float MoveValue, float LeftMotorValue, float RightMotorValue) {
	//最高速度を超えていない限り前方に対する移動を追加する
	if (!IsOverBoatMaxSpeed()) {
		AddForwardForce(MoveValue);
	}

	//回転処理
	AddRightForce(LeftMotorValue, RightMotorValue);

	//波の生成タイマー処理
	SettingWaveGenerateTimer();

	//波による加速処理
	const FVector WaveAccelVelocity = GetWaveAccelVelocity();
	const FVector NormalizedWaveAccelVelocity = WaveAccelVelocity.GetSafeNormal();
	BoatMesh->AddForce(NormalizedWaveAccelVelocity * WaveInfluence);
}

//最高速度を超えているか
bool UBoatMover::IsOverBoatMaxSpeed() const {
	const FVector Velocity = ParentPawn->GetVelocity();
	const float Length = Velocity.Size();
	const float Speed_km_h = USpeedConverter::ToSpeedKilometerPerHour(Length);

	return Speed_km_h >= MoveMaxSpeed;
}

//前方に対する力を加算する
//前方向に対する移動処理に使用
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

//右方向に力を加える
//回転に使用
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

//波の生成タイマー処理
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

//波の生成処理
void UBoatMover::GenerateWave() const {
	const FVector Location = GenerateWaveLocation->GetComponentLocation();
	const FRotator Rotation = GenerateWaveLocation->GetRelativeRotation();
	Field->GenerateAccelWave(Location, Rotation);
}

//波の加速度を取得する
FVector UBoatMover::GetWaveAccelVelocity() const {
	return Field->GetAccelVelocity(BoatMesh->GetComponentLocation());
}
