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
	UE_LOG(LogTemp, Log, TEXT("WaveField test"));

	//for (int i = 0; i < column; i++) {
	//	waveList.push_back(std::vector<FAccelWaveInfo>(row));
	//}
}

// Called every frame
void AWaterField::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

/*
 * テストで作成した関数
 */
void AWaterField::TestMethod() {
	UE_LOG(LogTemp, Log, TEXT("Test"));
}

int AWaterField::CulcGrid(const float gridPos, const float size, const int index) {
	float offset = gridPos + size;
	float s = size * 2.0f;

	offset /= s;

	offset *= index;

	int i = FMath::CeilToInt(offset);
	i = FMath::Min(i, index);
	i = FMath::Max(i, 0);

	if (i >= index) {
		return i - 1;
	}

	return i;
}

FVector AWaterField::GetAccelVelocity(const FVector position) {
	int r = CulcGrid(position.X, width, row);
	int c = CulcGrid(position.Y, height, column);

	if (IsWaveValid(r, c) == false) {
		return FVector();
	}

	return waveList[c][r].velocity * waveList[c][r].length;
}

void AWaterField::AddAccelWave(int r, int c, FVector velocity, float length, AActor* waveObject) {
	waveList[c][r] = FAccelWaveInfo(velocity, length, waveObject);
}

/*
 * グリッド上のオブジェクトがnullじゃないならtrueを返す
 */
bool AWaterField::IsWaveValid(const int r, const int c) {
	return waveList[c][r].waveObject != nullptr;
}
