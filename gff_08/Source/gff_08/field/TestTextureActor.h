// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TestTextureActor.generated.h"

USTRUCT(BlueprintType)
struct Fr8g8b8a8 {
	GENERATED_USTRUCT_BODY();

	uint8 r = 255, g = 255, b = 255, a = 255;
};

UCLASS()
class GFF_08_API ATestTextureActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestTextureActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* visualMesh;	 //ÉÅÉbÉVÉÖèÓïÒ

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static constexpr int32 width = 1024;
	static constexpr int32 height = 1024;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* texture;
	UPROPERTY()
	TArray<Fr8g8b8a8> my_data;
};
