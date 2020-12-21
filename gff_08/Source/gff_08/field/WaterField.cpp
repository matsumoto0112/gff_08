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

void AWaterField::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	//テクスチャの破棄
	FlowMap->ConditionalBeginDestroy();
	FlowMap->MarkPendingKill();
	FlowMap = nullptr;

	//マテリアルの破棄
	WaterMaterial->ConditionalBeginDestroy();
	WaterMaterial->MarkPendingKill();
	WaterMaterial = nullptr;
}

// Called every frame
void AWaterField::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (IsValid(FlowMap) == false || IsValid(WaterMaterial) == false) {
		return;
	}

	Timer += DeltaTime;
	UpdateWaveInfo();
}

FVector AWaterField::GetAccelVelocity(const FVector& position) {
	const FVector grid = CulcFieldGrid(position);
	if (this == nullptr || IsGrid(grid) == false || WaveArray[grid.X][grid.Y].IsValid == false) {
		return FVector::ZeroVector;
	}

	return WaveArray[grid.X][grid.Y].Velocity;
}

void AWaterField::GenerateAccelWave(const FVector& position, const FRotator& rotate) {
	const FVector grid = CulcFieldGrid(position);
	if (this == nullptr || IsGrid(grid) == false) {
		return;
	}

	FVector vel(FMath::Cos(FMath::DegreesToRadians(rotate.Yaw)), FMath::Sin(FMath::DegreesToRadians(rotate.Yaw)), 0.0f);
	vel.Normalize();
	//すでに波が生成されていたら
	if (WaveArray[grid.X][grid.Y].IsValid == true) {
		//波の生成時間を更新する
		WaveArray[grid.X][grid.Y].StartTime = Timer;
		//波の方向をベクトルの平均値にする
		WaveArray[grid.X][grid.Y].Velocity = (WaveArray[grid.X][grid.Y].Velocity + vel) / 2.0f;
		WaveArray[grid.X][grid.Y].Length = 700.0f;
		return;
	}

	WaveArray[grid.X][grid.Y].Initialize(vel, 700.0f, Timer, true);

	UpdateFlowMap(grid, WaveLifespan);
}

void AWaterField::Initialize() {
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
	TextureColorData.Init(Fr8g8b8a8(NEUTRAL), TEXTURE_EDGE_W * TEXTURE_EDGE_H);
	EdgeTexW = TEXTURE_EDGE_W * 1.0f / Row;
	EdgeTexH = TEXTURE_EDGE_H * 1.0f / Column;

	CreateTextureAndMaterial();

	Timer = 0.0f;
	CurrentRow = 0;
}

void AWaterField::CreateTextureAndMaterial() {
	//マテリアルの作成
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
	WaterMaterial = Primitive->CreateAndSetMaterialInstanceDynamicFromMaterial(0, CopyWaterMaterial);

	//テクスチャの作成
	FlowMap = UTexture2D::CreateTransient(TEXTURE_EDGE_W, TEXTURE_EDGE_H, PF_R8G8B8A8);
	UpdateTexture();

	// マテリアルインスタンスへテクスチャーパラメーターを設定する。与える値の型は UTexture2D*
	WaterMaterial->SetTextureParameterValue("FlowMap", FlowMap);
	WaterMaterial->SetVectorParameterValue("LightColor", LightColor);
	VisualMesh->SetMaterial(0, WaterMaterial);
}

void AWaterField::UpdateWaveInfo() {
	// 1回調べるのに200のfor文を回す
	for (int32 i = 0; i < WaveArray.Num(); i++) {
		if (i >= WaveArray[CurrentRow].Num()) {
			break;
		}
		//そのマスに波が生成されているかどうか
		if (WaveArray[CurrentRow][i].IsValid == false) {
			continue;
		}
		float t = Timer - WaveArray[CurrentRow][i].StartTime;
		int32 power = FMath::Clamp(static_cast<int32>(WaveLifespan - t), 0, static_cast<int32>(WaveLifespan));
		UpdateFlowMap(FVector(CurrentRow, i, 0), power);
		WaveArray[CurrentRow][i].Length *= FMath::Clamp((t / WaveLifespan), 0.0f, 1.0f);
		//生存時間を過ぎていたら
		if (t >= WaveLifespan) {
			WaveArray[CurrentRow][i].Initialize(FVector::ZeroVector, 0.0f, 0.0f, false);
		}
	}
	CurrentRow++;
	if (CurrentRow >= WaveArray.Num()) {
		CurrentRow = 0;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Update End")));
	}

	UpdateTexture();
}

void AWaterField::UpdateTexture() {
	auto locked_bulk_data = FlowMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, TextureColorData.GetData(), sizeof(Fr8g8b8a8) * TextureColorData.Num());
	FlowMap->PlatformData->Mips[0].BulkData.Unlock();
	FlowMap->UpdateResource();
}

void AWaterField::UpdateFlowMap(const FVector& fieldGrid, const int32 power) {
	//テクスチャのグリッド座標
	const int32 texX = FMath::CeilToInt(fieldGrid.Y) * EdgeTexW;
	const int32 texY = FMath::CeilToInt(fieldGrid.X) * EdgeTexH;

	const int32 index = (TEXTURE_EDGE_W * texX) + texY;

	const FVector vel = WaveArray[fieldGrid.X][fieldGrid.Y].Velocity * power;

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
	//グリッドで調べられる範囲を超えないようClamp処理をしておく
	const float gridF = ((position + edge) / (edge * 2.0f)) * index;
	int32 grid = FMath::CeilToInt(gridF);
	grid = FMath::Clamp(grid, 0, index - 1);
	return grid - 1;
}

bool AWaterField::IsGrid(const FVector& grid) {
	//グリッド内に収まっているなら
	if (grid.X < WaveArray.Num() && grid.Y < WaveArray[0].Num()) {
		return true;
	}
	return false;
}
