// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayData.h"

FGamePlayData UPlayDataNormalizer::NormalizePlayData(const FGamePlayData& Data) {
	FGamePlayData Res = Data;
	if (Res.LapTimes.Num() == 3) {
		for (int32 i = 0; i < 3; i++) {
			if (Res.LapTimes[i] < 10.0f) {
				Res.LapTimes[i] = 0.0f;
			}
		}

	} else {
		Res.LapTimes = {0.0f, 0.0f, 0.0f};
	}

	return Res;
}
