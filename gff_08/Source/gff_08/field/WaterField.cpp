// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterField.h"

// Sets default values
AWaterField::AWaterField() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���b�V���R���|�[�l���g��ǉ�
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// staticMesh���q�I�u�W�F�N�g�Ƃ��Ĕz�u����
	RootComponent = VisualMesh;

	VisualMesh->SetStaticMesh(StaticMesh);
	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AWaterField::BeginPlay() {
	Super::BeginPlay();

	Initialize();
}

// Called every frame
void AWaterField::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (UpdateFlag == false) {
		return;
	}

	UpdateTexture();

	UpdateFlag = false;
}

/**
 * �ʒu����O���b�h���W�����߁A���̏ꏊ�̉����g�̏����擾����
 * @param [position] Actor��world���W
 * @return �����x
 */
FVector AWaterField::GetAccelVelocity(const FVector& position) {
	FVector grid = CulcFieldGrid(position);
	if (WaveArray[grid.X][grid.Y].isValid == false) {
		return FVector::ZeroVector;
	}

	return WaveArray[grid.X][grid.Y].velocity * WaveArray[grid.X][grid.Y].length;
}

/**
 * �����g�̐�������
 * @param [position] Actor��world���W
 * @param [rotate]   Actor�̉�]
 */
void AWaterField::GenerateAccelWave(const FVector& position, const FRotator& rotate) {
	FVector grid = CulcFieldGrid(position);

	//���łɔg����������Ă�����
	if (WaveArray[grid.X][grid.Y].isValid == true) {
		return;
	}
	FVector vel(FMath::Cos(rotate.Yaw), FMath::Sin(rotate.Yaw), 0.0f);
	vel.Normalize();
	WaveArray[grid.X][grid.Y].velocity = vel;
	WaveArray[grid.X][grid.Y].length = 700.0f;
	WaveArray[grid.X][grid.Y].startTime = FDateTime::Now();
	WaveArray[grid.X][grid.Y].isValid = true;

	UpdateFlowMap(grid);
	UpdateFlag = true;
}

/**
 * ����������
 */
void AWaterField::Initialize() {
	UpdateFlag = false;
	//�t�B�[���h�̏c���̒����A�O���b�h1�ӂ̒����𒲂ׂ�
	FVector origin, boxExtent;
	GetActorBounds(false, origin, boxExtent);
	Width = boxExtent.X;
	Height = boxExtent.Y;

	EdgeW = Width / Row;
	EdgeH = Height / Column;

	//�g���ۑ��z��̏�����
	WaveArray.Init(TArray<FAccelWaveInfo>(), Row);
	for (int32 i = 0; i < WaveArray.Num(); i++) {
		WaveArray[i].Init(FAccelWaveInfo(), Column);
	}

	//�摜�F��񏉊���
	TextureColorData.Init(Fr8g8b8a8(), TEXTURE_EDGE_W * TEXTURE_EDGE_H);
	for (int32 i = 0; i < TEXTURE_EDGE_W * TEXTURE_EDGE_H; i++) {
		TextureColorData[i].r = NEUTRAL;
		TextureColorData[i].g = NEUTRAL;
		TextureColorData[i].b = 0;
		TextureColorData[i].a = 0;
	}
	EdgeTexW = TEXTURE_EDGE_W * 1.0f / Row;
	EdgeTexH = TEXTURE_EDGE_H * 1.0f / Column;

	CreateTextureAndMaterial();
}

/**
 * �}�e���A����flowMap�̍쐬
 */
void AWaterField::CreateTextureAndMaterial() {
	//�}�e���A���̍쐬
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
	UMaterialInstanceDynamic* Material = Primitive->CreateAndSetMaterialInstanceDynamicFromMaterial(0, CopyWaterMaterial);

	//�e�N�X�`���̍쐬
	FlowMap = UTexture2D::CreateTransient(TEXTURE_EDGE_W, TEXTURE_EDGE_H, PF_R8G8B8A8);

	UpdateTexture();

	// �}�e���A���C���X�^���X�փe�N�X�`���[�p�����[�^�[��ݒ肷��B�^����l�̌^�� UTexture2D*
	Material->SetTextureParameterValue("FlowMap", FlowMap);
	VisualMesh->SetMaterial(0, Material);
}

/**
 * �e�N�X�`���̍X�V���s��
 */
void AWaterField::UpdateTexture() {
	auto locked_bulk_data = FlowMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, TextureColorData.GetData(), sizeof(Fr8g8b8a8) * TextureColorData.Num());
	FlowMap->PlatformData->Mips[0].BulkData.Unlock();
	FlowMap->UpdateResource();
}

/**
 * flowMap�̐F���̍X�V���s��
 * @param [fieldGrid] Actor��Grid���W
 */
void AWaterField::UpdateFlowMap(const FVector& fieldGrid) {
	//�e�N�X�`���̃O���b�h���W
	int32 texX = FMath::CeilToInt(fieldGrid.Y) * EdgeTexW;
	int32 texY = FMath::CeilToInt(fieldGrid.X) * EdgeTexH;

	int32 index = (TEXTURE_EDGE_W * texX) + texY;

	FVector vel = WaveArray[fieldGrid.X][fieldGrid.Y].velocity;
	vel *= 50;
	//uint8 x = 
	int32 forCount = 0;
	for (int i = index; i < index + EdgeTexW; i++) {
		int startPoint = index + (TEXTURE_EDGE_W * forCount);
		for (int j = startPoint; j < startPoint + EdgeTexH; j++) {
			if (TextureColorData.Num() <= j) {
				continue;
			}
			TextureColorData[j].r = FMath::CeilToInt(vel.Y) + NEUTRAL;
			TextureColorData[j].g = FMath::CeilToInt(vel.X) + NEUTRAL;
		}
		forCount++;
	}
}

/**
 * �^����ꂽActor�̈ʒu��Grid���W�ɕϊ�����
 * @param [position] Actor��world���W
 * @return Grid���W
 */
FVector AWaterField::CulcFieldGrid(const FVector& position) {
	return FVector(CulcGrid(position.X, Width, Row), CulcGrid(position.Y, Height, Column), 0);
}

/**
 * Field�̕ӂ̒����AGrid�̐�����
 * Grid��̍��W�����߂�
 * @param [position] ���W
 * @param [edge]     ���ɑ΂���ӂ̒���
 * @param [index]    ���ɑ΂��镝�̐�
 * @return ���ɑ΂���Grid���W
 */
int32 AWaterField::CulcGrid(float position, float edge, int32 index) {
	//�O���b�h�Œ��ׂ���͈͂𒴂��Ȃ��悤Clamp���������Ă���
	float clampPos = FMath::Clamp(position, -edge, edge);
	float gridF = ((position + edge) / (edge * 2.0f)) * index;
	int32 grid = FMath::CeilToInt(gridF);
	grid = FMath::Clamp(grid, 0, index - 1);
	return grid;
}
