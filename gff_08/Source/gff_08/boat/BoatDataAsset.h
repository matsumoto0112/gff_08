// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"

#include "BoatDataAsset.generated.h"

/**
 * ボートのパラメータ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FBoatParameter : public FTableRowBase {
	GENERATED_USTRUCT_BODY()

	/**
	 * デフォルトコンストラクタ
	 */
	FBoatParameter() : BoatMesh(nullptr), MaxSpeed(0.0f), Acceleration(0.0f), Control(0.0f), Mass(0.0f) {
	}

	/**
	 * コンストラクタ
	 */
	FBoatParameter(UStaticMesh* BoatMesh, float MaxSpeed, float Acceleration, float Control, float Mass)
		: BoatMesh(nullptr), MaxSpeed(MaxSpeed), Acceleration(Acceleration), Control(Control), Mass(Mass) {
	}

	//! ボートのメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	UStaticMesh* BoatMesh;
	//! 最高速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float MaxSpeed;
	//! 加速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float Acceleration;
	//! 回転力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float Control;
	//! 重さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float Mass;
};

/**
 * ボートの各行におけるデータ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FBoatParameterRecord {
	GENERATED_USTRUCT_BODY()

	//! アセット内のID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	int32 BoatID;
	//! ボートのメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	UStaticMesh* BoatMesh;
	//! 最高速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float MaxSpeed;
	//! 加速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float Acceleration;
	//! 回転力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float Control;
	//! 重さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoatParameter")
	float Mass;
};

/**
 * ボートのデータアセット
 */
UCLASS()
class GFF_08_API UBoatDataAsset : public UDataAsset {
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "DataTable")
	UDataTable* DataTable;
#endif

	/**
	 * データテーブルからインポートする
	 */
	UFUNCTION(meta = (CallInEditor = "true"))
	void Import();

	//! データ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BoatDataAsset")
	TArray<FBoatParameterRecord> Data;
};
