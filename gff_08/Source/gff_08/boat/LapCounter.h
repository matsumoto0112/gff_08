// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "gff_08/field/CheckPoint.h"

#include "LapCounter.generated.h"

class ARaceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapIncrementDispatcher, int32, NextLapCount);

/**
 * 周回計測機能
 * 周回計測と言いつつ、順位の判定に使う変数も持たせているため役割が不明瞭になってきた
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GFF_08_API ULapCounter : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULapCounter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * チェックポイントを通過した
	 * @param PassedCheckPoint 通過したチェックポイント
	 */
	UFUNCTION(BlueprintCallable, Category = "LapCounter")
	void PassCheckPoint(ACheckPoint* PassedCheckPoint);

	/**
	 * 周回数を取得する
	 */
	int32 GetLapCount() const {
		return CurrentLapCount;
	}

	/**
	 * 現在のチェックポイントインデックスを取得する
	 */
	int32 GetCurrentCheckPointIndex() const {
		return CurrentIndex;
	}

	UFUNCTION(BlueprintGetter, Category = "LapCounter")
	int32 GetMostAdvancedLapCount() const {
		return MostAdvancedLapCount;
	}

	UFUNCTION(BlueprintGetter, Category = "LapCounter")
	int32 GetRanking() const {
		return Ranking;
	}
	/**
	 * ランキングをセットする
	 */
	UFUNCTION(BlueprintSetter, Category = "LapCounter")
	void SetRanking(int32 Rank) {
		Ranking = Rank;
	}

	/**
	 * 全体のラップタイムを取得する
	 */
	UFUNCTION(BlueprintCallable, Category = "LapCounter")
	TArray<float> GetLapTimes() const;

	/**
	* 正確なランキング情報に更新する
	*/
	UFUNCTION()
	void UpdateAccurateRanking();

protected:
	//! 最も進んだ時のチェックポイントのインデックス
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MostAdvancedIndex;

	//! 現在のラップ数（周回数）
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetMostAdvancedLapCount, Category = "LapCounter")
	int32 MostAdvancedLapCount;

	//! 現在のチェックポイントのインデックス
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 CurrentIndex;

	//! 現在のラップ数
	//! 逆走などで戻ることがあるため
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 CurrentLapCount;
	//最大で進んだチェックポイント番号
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MaxCheckPointIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LapCounter")
	ARaceManager* RaceManager;
	//現在のランキング
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRanking, BlueprintSetter = SetRanking, Category = "LapCounter")
	int32 Ranking;

	//! このゲームにおける各週のラップタイム
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	TArray<float> LapTimes;

	//! 周回時のデリゲート
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LapCounter")
	FLapIncrementDispatcher LapIncrementDispatcher;
};
