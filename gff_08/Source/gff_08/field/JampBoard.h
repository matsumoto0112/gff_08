// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "JampBoard.generated.h"

/**
 * �W�����v��I�u�W�F�N�g
 */
UCLASS()
class GFF_08_API AJampBoard : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJampBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//! �W�����v��̃��b�V��
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* JampBoardMesh;
};
