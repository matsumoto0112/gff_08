// Fill out your copyright notice in the Description page of Project Settings.

#include "JampBoard.h"

// Sets default values
AJampBoard::AJampBoard() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	JampBoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JampBoardMesh"));
	RootComponent = JampBoardMesh;
}

// Called when the game starts or when spawned
void AJampBoard::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AJampBoard::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
