// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WaterField.generated.h"

USTRUCT(BlueprintType)
struct GFF_08_API Fr8g8b8a8 {
	GENERATED_USTRUCT_BODY()

	uint8 r = 255, g = 255, b = 255, a = 255;
};

USTRUCT(BlueprintType)
struct GFF_08_API FAccelWaveInfo {
	GENERATED_USTRUCT_BODY()

	FAccelWaveInfo() : velocity(FVector::ZeroVector), length(0.0f), startTime(), isValid(false) {
	}

	FAccelWaveInfo(FVector velocity, float length, FDateTime startTime, bool isValid)
		: velocity(velocity), length(length), startTime(startTime), isValid(isValid) {
	}

	//�g�̌���
	FVector velocity;
	//�g�̋���
	float length;
	//��������Ă���̎���
	FDateTime startTime;
	//���݂��邩�ǂ���
	bool isValid;
};

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

	UPROPERTY(BlueprintReadOnly)
	float width;
	UPROPERTY(BlueprintReadOnly)
	float height;
	UPROPERTY(BlueprintReadOnly)
	float edgeW;
	UPROPERTY(BlueprintReadOnly)
	float edgeH;

	UPROPERTY(BlueprintReadOnly)
	float edgeTexW;
	UPROPERTY(BlueprintReadOnly)
	float edgeTexH;

	//�s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Index")
	int row;
	//��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Index")
	int column;

protected:
	// �X�^�[�g��
	virtual void BeginPlay() override;

public:
	// �X�V
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "WaterField")
	FVector GetAccelVelocity(FVector position);
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	void GenerateAccelWave(FVector position, FRotator rotate);

private:
	UFUNCTION()
	void CreateTextureAndMaterial();
	FVector CulcFieldGrid(FVector position);
	int CulcGrid(float position, float edge, int index);
	void UpdateFlowMap(FVector fieldGrid);

private:
	static constexpr int32 TEXTURE_EDGE_W = 1024;
	static constexpr int32 TEXTURE_EDGE_H = 1024;

	TArray<Fr8g8b8a8> textureColorData;
	TArray<TArray<FAccelWaveInfo>> waveArray;
	UTexture2D* flowMap;
	bool updateFlag; 
};
