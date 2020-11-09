// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterField.h"

// Sets default values
AWaterField::AWaterField() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���b�V���R���|�[�l���g��ǉ�
	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// staticMesh���q�I�u�W�F�N�g�Ƃ��Ĕz�u����
	visualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cubeVisualAsset(TEXT("/Engine/EngineMeshes/Cube"));

	if (cubeVisualAsset.Succeeded() == true) {
		visualMesh->SetStaticMesh(cubeVisualAsset.Object);
		visualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AWaterField::BeginPlay() {
	Super::BeginPlay();

	updateFlag = false;
	//�t�B�[���h�̏c���̒����A�O���b�h1�ӂ̒����𒲂ׂ�
	FVector origin, boxExtent;
	GetActorBounds(false, origin, boxExtent);
	width = boxExtent.X;
	height = boxExtent.Y;

	edgeW = width / row;
	edgeH = height / column;

	waveArray.Init(TArray<FAccelWaveInfo>(), row);
	for (int32 i = 0; i < waveArray.Num(); i++) {
		waveArray[i].Init(FAccelWaveInfo(), column);
	}

	//�摜�F��񏉊���
	textureColorData.Init(Fr8g8b8a8(), TEXTURE_EDGE_W * TEXTURE_EDGE_H);
	for (int32 i = 0; i < TEXTURE_EDGE_W * TEXTURE_EDGE_H; i++) {
		textureColorData[i].r = 255 / 2;
		textureColorData[i].g = 255 / 2;
		textureColorData[i].b = 0;
	}
	edgeTexW = TEXTURE_EDGE_W * 1.0f / row;
	edgeTexH = TEXTURE_EDGE_H * 1.0f / column;

	CreateTextureAndMaterial();
}
// Called every frame
void AWaterField::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (updateFlag == false) {
		return;
	}

	auto locked_bulk_data = flowMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, textureColorData.GetData(), sizeof(Fr8g8b8a8) * textureColorData.Num());
	flowMap->PlatformData->Mips[0].BulkData.Unlock();
	flowMap->UpdateResource();

	updateFlag = false;
}

/*
 �ʒu����O���b�h���W�����߁A���̏ꏊ�̉����g�̏����擾����
*/
FVector AWaterField::GetAccelVelocity(FVector position) {
	FVector grid = CulcFieldGrid(position);
	if (waveArray[grid.X][grid.Y].isValid == false) {
		return FVector::ZeroVector;
	}

	return waveArray[grid.X][grid.Y].velocity * waveArray[grid.X][grid.Y].length;
}

/*
 �����g�̐�������
*/
void AWaterField::GenerateAccelWave(FVector position, FRotator rotate) {
	FVector grid = CulcFieldGrid(position);

	if (waveArray[grid.X][grid.Y].isValid == true) {
		return;
	}
	FVector vel(FMath::Cos(rotate.Yaw), FMath::Sin(rotate.Yaw), 0.0f);
	vel.Normalize();
	waveArray[grid.X][grid.Y].velocity = vel;
	waveArray[grid.X][grid.Y].length = 700.0f;
	waveArray[grid.X][grid.Y].startTime = FDateTime::Now();
	waveArray[grid.X][grid.Y].isValid = true;

	UpdateFlowMap(grid);
	updateFlag = true;
}

void AWaterField::CreateTextureAndMaterial() {
	//�}�e���A���̍쐬
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
	UMaterialInstanceDynamic* Material = Primitive->CreateAndSetMaterialInstanceDynamicFromMaterial(
		0, Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/M_Water"))));

	//�e�N�X�`���̍쐬
	flowMap = UTexture2D::CreateTransient(TEXTURE_EDGE_W, TEXTURE_EDGE_H, PF_R8G8B8A8);

	auto locked_bulk_data = flowMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, textureColorData.GetData(), sizeof(Fr8g8b8a8) * textureColorData.Num());
	flowMap->PlatformData->Mips[0].BulkData.Unlock();
	flowMap->UpdateResource();

	// �}�e���A���C���X�^���X�փe�N�X�`���[�p�����[�^�[��ݒ肷��B�^����l�̌^�� UTexture2D*
	Material->SetTextureParameterValue("FlowMap", flowMap);
	visualMesh->SetMaterial(0, Material);
}

FVector AWaterField::CulcFieldGrid(FVector position) {
	return FVector(CulcGrid(position.X, width, row), CulcGrid(position.Y, height, column), 0);
}

int AWaterField::CulcGrid(float position, float edge, int index) {
	float gridF = ((position + edge) / (edge * 2.0f)) * index;
	int32 grid = FMath::CeilToInt(gridF);
	grid = FMath::Clamp(grid, 0, index - 1);
	return grid;
}

void AWaterField::UpdateFlowMap(FVector fieldGrid) {
	//�e�N�X�`���̃O���b�h���W
	int32 texX = fieldGrid.Y * edgeTexW;
	int32 texY = fieldGrid.X * edgeTexH;

	int32 index = (TEXTURE_EDGE_W * texX) + texY;

	FVector vel = waveArray[fieldGrid.X][fieldGrid.Y].velocity;
	vel *= 100;

	int32 forCount = 0;
	for (int i = index; i < index + edgeTexW; i++) {
		int startPoint = index + (TEXTURE_EDGE_W * forCount);
		for (int j = startPoint; j < startPoint + edgeTexH; j++) {
			if (textureColorData.Num() <= j) {
				continue;
			}
			textureColorData[j].r = (255 / 2) + vel.X;
			textureColorData[j].g = (255 / 2) + vel.Y;
		}
		forCount++;
	}
}
