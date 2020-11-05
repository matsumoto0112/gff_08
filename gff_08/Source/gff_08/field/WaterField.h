// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AccelWaveInfo.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WaterField.generated.h"

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
	UStaticMeshComponent* visualMesh;	 //メッシュ情報
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Index")
	int row;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Index")
	int column;
	UPROPERTY(BlueprintReadWrite)
	float width;
	UPROPERTY(BlueprintReadWrite)
	float height;

protected:
	// スタート時
	virtual void BeginPlay() override;

public:
	// 更新
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "WaterField")
	void TestMethod();
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	int CulcGrid(const float gridPos, const float size, const int index);
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	FVector GetAccelVelocity(const FVector position);
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	void AddAccelWave(int r, int c, FVector velocity, float length, AActor* waveObject);
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	bool IsWaveValid(const int r, const int c);

private:
	std::vector<std::vector<FAccelWaveInfo>> waveList;
};
