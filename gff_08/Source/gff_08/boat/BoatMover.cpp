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

	//�t�B�[���h�����[���h����T��
	AActor* FieldActor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaterField::StaticClass());
	Field = Cast<AWaterField>(FieldActor);

	if (!Field) {
		UE_LOG(LogBoat, Error, TEXT("Can not find Field Actor!"));
	}
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

	//�g�̐����^�C�}�[����
	SettingWaveGenerateTimer();

	//�g�ɂ���������
	const FVector WaveAccelVelocity = GetWaveAccelVelocity();
	const FVector NormalizedWaveAccelVelocity = WaveAccelVelocity.GetSafeNormal();
	BoatMesh->AddForce(NormalizedWaveAccelVelocity * WaveInfluence);
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
	float Yaw = VisualBoatMesh->GetRelativeRotation().Yaw;
	//�g�p�͈͂�0�`360�̂�-180�`180�ɕϊ�
	float Y = (Yaw > 180.0f) ? Yaw - 360.0f : Yaw;
	//�����̉������݂̐�Βl��s�w�肵���l�ȉ��Ȃ�
	if (FMath::Abs(RotateValue) <= 0.2f) {
		//���X�ɂ܂������ɂ���
		Y = FMath::Lerp(Y, 0.0f, 0.1f);
	} else {
		//��������ł�������։�]������(��]����)
		Y = FMath::Clamp(Y - RotateValue * 1.25f, -30.0f, 30.0f);
	}
	//�͈͂����ɖ߂�
	Y = (Y < 0) ? Y + 360.0f : Y;
	VisualBoatMesh->SetRelativeRotation(FRotator(0.0f, Y, 0.0f));
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
