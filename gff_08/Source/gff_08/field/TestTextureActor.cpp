// Fill out your copyright notice in the Description page of Project Settings.

#include "TestTextureActor.h"

#include <array>

// Sets default values
ATestTextureActor::ATestTextureActor() {
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
void ATestTextureActor::BeginPlay() {
	Super::BeginPlay();
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
	UMaterialInstanceDynamic* Material = Primitive->CreateAndSetMaterialInstanceDynamicFromMaterial(
		0, Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/M_Water"))));

	my_data.Init(Fr8g8b8a8(), width * height);

	texture = UTexture2D::CreateTransient(width, height, PF_R8G8B8A8);
	for (int i = 0; i < width * height; i++) {
		my_data[i].r = 255 / 2;
		my_data[i].g = 255 / 2;
		my_data[i].b = 0;
	}

	for (int i = 0; i < width * height; i++) {
		
		my_data[i].r += 10;
	}

	auto locked_bulk_data = texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(locked_bulk_data, my_data.GetData(), sizeof(Fr8g8b8a8) * my_data.Num());
	texture->PlatformData->Mips[0].BulkData.Unlock();
	texture->UpdateResource();

	// マテリアルインスタンスへテクスチャーパラメーターを設定する。与える値の型は UTexture2D*
	Material->SetTextureParameterValue("FlowMap", texture);
	visualMesh->SetMaterial(0, Material);
}

// Called every frame
void ATestTextureActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//static FRandomStream f;
	//for (int i = 0; i < my_data.Num(); i++) {
	//	 float rnd = f.FRand();
	//	 my_data[i].r = rnd * 255;
	//}
	//auto locked_bulk_data = texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	//FMemory::Memcpy(locked_bulk_data, my_data.GetData(), sizeof(Fr8g8b8a8) * my_data.Num());
	//texture->PlatformData->Mips[0].BulkData.Unlock();
	//texture->UpdateResource();
}
