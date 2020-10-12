// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

#include "MyCheatManager.h"

AMyPlayerController::AMyPlayerController() {
	CheatClass = UMyCheatManager::StaticClass();
}