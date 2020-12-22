// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "gff_08/field/WaterField.h"

#include "BoatMover.generated.h"

/**
 * BoatMoverの初期化構造体
 */
USTRUCT(BlueprintType)
struct FBoatMoverInitStructure {
	GENERATED_USTRUCT_BODY()

public:
	/**
	 * デフォルトコンストラクタ
	 */
	FBoatMoverInitStructure() : ParentPawn(nullptr), SteerForceLocation(nullptr), GenerateWaveLocation(nullptr) {
	}

	/**
	 * コンストラクタ
	 */
	FBoatMoverInitStructure(
		class APawn* ParentPawn, class UArrowComponent* SteerForceLocation, class UArrowComponent* GenerateWaveLocation)
		: ParentPawn(ParentPawn), SteerForceLocation(SteerForceLocation), GenerateWaveLocation(GenerateWaveLocation) {
	}

public:
	//! 親のポーン
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	APawn* ParentPawn;
	//! ボートのメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UStaticMeshComponent* BoatMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UStaticMeshComponent* VisualBoatMesh;
	//! 回転をかける場所
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UArrowComponent* SteerForceLocation;
	//! 波の生成地点
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatMoverInitStructure")
	UArrowComponent* GenerateWaveLocation;
};

/**
 * ボートの移動機能管理
 */
UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class GFF_08_API UBoatMover : public UActorComponent {
	GENERATED_BODY()

public:
	/**
	 * コンストラクタ
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
	 * 初期化処理
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	void Init(const FBoatMoverInitStructure& InitStructure);

	/**
	 * ボートのパラメータ設定
	 * @param MaxMoveSpeed 最高速度
	 * @param Accel 加速度
	 * @param Control 回転力
	 */
	void SetParameter(float MaxMoveSpeed, float Accel, float Control);
	/**
	 * 移動処理
	 * @param MoveValue 移動量
	 * @param LeftMotorValue 左モーターの回転量
	 * @param RightMotorValue 右モーターの回転量
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	virtual void Move(float MoveValue, float LeftMotorValue, float RightMotorValue);

private:
	/**
	 * 最高移動速度を超過しているか判定する
	 */
	UFUNCTION()
	bool IsOverBoatMaxSpeed() const;
	/**
	 * 正面方向に移動する力を追加する
	 */
	UFUNCTION()
	void AddForwardForce(float MoveValue);
	/**
	 * 右方向に移動する力を追加する
	 */
	UFUNCTION()
	void AddRightForce(float LeftMotorValue, float RightMotorValue);

	/**
	 * 入力時のボートの左右への傾きを調整する
	 */
	UFUNCTION()
	void AddMeshRotate(float LeftMotorValue, float RightMotorValue);

	UFUNCTION()
	void AddMeshVerticalTilt(float LeftMotorValue, float RightMotorValue);

	/**
	 * 波生成タイマーのセッティング
	 */
	UFUNCTION()
	void SettingWaveGenerateTimer();

	UFUNCTION()
	int32 GetRanking() const;

protected:
	/**
	 * 波の生成処理
	 * @note 波の生成処理はBP上でしか行えないため、BPに処理を移譲する
	 * 後々Cpp上で呼べるようになった時にはcpp上で処理する
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	void GenerateWave() const;

	/**
	 * 波の加速度の取得
	 * @note 波の加速度取得処理はBP上でしか行えないため、BPに処理を移譲する
	 * 後々Cpp上で呼べるようになった時にはcpp上で処理する
	 */
	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	FVector GetWaveAccelVelocity() const;

	UFUNCTION(BlueprintCallable, Category = "BoatMover")
	void GenerateSynchroWave(const FVector& direction, const FRotator& rotate);

protected:
	//! 親のポーン
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	APawn* ParentPawn;
	//! ボートのメッシュ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BoatMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* VisualBoatMesh;
	//! 回転をかける場所
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SteerForceLocation;
	//! 波の生成地点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* GenerateWaveLocation;

protected:
	//! フィールド
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Field")
	AWaterField* Field;

	//! 最大移動速度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move")
	float MoveMaxSpeed = 150.0f;
	//! 加速力
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move")
	float Acceleration = 6000.0f;

	//! 回転加速力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float AngularAcceleration = 500.0f;
	//モーターの左右値に対して乗算する係数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float RotatePowerCoef = 1.0f;
	//横の傾きの最大(Z軸)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float MaxHorizontalRotate = 30.0f;
	//斜めの傾きの最大(X軸)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float MaxDiagonalRotate = 5.0f;
	//縦の傾きの最大(Y軸)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float MaxVerticalRotate = 5.0f;
	//! 入力を反転するかどうか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	bool bFlipInput = true;

	//! 波の生成間隔(秒)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveSpawnSeconds = 0.1f;
	//! 波の生成可能最低速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveSpawnableSpeed = 30.0f;
	//! 波の加速度を受けて加わる力の影響度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveInfluence = 150000.0f;

	//! 波の生成タイマー
	FTimerHandle CurrentWaveTimerHandle;
	float VerticalCount = 0.0f;

	//! 波の加速間隔を順位ごとに一定間隔で有効化する機能用変数
	float WaveAccelerationManageTime;
	enum class EWaveAccelerationType {
		Active,
		Deactive,
	} WaveAccelerationType;

	static const TMap<int32, float> kWaveAccelerationRecoverIntervalTimes;
	static const TMap<int32, float> kWaveAccelerationActiveTimes;
	static const TMap<int32, float> kBoatAccerationCoefs;
};
