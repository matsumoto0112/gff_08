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
	// �V�[����ɏo�����Ƃ��ɌĂ΂��
	AWaterField();

	// VisibleAnywhere -> �G�f�B�^��ɕ\�����邪�A�ҏW�s��
	// EditAnywhere -> �G�f�B�^��ɕ\�����A�ҏW�ł���
	// BlueprintReadWrite -> Blueprint��ŕҏW�\�ɂ���
	// BlueprintReadOnly -> Blueprint��œǂݎ��\

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* visualMesh;	 //���b�V�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Index")
	int row;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Index")
	int column;
	UPROPERTY(BlueprintReadWrite)
	float width;
	UPROPERTY(BlueprintReadWrite)
	float height;

protected:
	// �X�^�[�g��
	virtual void BeginPlay() override;

public:
	// �X�V
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
