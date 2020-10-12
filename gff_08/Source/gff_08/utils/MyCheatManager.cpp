// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCheatManager.h"

void UMyCheatManager::MyCheatCommand() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("CheatCommand!"));
	}
}