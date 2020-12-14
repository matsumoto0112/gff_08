// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceTimer.h"

#include "gff_08/ui/UITime.h"

void URaceTimer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetWorld()->IsPaused()) {
		return;
	}

	if (!bIsStarted)
		return;
	CurrentTime += InDeltaTime;

	//ŽžŠÔ•\Ž¦—pUI‚ÌŽæ“¾
	UUITime* UITime = Cast<UUITime>(GetWidgetFromName("BP_UITime"));
	if (UITime && bUpdateImagesFlag) {
		UITime->SetTimeFloat(CurrentTime);
	}
}

void URaceTimer::Start() {
	CurrentTime = 0.0f;
	bIsStarted = true;
}

void URaceTimer::Stop() {
	bIsStarted = false;
}

void URaceTimer::StopUpdateImages() {
	bUpdateImagesFlag = false;
}
