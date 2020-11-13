// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterField.h"

#include "kismet/GamePlayStatics.h"

// Sets default values
AWaterField::AWaterField() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//メッシュコンポーネントを追加
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// staticMeshを子オブジェクトとして配置する
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

FVector AWaterField::GetAccelVelocity(const FVector& position) {
	if (this == nullptr) {
		return FVector::ZeroVector;
	}
	FVector grid = CulcFieldGrid(position);
	if (WaveArray[grid.X][grid.Y].isValid == false) {
		return FVector::ZeroVector;
	}

	return WaveArray[grid.X][grid.Y].velocity;
}

void AWaterField::GenerateAccelWave(const FVector& position, const FRotator& rotate) {
	if (this == nullptr) {
		return;
	}
	FVector grid = CulcFieldGrid(position);

	//すでに波が生成されていたら
	if (WaveArray[grid.X][grid.Y].isValid == true) {
		return;
	}
	// UE_LOG(LogTemp, Log, TEXT("Yaw:%f"), rotate.Yaw);
	FVector vel(FMath::Cos(FMath::DegreesToRadians(rotate.Yaw)), FMath::Sin(FMath::DegreesToRadians(rotate.Yaw)), 0.0f);
	vel.Normalize();
	WaveArray[grid.X][grid.Y].velocity = vel;
	WaveArray[grid.X][grid.Y].length = 700.0f;
	WaveArray[grid.X][grid.Y].startTime = FDateTime::Now();
	WaveArray[grid.X][grid.Y].isValid = true;
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), position, position + vel * 100.0f, FColor::Green, 100.0f, 2.0f);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), position + vel * 100.0f, position + vel * 100.0f + FVector(10,0,0), FColor::Green, 100.0f, 2.0f);

	UpdateFlowMap(grid);
	UpdateFlag = true;
}

void AWaterField::Initialize() {
	UpdateFlag = false;
	//フィールドの縦横の長さ、グリッド1辺の長さを調べる
	FVector origin, boxExtent;
	GetActorBounds(false, origin, boxExtent);
	Width = boxExtent.X;
	Height = boxExtent.Y;

	EdgeW = Width / Row;
	EdgeH = Height / Column;

	//波情報保存配列の初期化
	WaveArray.Init(TArray<FAccelWaveInfo>(), Row);
	for (int32 i = 0; i < WaveArray.Num(); i++) {
		WaveArray[i].Init(FAccelWaveInfo(), Column);
	}

	//画像色情報初期化
	TextureColorData.Init(Fr8g8b8a8(), TEXTURE_EDGE_W * TEXTURE_EDGE_H);
	for (int32 i = 0; i < TEXTURE_EDGE_W * TEXTURE_EDGE_H; i++) {
		TextureColorData[i].r = NEUTRAL;
		TextureColorData[i].g = NEUTRAL;
		TextureColorData[i].b = 0;
		TextureColorData[i].a = 255;
	}
	EdgeTexW = TEXTURE_EDGE_W * 1.0f / Row;
	EdgeTexH = TEXTURE_EDGE_H * 1.0f / Column;

	CreateTextureAndMaterial();
}

void AWaterField::CreateTextureAndMaterial() {
	//マテリアルの作成
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
	UMaterialInstanceDynamic* Material = Primitive->CreateAndSetMaterialInstanceDynamicFromMaterial(0, CopyWaterMaterial);

	//テクスチャの作成
	FlowMap = UTexture2D::CreateTransient(TEXTURE_EDGE_W, TEXTURE_EDGE_H, PF_R8G8B8A8);

	UpdateTexture();

	// マテリアルインスタンスへテクスチャーパラメーターを設定する。与える値の型は UTexture2D*
	Material->SetTextureParameterValue("FlowMap", FlowMap);
	VisualMesh->SetMaterial(0, Material);
}

void AWaterField::UpdateTexture() {
	auto locked_bulk_data = FlowMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, TextureColorData.GetData(), sizeof(Fr8g8b8a8) * TextureColorData.Num());
	FlowMap->PlatformData->Mips[0].BulkData.Unlock();
	FlowMap->UpdateResource();
}

void AWaterField::UpdateFlowMap(const FVector& fieldGrid) {
	//テクスチャのグリッド座標
	int32 texX = FMath::CeilToInt(fieldGrid.Y) * EdgeTexW;
	int32 texY = FMath::CeilToInt(fieldGrid.X) * EdgeTexH;

	int32 index = (TEXTURE_EDGE_W * texX) + texY;

	FVector vel = WaveArray[fieldGrid.X][fieldGrid.Y].velocity;
	vel *= 50;

	int32 forCount = 0;
	for (int i = index; i < index + EdgeTexW; i++) {
		int startPoint = index + (TEXTURE_EDGE_W * forCount);
		for (int j = startPoint; j < startPoint + EdgeTexH; j++) {
			if (TextureColorData.Num() <= j) {
				continue;
			}
			TextureColorData[j].r = FMath::CeilToInt(vel.Y) + NEUTRAL;
			TextureColorData[j].g = FMath::CeilToInt(vel.X * -1) + NEUTRAL;
		}
		forCount++;
	}
}

FVector AWaterField::CulcFieldGrid(const FVector& position) {
	return FVector(CulcGrid(position.X, Width, Row), CulcGrid(position.Y, Height, Column), 0);
}

int32 AWaterField::CulcGrid(float position, float edge, int32 index) {
	//グリッドで調べられる範囲を超えないようClamp処理をしておく
	float clampPos = FMath::Clamp(position, -edge, edge);
	float gridF = ((position + edge) / (edge * 2.0f)) * index;
	int32 grid = FMath::CeilToInt(gridF);
	grid = FMath::Clamp(grid, 0, index - 1);
	return grid - 1;
}
