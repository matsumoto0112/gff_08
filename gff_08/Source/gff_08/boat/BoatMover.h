// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "gff_08/field/WaterField.h"

#include "BoatMover.generated.h"

/**
 * BoatMover�̏������\����
 */
USTRUCT(BlueprintType)
struct FBoatMoverInitStructure {
	GENERATED_USTRUCT_BODY()

public:
	/**
	 * �f�t�H���g�R���X�g���N�^
	 */
	FBoatMoverInitStructure() : ParentPawn(nullptr), SteerForceLocation(nullptr), GenerateWaveLocation(nullptr) {
	}

	/**
	 * �R���X�g���N�^
	 */
	FBoatMoverInitStructure(
		class APawn* ParentPawn, class UArrowComponent* SteerForceLocation, class UArrowComponent* GenerateWaveLocation)
		: ParentPawn(ParentPawn), SteerForceLocation(SteerForceLocation), GenerateWaveLocation(GenerateWaveLocation) {
	}

public:
	//! �e�̃|�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	APawn* ParentPawn;
	//! �{�[�g�̃��b�V��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UStaticMeshComponent* BoatMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UStaticMeshComponent* VisualBoatMesh;
	//! ��]��������ꏊ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UArrowComponent* SteerForceLocation;
	//! �g�̐����n�_
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UArrowComponent* GenerateWaveLocation;
};

/**
 * �{�[�g�̈ړ��@�\�Ǘ�
 */
UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class GFF_08_API UBoatMover : public UActorComponent {
	GENERATED_BODY()

public:
	/**
	 * �R���X�g���N�^
	 */
	UBoatMover(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/**
	 * ����������
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	void Init(const FBoatMoverInitStructure& InitStructure);

	/**
	 * �{�[�g�̃p�����[�^�ݒ�
	 * @param MaxMoveSpeed �ō����x
	 * @param Accel �����x
	 * @param Control ��]��
	 */
	void SetParameter(float MaxMoveSpeed, float Accel, float Control);
	/**
	 * �ړ�����
	 * @param MoveValue �ړ���
	 * @param LeftMotorValue �����[�^�[�̉�]��
	 * @param RightMotorValue �E���[�^�[�̉�]��
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	virtual void Move(float MoveValue, float LeftMotorValue, float RightMotorValue);

private:
	/**
	 * �ō��ړ����x�𒴉߂��Ă��邩���肷��
	 */
	UFUNCTION()
	bool IsOverBoatMaxSpeed() const;
	/**
	 * ���ʕ����Ɉړ�����͂�ǉ�����
	 */
	UFUNCTION()
	void AddForwardForce(float MoveValue);
	/**
	 * �E�����Ɉړ�����͂�ǉ�����
	 */
	UFUNCTION()
	void AddRightForce(float LeftMotorValue, float RightMotorValue);

	/**
	 * ���͎��̃{�[�g�̍��E�ւ̌X���𒲐�����
	 */
	UFUNCTION()
	void AddMeshRotate(float LeftMotorValue, float RightMotorValue);

	UFUNCTION()
	void AddMeshVerticalTilt(float LeftMotorValue, float RightMotorValue);

	/**
	 * �g�����^�C�}�[�̃Z�b�e�B���O
	 */
	UFUNCTION()
	void SettingWaveGenerateTimer();

	UFUNCTION()
	int32 GetRanking() const;

protected:
	/**
	 * �g�̐�������
	 * @note �g�̐���������BP��ł����s���Ȃ����߁ABP�ɏ������ڏ�����
	 * ��XCpp��ŌĂׂ�悤�ɂȂ������ɂ�cpp��ŏ�������
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	void GenerateWave() const;

	/**
	 * �g�̉����x�̎擾
	 * @note �g�̉����x�擾������BP��ł����s���Ȃ����߁ABP�ɏ������ڏ�����
	 * ��XCpp��ŌĂׂ�悤�ɂȂ������ɂ�cpp��ŏ�������
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	FVector GetWaveAccelVelocity() const;

	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	void GenerateSynchroWave(const FVector& direction, const FRotator& rotate);

protected:
	//! �e�̃|�[��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	APawn* ParentPawn;
	//! �{�[�g�̃��b�V��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BoatMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* VisualBoatMesh;
	//! ��]��������ꏊ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SteerForceLocation;
	//! �g�̐����n�_
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* GenerateWaveLocation;

protected:
	//! �t�B�[���h
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Field")
	AWaterField* Field;

	//! �ő�ړ����x
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move")
	float MoveMaxSpeed = 150.0f;
	//! ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move")
	float Acceleration = 6000.0f;

	//! ��]������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float AngularAcceleration = 500.0f;
	//���[�^�[�̍��E�l�ɑ΂��ď�Z����W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float RotatePowerCoef = 1.0f;
	//���̌X���̍ő�(Z��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float MaxHorizontalRotate = 30.0f;
	//�΂߂̌X���̍ő�(X��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float MaxDiagonalRotate = 5.0f;
	//�c�̌X���̍ő�(Y��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float MaxVerticalRotate = 5.0f;
	//! ���͂𔽓]���邩�ǂ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	bool bFlipInput = true;

	//! �g�̐����Ԋu(�b)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveSpawnSeconds = 0.1f;
	//! �g�̐����\�Œᑬ�x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveSpawnableSpeed = 30.0f;
	//! �g�̉����x���󂯂ĉ����͂̉e���x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveInfluence = 150000.0f;

	//! �g�̐����^�C�}�[
	FTimerHandle CurrentWaveTimerHandle;
	float VerticalCount = 0.0f;

	//! �g�̉����Ԋu�����ʂ��ƂɈ��Ԋu�ŗL��������@�\�p�ϐ�
	float WaveAccelerationManageTime;
	enum class EWaveAccelerationType {
		Active,
		Deactive,
	} WaveAccelerationType;

	static const TMap<int32, float> kWaveAccelerationRecoverIntervalTimes;
	static const TMap<int32, float> kWaveAccelerationActiveTimes;
	static const TMap<int32, float> kBoatAccerationCoefs;
};
