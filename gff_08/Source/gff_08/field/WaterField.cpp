// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterField.h"

// Sets default values
AWaterField::AWaterField() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//メッシュコンポーネントを追加
	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// staticMeshを子オブジェクトとして配置する
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

	Initialize();
}

// Called every frame
void AWaterField::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (updateFlag == false) {
		return;
	}

	UpdateTexture();

	updateFlag = false;
}

/**
 * 位置からグリッド座標を求め、その場所の加速波の情報を取得する
 * @param [position] Actorのworld座標
 * @return 加速度
 */
FVector AWaterField::GetAccelVelocity(const FVector position) {
	FVector grid = CulcFieldGrid(position);
	if (waveArray[grid.X][grid.Y].isValid == false) {
		return FVector::ZeroVector;
	}

	return waveArray[grid.X][grid.Y].velocity * waveArray[grid.X][grid.Y].length;
}

/**
 * 加速波の生成処理
 * @param [position] Actorのworld座標
 * @param [rotate]   Actorの回転
 */
void AWaterField::GenerateAccelWave(const FVector position, const FRotator rotate) {
	FVector grid = CulcFieldGrid(position);

	//すでに波が生成されていたら
	if (waveArray[grid.X][grid.Y].isValid == true) {
		return;
	}
	FVector vel(FMath::Cos(rotate.Pitch), FMath::Sin(rotate.Pitch), 0.0f);
	vel.Normalize();
	waveArray[grid.X][grid.Y].velocity = vel;
	waveArray[grid.X][grid.Y].length = 700.0f;
	waveArray[grid.X][grid.Y].startTime = FDateTime::Now();
	waveArray[grid.X][grid.Y].isValid = true;

	UpdateFlowMap(grid);
	updateFlag = true;
}

/**
 * 初期化処理
 */
void AWaterField::Initialize() {
	updateFlag = false;
	//フィールドの縦横の長さ、グリッド1辺の長さを調べる
	FVector origin, boxExtent;
	GetActorBounds(false, origin, boxExtent);
	width = boxExtent.X;
	height = boxExtent.Y;

	edgeW = width / row;
	edgeH = height / column;

	//波情報保存配列の初期化
	waveArray.Init(TArray<FAccelWaveInfo>(), row);
	for (int32 i = 0; i < waveArray.Num(); i++) {
		waveArray[i].Init(FAccelWaveInfo(), column);
	}

	//画像色情報初期化
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

/**
 * マテリアルとflowMapの作成
 */
void AWaterField::CreateTextureAndMaterial() {
	//マテリアルの作成
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
	UMaterialInstanceDynamic* Material = Primitive->CreateAndSetMaterialInstanceDynamicFromMaterial(0, copyWaterMaterial);

	//テクスチャの作成
	flowMap = UTexture2D::CreateTransient(TEXTURE_EDGE_W, TEXTURE_EDGE_H, PF_R8G8B8A8);

	UpdateTexture();

	// マテリアルインスタンスへテクスチャーパラメーターを設定する。与える値の型は UTexture2D*
	Material->SetTextureParameterValue("FlowMap", flowMap);
	visualMesh->SetMaterial(0, Material);
}

/**
 * テクスチャの更新を行う
 */
void AWaterField::UpdateTexture() {
	auto locked_bulk_data = flowMap->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, textureColorData.GetData(), sizeof(Fr8g8b8a8) * textureColorData.Num());
	flowMap->PlatformData->Mips[0].BulkData.Unlock();
	flowMap->UpdateResource();
}

/**
 * flowMapの色情報の更新を行う
 * @param [fieldGrid] ActorのGrid座標
 */
void AWaterField::UpdateFlowMap(const FVector fieldGrid) {
	//テクスチャのグリッド座標
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

/**
 * 与えられたActorの位置をGrid座標に変換する
 * @param [position] Actorのworld座標
 * @return Grid座標
 */
FVector AWaterField::CulcFieldGrid(const FVector position) {
	return FVector(CulcGrid(position.X, width, row), CulcGrid(position.Y, height, column), 0);
}

/**
 * Fieldの辺の長さ、Gridの数から
 * Grid上の座標を求める
 * @param [position] 座標
 * @param [edge]     軸に対する辺の長さ
 * @param [index]    軸に対する幅の数
 * @return 軸に対するGrid座標
 */
int32 AWaterField::CulcGrid(float position, float edge, int32 index) {
	float gridF = ((position + edge) / (edge * 2.0f)) * index;
	int32 grid = FMath::CeilToInt(gridF);
	grid = FMath::Clamp(grid, 0, index - 1);
	return grid;
}
