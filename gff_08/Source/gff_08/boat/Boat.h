// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "gff_08/boat/BoatMover.h"
#include "gff_08/boat/Driver.h"
#include "gff_08/boat/LapCounter.h"
#include "gff_08/field/CheckPoint.h"
#include "gff_08/sound/SoundObject.h"

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

UCLASS()
class GFF_08_API ABoat : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
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

protected:
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
};
