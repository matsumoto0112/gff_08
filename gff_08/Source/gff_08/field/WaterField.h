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
	UStaticMeshComponent* VisualMesh;	 //���b�V���R���|�[�l���g���
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

	//�s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Index")
	int Row;
	//��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Index")
	int Column;
	UPROPERTY(EditAnywhere, Category = "CopyMaterial")
	UMaterial* CopyWaterMaterial;

protected:
	// �X�^�[�g��
	virtual void BeginPlay() override;

public:
	// �X�V
	virtual void Tick(float DeltaTime) override;

	/**
	 * �ʒu����O���b�h���W�����߁A���̏ꏊ�̉����g�̏����擾����
	 * @param [position] Actor��world���W
	 * @return �����x
	 */
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	FVector GetAccelVelocity(const FVector& position);

	/**
	 * �����g�̐�������
	 * @param [position] Actor��world���W
	 * @param [rotate]   Actor�̉�]
	 */
	UFUNCTION(BlueprintCallable, Category = "WaterField")
	void GenerateAccelWave(const FVector& position, const FRotator& rotate);

private:
	/**
	 * ����������
	 */
	void Initialize();

	/**
	 * �}�e���A����flowMap�̍쐬
	 */
	void CreateTextureAndMaterial();

	/**
	 * �e�N�X�`���̍X�V���s��
	 */
	void UpdateTexture();

	/**
	 * flowMap�̐F���̍X�V���s��
	 * @param [fieldGrid] Actor��Grid���W
	 */
	void UpdateFlowMap(const FVector& fieldGrid);

	/**
	 * �^����ꂽActor�̈ʒu��Grid���W�ɕϊ�����
	 * @param [position] Actor��world���W
	 * @return Grid���W
	 */
	FVector CulcFieldGrid(const FVector& position);

	/**
	 * Field�̕ӂ̒����AGrid�̐�����
	 * Grid��̍��W�����߂�
	 * @param [position] ���W
	 * @param [edge]     ���ɑ΂���ӂ̒���
	 * @param [index]    ���ɑ΂��镝�̐�
	 * @return ���ɑ΂���Grid���W
	 */
	int32 CulcGrid(float position, float edge, int32 index);

private:
	//�摜�T�C�Y
	static constexpr int32 TEXTURE_EDGE_W = 1024;
	static constexpr int32 TEXTURE_EDGE_H = 1024;

	static constexpr uint8 NEUTRAL = 0300;

	TArray<Fr8g8b8a8> TextureColorData;
	TArray<TArray<FAccelWaveInfo>> WaveArray;
	UTexture2D* FlowMap;
	bool UpdateFlag;
};
