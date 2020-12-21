// Fill out your copyright notice in the Description page of Project Settings.

#include "BoatMover.h"

#include "gff_08/boat/Boat.h"
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

	//�t�B�[���h�����[���h����T��
	AActor* FieldActor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaterField::StaticClass());
	Field = Cast<AWaterField>(FieldActor);

	if (!Field) {
		UE_LOG(LogBoat, Error, TEXT("Can not find Field Actor!"));
	}
	VerticalCount = 0.0f;
}

void UBoatMover::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (CurrentWaveTimerHandle.IsValid()) {
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(CurrentWaveTimerHandle);
		CurrentWaveTimerHandle.Invalidate();
	}
}

//������
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

//�p�����[�^�ݒ�
void UBoatMover::SetParameter(float MaxMoveSpeed, float Accel, float Control) {
	this->MoveMaxSpeed = MaxMoveSpeed;
	this->Acceleration = Accel;
	this->AngularAcceleration = Control;
}

//�ړ�����
void UBoatMover::Move(float MoveValue, float LeftMotorValue, float RightMotorValue) {
	//�ō����x�𒴂��Ă��Ȃ�����O���ɑ΂���ړ���ǉ�����
	if (!IsOverBoatMaxSpeed()) {
		AddForwardForce(MoveValue);
	}

	//��]����
	AddRightForce(LeftMotorValue, RightMotorValue);

	AddMeshRotate(LeftMotorValue, RightMotorValue);

	AddMeshVerticalTilt(LeftMotorValue, RightMotorValue);

	//�g�̐����^�C�}�[����
	SettingWaveGenerateTimer();

	//�g�ɂ���������
	const FVector WaveAccelVelocity = GetWaveAccelVelocity();
	const FVector NormalizedWaveAccelVelocity = WaveAccelVelocity.GetSafeNormal();

	const float Coef = [&]() {
		ABoat* Parent = Cast<ABoat>(ParentPawn);
		if (!Parent) {
			return 1.0f;
		}
		ULapCounter* LapCounter = Parent->GetLapCounter();
		if (!LapCounter) {
			return 1.0f;
		}
		const int32 Ranking = LapCounter->GetRanking();
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Format(TEXT("{0}"), {Ranking}));
		//�O�ʁi�G���[�΍�j,�P�ʁA�Q�ʁA�R�ʁA�S��
		return TArray<float>{1.0f, 1.0f, 1.1f, 1.2f, 1.25f}[Ranking];
	}();
	BoatMesh->AddForce(NormalizedWaveAccelVelocity * WaveInfluence * Coef);
}

//�ō����x�𒴂��Ă��邩
bool UBoatMover::IsOverBoatMaxSpeed() const {
	const FVector Velocity = ParentPawn->GetVelocity();
	const float Length = Velocity.Size();
	const float Speed_km_h = USpeedConverter::ToSpeedKilometerPerHour(Length);

	return Speed_km_h >= MoveMaxSpeed;
}

//�O���ɑ΂���͂����Z����
//�O�����ɑ΂���ړ������Ɏg�p
void UBoatMover::AddForwardForce(float MoveValue) {
	//���ݑ��x(cm/s)���擾����
	const FVector Velocity = ParentPawn->GetVelocity();
	const float VelocityLength = Velocity.Size();

	// ���ݑ��x/�ő呬�x������o�����߂�MaxSpeed��cm/s�ɕϊ�����
	const float MaxSpeed_cm_s = USpeedConverter::ToSpeedCentimeterPerSecond(MoveMaxSpeed);

	//�������銄����0.0~1.0�{���邽�߂̌W�����v�Z����
	//�ő呬�x�ɑ΂��Č��ݑ��x���������ق�1.0�ɋ߂��Ȃ�
	const float Coef = FMath::Lerp(1.0f, 0.0f, VelocityLength / MaxSpeed_cm_s);

	const float Mass = BoatMesh->GetMass();
	const float ForcePower = MoveValue * Mass * Acceleration * Coef;

	const FVector ForwardVector = BoatMesh->GetForwardVector();
	BoatMesh->AddForce(FVector(ForwardVector.X, ForwardVector.Y, 0.0f) * ForcePower);
}

