// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gff_08/field/CheckPointManager.h"
#include "gff_08/field/RankingCalculator.h"
#include "gff_08/network/NetworkSynchroParameters.h"
#include "gff_08/stage/SetupRacers.h"
#include "gff_08/ui/CountDownTimer.h"
#include "gff_08/ui/MyHUD.h"

#include "RaceManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRaceEndEvent);

/**
 * レース管理
 */
UCLASS()
class GFF_08_API ARaceManager : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARaceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * ボートのセットアップ
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void RaceSetup(const FAllRacerInfo& RacersInfo);

	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	ABoat* SpawnBoat(const FNetworkUserData& UserData);

	/**
	 * マルチプレイ時のボートのセットアップ
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void MultiRaceSetup(const FRacerInfo& Info);

	/**
	 * レプリケートされたボートのセットアップ処理
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void ReplicateRaceSetup(ABoat* Boat, const int32 BoatIndex, const int32 PlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	bool IsStart();

	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void StartRaceSetUp();
	/**
	 * レース開始処理
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void RaceStart();

	/**
	 * レースのセットアップ処理が完了したか
	 */
	UFUNCTION(BlueprintGetter, Category = "RaceManager")
	bool GetRaceAlreadySetup() const {
		return bRaceAlreadySetup;
	}
	/**
	 * レースの時間管理機能の取得
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	URaceTimer* GetRaceTimer() const;

private:
	/**
	 * カウントダウンの更新処理
	 */
	void CountdownUpdate();
	/**
	 * いずれかのボートがゴールしたかどうか
	 */
	bool IsAnyBoatGoaled() const;

	FAllRacersGamePlayData CalculateResult();

protected:
	static const FName NEXT_LEVEL_NAME;

protected:
	//! レースのセットアップ処理担当
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USetupRacers* Setup;
	//! 順位計測
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URankingCalculator* RankingCalculator;

	//! チェックポイント管理者
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RaceManager")
	ACheckPointManager* CheckPointManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RaceManager")
	UCountDownTimer* CountDownUI;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RaceManager")
	float CountDownTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceManager")
	TArray<ABoat*> Boats;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaceManager")
	TSubclassOf<UMyHUD> HUDClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceManager")
	UMyHUD* MainUI;

	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRaceAlreadySetup, Category = "RaceManager")
	bool bRaceAlreadySetup;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceManager")
	bool bRaceStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatManager")
	float RaceEndRemainTime = 10.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BoatManager")
	bool bRaceEnded;

	//! レース終了時のイベント関数
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LapCounter")
	FRaceEndEvent RaceEndEvent;
};
