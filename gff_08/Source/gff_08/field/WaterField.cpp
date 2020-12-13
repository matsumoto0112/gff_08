// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterField.h"

#include "kismet/GamePlayStatics.h"

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
	GetWorld()->GetTimerManager().SetTimer(handle, this, &AWaterField::UpdateWaveInfo, LIMIT_TIME, true);
}

void AWaterField::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(handle);

	//�e�N�X�`���̔j��
	FlowMap->ConditionalBeginDestroy();
	FlowMap = nullptr;

	//�}�e���A���̔j��
	WaterMaterial->ConditionalBeginDestroy();
	WaterMaterial = nullptr;
}

// Called every frame
void AWaterField::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (FlowMap == nullptr || WaterMaterial == nullptr) {
		return;
	}

	Timer += DeltaTime;
	if (UpdateFlag == false) {
		return;
	}

	UpdateTexture();

	UpdateFlag = false;
}

FVector AWaterField::GetAccelVelocity(const FVector& position) {
	FVector grid = CulcFieldGrid(position);
	if (this == nullptr || IsGrid(grid) == false || WaveArray[grid.X][grid.Y].IsValid == false) {
		return FVector::ZeroVector;
	}

	return WaveArray[grid.X][grid.Y].Velocity;
}

void AWaterField::GenerateAccelWave(const FVector& position, const FRotator& rotate) {
	FVector grid = CulcFieldGrid(position);
	if (this == nullptr || IsGrid(grid) == false) {
		return;
	}

	//���łɔg����������Ă�����
	if (WaveArray[grid.X][grid.Y].IsValid == true) {
		//�g�̐������Ԃ��X�V����
		WaveArray[grid.X][grid.Y].StartTime = Timer;
		return;
	}

	FVector vel(FMath::Cos(FMath::DegreesToRadians(rotate.Yaw)), FMath::Sin(FMath::DegreesToRadians(rotate.Yaw)), 0.0f);
	vel.Normalize();
	WaveArray[grid.X][grid.Y].Initialize(vel, 700.0f, Timer, true);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), position, position + vel * 100.0f, FColor::Green, 40.0f, 2.0f);

	UpdateFlowMap(grid);
	UpdateFlag = true;
}

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
	TextureColorData.Init(Fr8g8b8a8(NEUTRAL), TEXTURE_EDGE_W * TEXTURE_EDGE_H);
	EdgeTexW = TEXTURE_EDGE_W * 1.0f / Row;
	EdgeTexH = TEXTURE_EDGE_H * 1.0f / Column;

	CreateTextureAndMaterial();

	Timer = 0.0f;
	ColumnArrayIndex = 0;
}

void AWaterField::CreateTextureAndMaterial() {
	//�}�e���A���̍쐬
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
	WaterMaterial = Primitive->CreateAndSetMaterialInstanceDynamicFromMaterial(0, CopyWaterMaterial);

	//�e�N�X�`���̍쐬
	FlowMap = UTexture2D::CreateTransient(TEXTURE_EDGE_W, TEXTURE_EDGE_H, PF_R8G8B8A8);

	UpdateTexture();

	// �}�e���A���C���X�^���X�փe�N�X�`���[�p�����[�^�[��ݒ肷��B�^����l�̌^�� UTexture2D*
	WaterMaterial->SetTextureParameterValue("FlowMap", FlowMap);
	WaterMaterial->SetVectorParameterValue("LightColor", LightColor);
	VisualMesh->SetMaterial(0, WaterMaterial);
}

void AWaterField::UpdateWaveInfo() {
	bool updateFlag = false;
	int32 addColumnIndex = 50;
	for (int32 i = 0; i < WaveArray.Num(); i++) {
		for (int32 j = ColumnArrayIndex; j < ColumnArrayIndex + addColumnIndex; j++) {
			if (j >= WaveArray[i].Num()) {
				break;
			}
			if (WaveArray[i][j].IsValid == false) {
				continue;
			}
			float t = Timer - WaveArray[i][j].StartTime;
			if (t >= WaveLifespan) {
				WaveArray[i][j].Initialize(FVector::ZeroVector, 0.0f, 0.0f, false);
				UpdateFlowMap(FVector(i, j, 0));
				updateFlag = true;
			}
		}
	}
	ColumnArrayIndex += addColumnIndex;
	if (ColumnArrayIndex >= Column) {
		ColumnArrayIndex = 0;
	}

	if (updateFlag == true) {
		UpdateTexture();
	}
}

void AWaterField::UpdateTexture() {
	auto locked_bulk_data = FlowMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, TextureColorData.GetData(), sizeof(Fr8g8b8a8) * TextureColorData.Num());
	FlowMap->PlatformData->Mips[0].BulkData.Unlock();
	FlowMap->UpdateResource();
}

void AWaterField::UpdateFlowMap(const FVector& fieldGrid) {
	//�e�N�X�`���̃O���b�h���W
	int32 texX = FMath::CeilToInt(fieldGrid.Y) * EdgeTexW;
	int32 texY = FMath::CeilToInt(fieldGrid.X) * EdgeTexH;

	int32 index = (TEXTURE_EDGE_W * texX) + texY;

	FVector vel = WaveArray[fieldGrid.X][fieldGrid.Y].Velocity;
	vel *= 50;

	int32 forCount = 0;
	for (int32 i = index; i < index + EdgeTexW; i++) {
		int32 startPoint = index + (TEXTURE_EDGE_W * forCount);
		for (int32 j = startPoint; j < startPoint + EdgeTexH; j++) {
			if (TextureColorData.Num() <= j) {
				continue;
			}
			TextureColorData[j].R = FMath::CeilToInt(vel.X) + NEUTRAL;
			TextureColorData[j].G = FMath::CeilToInt(vel.Y * -1) + NEUTRAL;
		}
		forCount++;
	}
}

FVector AWaterField::CulcFieldGrid(const FVector& position) {
	return FVector(CulcGrid(position.X, Width, Row), CulcGrid(position.Y, Height, Column), 0);
}

int32 AWaterField::CulcGrid(float position, float edge, int32 index) {
	//�O���b�h�Œ��ׂ���͈͂𒴂��Ȃ��悤Clamp���������Ă���
	float clampPos = FMath::Clamp(position, -edge, edge);
	float gridF = ((position + edge) / (edge * 2.0f)) * index;
	int32 grid = FMath::CeilToInt(gridF);
	grid = FMath::Clamp(grid, 0, index - 1);
	return grid - 1;
}

bool AWaterField::IsGrid(const FVector& grid) {
	//�O���b�h���Ɏ��܂��Ă���Ȃ�
	if (grid.X < WaveArray.Num() && grid.Y < WaveArray[0].Num()) {
		return true;
	}
	return false;
}