//�E�����ɗ͂�������
//��]�Ɏg�p
void UBoatMover::AddRightForce(float LeftMotorValue, float RightMotorValue) {
	const float RotateValue = LeftMotorValue - RightMotorValue;
	const float Mass = BoatMesh->GetMass();
	//���͔��]�w�߂�����Ȃ甽�]�����邽�߂�-1���|���邩���肷��
	const float Coef = bFlipInput ? -1.0 : 1.0;
	const float ForcePower = RotateValue * Mass * AngularAcceleration * Coef;

	// Y�����̒P��x�N�g�����擾����(�@�̂̐���)
	const FVector RightVector = SteerForceLocation->GetRightVector();
	//�e�I�u�W�F�N�g�̈ʒu���擾
	const FVector SteerLocation = SteerForceLocation->GetComponentLocation();
	const FVector V = FVector(RightVector.X, RightVector.Y, 0.0f) * ForcePower;
	BoatMesh->AddForceAtLocation(V, SteerLocation);
}

void UBoatMover::AddMeshRotate(float LeftMotorValue, float RightMotorValue) {
	const float RotateValue = LeftMotorValue - RightMotorValue;
	const FRotator nowVisualMeshRotate = VisualBoatMesh->GetRelativeRotation();
	//�g�p�͈͂�0�`360�̂�-180�`180�ɕϊ�
	float Z = (nowVisualMeshRotate.Yaw > 180.0f) ? nowVisualMeshRotate.Yaw - 360.0f : nowVisualMeshRotate.Yaw;
	float X = (nowVisualMeshRotate.Roll > 180.0f) ? nowVisualMeshRotate.Roll - 360.0f : nowVisualMeshRotate.Roll;
	//�����̉������݂̐�Βl��s�w�肵���l�ȉ��Ȃ�
	if (FMath::Abs(RotateValue) <= 0.2f) {
		//���X�ɂ܂������ɂ���
		Z = FMath::Lerp(Z, 0.0f, 0.1f);
		X = FMath::Lerp(X, 0.0f, 0.1f);
	} else {
		//��������ł�������։�]������(��]����)
		Z = FMath::Clamp(Z - RotateValue * 1.25f, -MaxHorizontalRotate, MaxHorizontalRotate);
		X = FMath::Clamp(X - RotateValue, -MaxDiagonalRotate, MaxDiagonalRotate);
	}
	//�͈͂����ɖ߂�
	Z = (Z < 0) ? Z + 360.0f : Z;
	X = (X < 0) ? X + 360.0f : X;
	VisualBoatMesh->SetRelativeRotation(FRotator(nowVisualMeshRotate.Pitch, Z, X));
}

void UBoatMover::AddMeshVerticalTilt(float LeftMotorValue, float RightMotorValue) {
	//���ݑ��x(cm/s)���擾����
	const FVector Velocity = ParentPawn->GetVelocity();
	const float VelocityLength = Velocity.Size();

	// ���ݑ��x/�ő呬�x������o�����߂�MaxSpeed��cm/s�ɕϊ�����
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

//�g�̐����^�C�}�[����
void UBoatMover::SettingWaveGenerateTimer() {
	const FVector Velocity = ParentPawn->GetVelocity();
	const float VelocityLength = Velocity.Size();
	const float Speed_km_h = USpeedConverter::ToSpeedKilometerPerHour(VelocityLength);

	//���x�����l�ȏ�Ȃ�g�̐����^�C�}�[���Z�b�g����
	if (Speed_km_h >= WaveSpawnableSpeed) {
		//��x�Z�b�g�����烋�[�v�������邽�߁A�ēx�����ɂȂ����^�C�~���O�ŉ��߂ăZ�b�g����
		if (CurrentWaveTimerHandle.IsValid()) {
			return;
		}

		//�����_���̂ق����Ăяo�����ȒP�Ȃ̂ō̗p
		TFunction<void(void)> Func = [&]() { GenerateWave(); };
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(CurrentWaveTimerHandle, (TFunction<void(void)> &&) Func, WaveSpawnSeconds, true);

	} else {
		//���x�����l����������琶���^�C�}�[������
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(CurrentWaveTimerHandle);
		CurrentWaveTimerHandle.Invalidate();
	}
}

//�g�̐�������
void UBoatMover::GenerateWave() const {
	const FVector Location = GenerateWaveLocation->GetComponentLocation();
	const FRotator Rotation = GenerateWaveLocation->GetComponentRotation();
	Field->GenerateAccelWave(Location, Rotation);
}

//�g�̉����x���擾����
FVector UBoatMover::GetWaveAccelVelocity() const {
	return Field->GetAccelVelocity(BoatMesh->GetComponentLocation());
}

void UBoatMover::GenerateSynchroWave(const FVector& direction, const FRotator& rotate) {

}