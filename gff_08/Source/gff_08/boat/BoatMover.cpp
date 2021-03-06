// Fill out your copyright notice in the Description page of Project Settings.

#include "BoatMover.h"

#include "gff_08/boat/Boat.h"
#include "gff_08/utils/MyLogCategory.h"
#include "gff_08/utils/SpeedConverter.h"
#include "kismet/GamePlayStatics.h"

//順位:回復時間(s)
const TMap<int32, float> UBoatMover::kWaveAccelerationRecoverIntervalTimes = {{1, 1.0f}, {2, 0.75f}, {3, 0.5f}, {4, 0.0f}};
//順位:有効時間(s)
const TMap<int32, float> UBoatMover::kWaveAccelerationActiveTimes = {{1, 2.0f}, {2, 4.0f}, {3, 6.0f}, {4, 10.0f}};
//順位:加速力
// NOTE:最大速度は変わらないため、最高速度に達しやすくなるかのみを変えられる
const TMap<int32, float> UBoatMover::kBoatAccerationCoefs = {{1, 1.0f}, {2, 1.3f}, {3, 1.4f}, {4, 1.5f}};
//順位:最高速度
const TMap<int32, float> UBoatMover::kBoatMaxSpeedCoefs = {{1, 1.0f}, {2, 1.0f}, {3, 1.0f}, {4, 1.0f}};

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
	VerticalCount = 0.0f;
	WaveAccelerationManageTime = 0.0f;
	WaveAccelerationType = EWaveAccelerationType::Active;
}

void UBoatMover::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (CurrentWaveTimerHandle.IsValid()) {
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(CurrentWaveTimerHandle);
		CurrentWaveTimerHandle.Invalidate();
	}
}

//初期化
void UBoatMover::Init(const FBoatMoverInitStructure& InitStructure) {
	ParentPawn = InitStructure.ParentPawn;
	BoatMesh = InitStructure.BoatMesh;
	SteerForceLocation = InitStructure.SteerForceLocation;
	GenerateWaveLocation = InitStructure.GenerateWaveLocation;
	VisualBoatMesh = InitStructure.VisualBoatMesh;
}

// Called every frame
void UBoatMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//パラメータ設定
void UBoatMover::SetParameter(float MaxMoveSpeed, float Accel, float Control) {
	this->MoveMaxSpeed = MaxMoveSpeed;
	this->Acceleration = Accel;
	this->AngularAcceleration = Control;
}

//移動処理
void UBoatMover::Move(float MoveValue, float LeftMotorValue, float RightMotorValue) {
	//最高速度を超えていない限り前方に対する移動を追加する
	if (!IsOverBoatMaxSpeed()) {
		AddForwardForce(MoveValue);
	}

	//回転処理
	AddRightForce(LeftMotorValue, RightMotorValue);

	AddMeshRotate(LeftMotorValue, RightMotorValue);

	AddMeshVerticalTilt(LeftMotorValue, RightMotorValue);

	//波の生成タイマー処理
	SettingWaveGenerateTimer();

	//波による加速処理
	const FVector WaveAccelVelocity = GetWaveAccelVelocity();

	const float Coef = [&]() {
		if (WaveAccelerationType == EWaveAccelerationType::Deactive)
			return 0.0f;
		const int32 Ranking = GetRanking();
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Format(TEXT("{0}"), {Ranking}));
		//０位（エラー対策）,１位、２位、３位、４位
		return TArray<float>{1.0f, 1.0f, 1.1f, 1.2f, 1.25f}[Ranking];
	}();

	BoatMesh->AddForce(WaveAccelVelocity * WaveInfluence * Coef);

	const float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	if (WaveAccelerationType == EWaveAccelerationType::Active) {
		//波に乗っている間、時間を計算する
		if (WaveAccelVelocity.Size() > 0.0f) {
			WaveAccelerationManageTime += DeltaSeconds;
			//一定時間を超過したら無効にする
			if (WaveAccelerationManageTime >= kWaveAccelerationActiveTimes[GetRanking()]) {
				WaveAccelerationType = EWaveAccelerationType::Deactive;
				WaveAccelerationManageTime = 0.0f;
			}
		} else {
			//波に乗っていない間はカウンターをもとに戻す
			WaveAccelerationManageTime -= DeltaSeconds;
			WaveAccelerationManageTime = FMath::Max(0.0f, WaveAccelerationManageTime);
		}
	} else {
		WaveAccelerationManageTime += GetWorld()->GetDeltaSeconds();
		//各順位ごとに決められた時間を超過していたら波による加速を有効化する
		if (WaveAccelerationManageTime >= kWaveAccelerationRecoverIntervalTimes[GetRanking()]) {
			WaveAccelerationType = EWaveAccelerationType::Active;
			WaveAccelerationManageTime = 0.0f;
		}
	}
}

//最高速度を超えているか
bool UBoatMover::IsOverBoatMaxSpeed() const {
	const FVector Velocity = ParentPawn->GetVelocity();
	const float Length = Velocity.Size();
	const float Speed_km_h = USpeedConverter::ToSpeedKilometerPerHour(Length);

	return Speed_km_h >= MoveMaxSpeed * kBoatMaxSpeedCoefs[GetRanking()];
}

