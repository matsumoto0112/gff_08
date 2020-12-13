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

	//�g�̌���
	FVector Velocity;
	//�g�̋���
	float Length;
	//��������Ă���̎���
	float StartTime;
	//���݂��邩�ǂ���
	bool IsValid;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 Row = 200;
	//��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 Column = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float WaveLifespan = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterial* CopyWaterMaterial;
	UPROPERTY(EditAnywhere, Category = "Material")
	FColor LightColor = FColor::White;

protected:
	// �X�^�[�g��
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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
	 * �g���̍X�V
	 */
	void UpdateWaveInfo();

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

	/**
    * �O���b�h���Ɏ��܂��Ă��邩�ǂ���	
	* @return true:�O���b�h�� false:�O���b�h�O
	*/
	bool IsGrid(const FVector& grid);

private:
	//�摜�T�C�Y
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
