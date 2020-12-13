// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WaterField.generated.h"

USTRUCT(BlueprintType)
struct GFF_08_API Fr8g8b8a8 {
	GENERATED_USTRUCT_BODY()

	Fr8g8b8a8() : R(0), G(0), B(0), A(0) {
	}
	Fr8g8b8a8(uint8 col) : R(col), G(col), B(col), A(col) {
	}
	Fr8g8b8a8(uint8 r,uint8 g,uint8 b,uint8 a) : R(r), G(g), B(b), A(a) {
	}
	uint8 R = 255, G = 255, B = 255, A = 255;
};

USTRUCT(BlueprintType)
struct GFF_08_API FAccelWaveInfo {
	GENERATED_USTRUCT_BODY()

	FAccelWaveInfo() : Velocity(FVector::ZeroVector), Length(0.0f), StartTime(0.0f), IsValid(false) {
	}

	FAccelWaveInfo(const FVector& velocity, const float length, const float startTime, const bool isValid)
		: Velocity(velocity), Length(length), StartTime(startTime), IsValid(isValid) {
	}

	void Initialize(const FVector& velocity, const float length, const float startTime, const bool isValid) {
		Velocity = velocity;
		Length = length;
		StartTime = startTime;
		IsValid = isValid;
	}

	//波の向き
	FVector Velocity;
	//波の強さ
	float Length;
	//生成されてからの時間
	float StartTime;
	//存在するかどうか
	bool IsValid;
};

UCLASS()
class GFF_08_API AWaterField : public AActor {
	GENERATED_BODY()

public:
	// シーン上に出したときに呼ばれる
	AWaterField();

	// VisibleAnywhere -> エディタ上に表示するが、編集不可
	// EditAnywhere -> エディタ上に表示し、編集できる
	// BlueprintReadWrite -> Blueprint上で編集可能にする
	// BlueprintReadOnly -> Blueprint上で読み取り可能

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;	 //メッシュコンポーネント情報
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;

	UPROPERTY(BlueprintReadOnly)
	float Width;
	UPROPERTY(BlueprintReadOnly)
	float Height;
	UPROPERTY(BlueprintReadOnly)
	float EdgeW;
	UPROPERTY(BlueprintReadOnly)
	float EdgeH;

	UPROPERTY(BlueprintReadOnly)
	float EdgeTexW;
	UPROPERTY(BlueprintReadOnly)
	float EdgeTexH;

	//行
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 Row = 200;
	//列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 Column = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveLifespan = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterial* CopyWaterMaterial;
	UPROPERTY(EditAnywhere, Category = "Material")
	FColor LightColor = FColor::White;

protected:
	// スタート時
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// 更新
	virtual void Tick(float DeltaTime) override;

	/**
	 * 位置からグリッド座標を求め、その場所の加速波の情報を取得する
	 * @param [position] Actorのworld座標
	 * @return 加速度
	 */
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	FVector GetAccelVelocity(const FVector& position);

	/**
	 * 加速波の生成処理
	 * @param [position] Actorのworld座標
	 * @param [rotate]   Actorの回転
	 */
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	void GenerateAccelWave(const FVector& position, const FRotator& rotate);

private:
	/**
	 * 初期化処理
	 */
	void Initialize();

	/**
	 * マテリアルとflowMapの作成
	 */
	void CreateTextureAndMaterial();

	/**
	 * 波情報の更新
	 */
	void UpdateWaveInfo();

	/**
	 * テクスチャの更新を行う
	 */
	void UpdateTexture();

	/**
	 * flowMapの色情報の更新を行う
	 * @param [fieldGrid] ActorのGrid座標
	 */
	void UpdateFlowMap(const FVector& fieldGrid);

	/**
	 * 与えられたActorの位置をGrid座標に変換する
	 * @param [position] Actorのworld座標
	 * @return Grid座標
	 */
	FVector CulcFieldGrid(const FVector& position);

	/**
	 * Fieldの辺の長さ、Gridの数から
	 * Grid上の座標を求める
	 * @param [position] 座標
	 * @param [edge]     軸に対する辺の長さ
	 * @param [index]    軸に対する幅の数
	 * @return 軸に対するGrid座標
	 */
	int32 CulcGrid(float position, float edge, int32 index);

	/**
    * グリッド内に収まっているかどうか	
	* @return true:グリッド内 false:グリッド外
	*/
	bool IsGrid(const FVector& grid);

private:
	//画像サイズ
	static constexpr int32 TEXTURE_EDGE_W = 1024;
	static constexpr int32 TEXTURE_EDGE_H = 1024;

	static constexpr int32 LIMIT_TIME = 1;
	static constexpr uint8 NEUTRAL = 0300;

	TArray<Fr8g8b8a8> TextureColorData;
	TArray<TArray<FAccelWaveInfo>> WaveArray;
	UTexture2D* FlowMap;
	UMaterialInstanceDynamic* WaterMaterial;
	bool UpdateFlag;
	float Timer;
	int32 ColumnArrayIndex;
	FTimerHandle handle;
};
