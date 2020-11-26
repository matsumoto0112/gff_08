// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CheckPoint.generated.h"

class ACheckPointManager;

/**
 * �R�[�X�ɂ�����ʉߓ_������
 * ���AI�A����A�t������Ɏg�p����
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
	 * ���Ԗڂ̃`�F�b�N�|�C���g���擾����
	 */
	int32 GetIndex() const {
		return Index;
	}

	/**
	 * ���̃`�F�b�N�|�C���g��Ԃ�
	 */
	UFUNCTION(BlueprintCallable, Category = "CheckPoint")
	ACheckPoint* GetNextPoint() const;
	/**
	 * �O�̃`�F�b�N�|�C���g��Ԃ�
	 */
	UFUNCTION(BlueprintCallable, Category = "CheckPoint")
	ACheckPoint* GetPrevPoint() const;

	/**
	 * �`�F�b�N�|�C���g�̓��_�������n�_�̍��W��Ԃ�
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
