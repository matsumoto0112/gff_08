// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CheckPoint.generated.h"

class ACheckPointManager;

/**
 * コースにおける通過点を示す
 * 主にAI、周回、逆走判定に使用する
 */
UCLASS()
class GFF_08_API ACheckPoint : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * 何番目のチェックポイントか取得する
	 */
	int32 GetIndex() const {
		return Index;
	}

	/**
	 * 次のチェックポイントを返す
	 */
	UFUNCTION(BlueprintCallable, Category = "CheckPoint")
	ACheckPoint* GetNextPoint() const;
	/**
	 * 前のチェックポイントを返す
	 */
	UFUNCTION(BlueprintCallable, Category = "CheckPoint")
	ACheckPoint* GetPrevPoint() const;

	/**
	 * チェックポイントの得点が高い地点の座標を返す
	 */
	UFUNCTION(BlueprintCallable, Category = "CheckPoint")
	FVector GetPointLocation() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckPoint")
	int32 Index;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CheckPoint")
	ACheckPointManager* Manager;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CheckPoint",
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MostHeightPoint = 0.5f;
};
