// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "gff_08/field/CheckPoint.h"

#include "LapCounter.generated.h"

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

	void SetRanking(int32 Rank) {
		Ranking = Rank;
	}

	UFUNCTION(BlueprintCallable, Category = "LapCounter")
	float GetTotalLapTime() const;

protected:
	//! 最も進んだ時のチェックポイントのインデックス
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MostAdvancedIndex;

	//! 現在のラップ数（周回数）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MostAdcancedLapCount;

	//! 現在のチェックポイントのインデックス
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 CurrentIndex;

	//! 現在のラップ数
	//! 逆走などで戻ることがあるため
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 CurrentLapCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MaxCheckPointIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 Ranking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	float CurrentLapTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	TArray<float> LapTimes;
};
