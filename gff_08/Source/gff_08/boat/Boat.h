// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "gff_08/boat/BoatDataAsset.h"
#include "gff_08/boat/BoatMover.h"
#include "gff_08/boat/Driver.h"
#include "gff_08/boat/LapCounter.h"
#include "gff_08/field/CheckPoint.h"
#include "gff_08/sound/SoundObject.h"
#include "gff_08/utils/GamePlayData.h"

#include "Boat.generated.h"

/**
 * ボートの移動可能状態
 */
UENUM(BlueprintType)
enum class EBoatMovableType : uint8 {
	Default,
	NoMove,
	StraightOnly,
};

USTRUCT(BlueprintType)
struct FSynchroParameters {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SynchroParameters")
	int32 PlayerIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SynchroParameters")
	int32 LapCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SynchroParameters")
	int32 CurrentCheckPointIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SynchroParameters")
	int32 Ranking;
};

/**
 * ボートクラス
 */
UCLASS()
class GFF_08_API ABoat : public APawn {
	GENERATED_BODY()

public:
	/**
	 * デフォルトコンストラクタ
	 */
	ABoat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * 移動量を計算する
	 * @param[out] 移動量
	 * @param[out] 左回転量
	 * @param[out] 右回転量
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual void CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * 逆走運転しているか
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual bool IsReverseDriving() const;

	/**
	 * 次に向かうべきチェックポイントを取得する
	 */
	ACheckPoint* GetNextCheckPoint() const {
		return NextCheckPoint;
	}

	/**
	 * 機体を変更する
	 * @param BoatID ボートのID
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	void ChangeBoat(int32 BoatID, int32 PlayerIndex);
	/**
	 * レース準備
	 * @param StartCheckPoint スタート時のチェックポイント
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	void RaceReady(ACheckPoint* StartCheckPoint);
	/**
	 * レース開始
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	void RaceStart();

	/**
	 * プレイヤーのスピード
	 */
	UFUNCTION(BlueprintCallable, Category = "Boat")
	virtual float GetPlayerSpeed() const;
	/**
	 * 周回計測機能の取得
	 */
	UFUNCTION(BlueprintGetter, Category = "Boat")
	ULapCounter* GetLapCounter() const {
		return LapCounter;
	}

	UFUNCTION(BlueprintSetter, Category = "Boat")
	void SetRacerName(const FName& Name) {
		RacerName = Name;
	}
	UFUNCTION(BlueprintGetter, Category = "Boat")
	FName GetRacerName() const {
		return RacerName;
	}
	int32 GetPlayerIndex_() const {
		return PlayerIndex_;
	}
	UFUNCTION(BlueprintCallable, Category = "Boat")
	void ReturnPrevCheckPoint();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Boat")
	FSynchroParameters GetSynchroParameters() const;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Boat")
	void SetSynchroParameters(const FSynchroParameters& Parameters);

private:
	UFUNCTION()
	void PushMovementValue();

protected:
	//! ボートメッシュ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	//! ボート移動処理
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoatMover* BoatMover;
	//! 周回計測
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetLapCounter, BlueprintReadOnly, Category = "Components")
	ULapCounter* LapCounter;
	//! 回転の力を加える地点
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SteerForceLocation;
	//! 波の生成地点
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UArrowComponent* GenerateWaveLocation;

	//! ボートのデータアセット
	UPROPERTY(EditDefaultsOnly, Category = "Boat")
	UBoatDataAsset* BoatDataAsset;

	//! ボートの現在の移動可能状態
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	EBoatMovableType MoveType;
	//! 移動音
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
	ASoundObject* MoveSound;
	//! スクリュー音
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boat")
	ASoundObject* ScrewSound;
	//! 次に向かうべきチェックポイント
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	ACheckPoint* NextCheckPoint;
	//! 運転手
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat")
	TScriptInterface<IDriver> Driver;
	//! レーサーの名前
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRacerName, BlueprintSetter = SetRacerName, Category = "Boat")
	FName RacerName;
	//! プレイヤー番号
	int32 PlayerIndex_;

	//! モーターの回転量を保存するタイマーのハンドル
	FTimerHandle PrevMotorValueStockHandle;
	//!モーターの回転量を保存するタイマーの間隔
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat")
	float PrevMotorValueStockInterval = 0.1f;
	//! 姿勢を維持しているときに最高速に達するまでにかかる時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat")
	float MaxInfluencePostureMaintainingTime = 1.0f;
	//! 以前のモーターの回転量の値
	TArray<TPair<float, float>> PrevMotorValues;
	//! 姿勢維持時間
	float PostureMaintainingTime;
	//! X軸回転量の履歴
	TArray<float> RotationXHistory;
};