//前方に対する力を加算する
//前方向に対する移動処理に使用
void UBoatMover::AddForwardForce(float MoveValue) {
	//現在速度(cm/s)を取得する
	const FVector Velocity = ParentPawn->GetVelocity();
	const float VelocityLength = Velocity.Size();

	// 現在速度/最大速度を割り出すためにMaxSpeedをcm/sに変換する
	const float MaxSpeed_cm_s = USpeedConverter::ToSpeedCentimeterPerSecond(MoveMaxSpeed * kBoatMaxSpeedCoefs[GetRanking()]);

	//加速する割合を0.0~1.0倍するための係数を計算する
	//最大速度に対して現在速度が小さいほど1.0に近くなる
	const float Coef = FMath::Lerp(1.0f, 0.0f, VelocityLength / MaxSpeed_cm_s) * kBoatAccerationCoefs[GetRanking()];

	const float Mass = BoatMesh->GetMass();
	const float ForcePower = MoveValue * Mass * Acceleration * Coef;

	const FVector ForwardVector = BoatMesh->GetForwardVector();
	BoatMesh->AddForce(FVector(ForwardVector.X, ForwardVector.Y, 0.0f) * ForcePower);
}

//右方向に力を加える
//回転に使用
void UBoatMover::AddRightForce(float LeftMotorValue, float RightMotorValue) {
	const float RotateValue = LeftMotorValue - RightMotorValue;
	const float Mass = BoatMesh->GetMass();
	//入力反転指令があるなら反転させるために-1を掛けるか決定する
	const float Coef = bFlipInput ? -1.0 : 1.0;
	const float ForcePower = RotateValue * Mass * AngularAcceleration * Coef;

	// Y方向の単一ベクトルを取得する(機体の正面)
	const FVector RightVector = SteerForceLocation->GetRightVector();
	//親オブジェクトの位置を取得
	const FVector SteerLocation = SteerForceLocation->GetComponentLocation();
	const FVector V = FVector(RightVector.X, RightVector.Y, 0.0f) * ForcePower;
	BoatMesh->AddForceAtLocation(V, SteerLocation);
}

void UBoatMover::AddMeshRotate(float LeftMotorValue, float RightMotorValue) {
	const float RotateValue = LeftMotorValue - RightMotorValue;
	const FRotator nowVisualMeshRotate = VisualBoatMesh->GetRelativeRotation();
	//使用範囲を0〜360のを-180〜180に変換
	float Z = (nowVisualMeshRotate.Yaw > 180.0f) ? nowVisualMeshRotate.Yaw - 360.0f : nowVisualMeshRotate.Yaw;
	float X = (nowVisualMeshRotate.Roll > 180.0f) ? nowVisualMeshRotate.Roll - 360.0f : nowVisualMeshRotate.Roll;
	//両方の押し込みの絶対値がs指定した値以下なら
	if (FMath::Abs(RotateValue) <= 0.2f) {
		//徐々にまっすぐにする
		Z = FMath::Lerp(Z, 0.0f, 0.1f);
		X = FMath::Lerp(X, 0.0f, 0.1f);
	} else {
		//押し込んでいる方向へ回転させる(回転制限)
		Z = FMath::Clamp(Z - RotateValue * 1.25f, -MaxHorizontalRotate, MaxHorizontalRotate);
		X = FMath::Clamp(X - RotateValue, -MaxDiagonalRotate, MaxDiagonalRotate);
	}
	//範囲を元に戻す
	Z = (Z < 0) ? Z + 360.0f : Z;
	X = (X < 0) ? X + 360.0f : X;
	VisualBoatMesh->SetRelativeRotation(FRotator(nowVisualMeshRotate.Pitch, Z, X));
}

void UBoatMover::AddMeshVerticalTilt(float LeftMotorValue, float RightMotorValue) {
	//現在速度(cm/s)を取得する
	const FVector Velocity = ParentPawn->GetVelocity();
	const float VelocityLength = Velocity.Size();

	// 現在速度/最大速度を割り出すためにMaxSpeedをcm/sに変換する
	const float MaxSpeed_cm_s = USpeedConverter::ToSpeedCentimeterPerSecond(MoveMaxSpeed);
	const float Coef = FMath::Lerp(0.0f, 1.0f, VelocityLength / MaxSpeed_cm_s);

	const FRotator nowRotator = VisualBoatMesh->GetRelativeRotation();
	float Y = (nowRotator.Pitch > 180.0f) ? nowRotator.Pitch - 360.0f : nowRotator.Pitch;
	if (Coef <= 0.5f) {
		Y = FMath::Lerp(Y, 0.0f, 0.1f);
		VerticalCount = 0.0f;
	} else {
		VerticalCount += GetWorld()->DeltaTimeSeconds;
		Y = FMath::Abs(FMath::Sin(VerticalCount * 2.0f) * MaxVerticalRotate);
		Y = FMath::Clamp(Y, 0.0f, MaxVerticalRotate);
	}
	Y = (Y < 0) ? Y + 360.0f : Y;
	VisualBoatMesh->SetRelativeRotation(FRotator(Y, nowRotator.Yaw, nowRotator.Roll));
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

int32 UBoatMover::GetRanking() const {
	ABoat* Parent = Cast<ABoat>(ParentPawn);
	if (!Parent) {
		return 4;
	}
	ULapCounter* LapCounter = Parent->GetLapCounter();
	if (!LapCounter) {
		return 4;
	}
	const int32 Ranking = LapCounter->GetRanking();
	return FMath::Clamp(Ranking, 1, 4);
}

//波の生成処理
void UBoatMover::GenerateWave() const {
	const FVector Location = GenerateWaveLocation->GetComponentLocation();
	const FRotator Rotation = GenerateWaveLocation->GetComponentRotation();
	Field->GenerateAccelWave(Location, Rotation);
}

//波の加速度を取得する
FVector UBoatMover::GetWaveAccelVelocity() const {
	return Field->GetAccelVelocity(BoatMesh->GetComponentLocation());
}

void UBoatMover::GenerateSynchroWave(const FVector& direction, const FRotator& rotate) {
}