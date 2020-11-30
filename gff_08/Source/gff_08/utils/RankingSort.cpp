// Fill out your copyright notice in the Description page of Project Settings.

#include "RankingSort.h"

#include "gff_08/utils/MyGameInstance.h"

TArray<FGamePlayData> URankingSort::GetPlayDatasSortedByRanking() {
	auto Data = UMyGameInstance::GetInstance()->GetPlayData();
	auto GetSumTimes = [](const TArray<float>& Times) {
		if (Times.Num() == 3) {
			float Res = 0.0f;
			for (auto&& Time : Times) {
				// 0.0•b‚ªƒZƒbƒg‚³‚ê‚Ä‚¢‚½‚çŽü‰ñ’x‚ê
				if (Time <= 0.01f) {
					return FLT_MAX;
				}
				Res += Time;
			}
			return Res;
		} else {
			return FLT_MAX;
		}
	};

	TArray<FGamePlayData> Res;
	Res.Push(Data->Player1Data);
	Res.Push(Data->Player2Data);
	Res.Push(Data->Player3Data);
	Res.Push(Data->Player4Data);
	Res.Sort([GetSumTimes](const auto& A, const auto& B) {
		const float SumLapTimes_A = GetSumTimes(A.LapTimes);
		const float SumLapTimes_B = GetSumTimes(B.LapTimes);
		return SumLapTimes_A < SumLapTimes_B;
	});

	return Res;
}

float URankingSort::GetSumTimes(const FGamePlayData& Data) {
	float Res = 0.0f;
	for (auto&& Time : Data.LapTimes) {
		if (Time <= 0.01f) {
			return 0.0f;
		}
		Res += Time;
	}
	return Res;
}

FGamePlayData URankingSort::GetMyPlayerResultData() {
	UMyGameInstance* Instance = UMyGameInstance::GetInstance();
	switch (Instance->GetUserData()->GetPlayerIndex()) {
		case 0:
			return Instance->GetPlayData()->Player1Data;
		case 1:
			return Instance->GetPlayData()->Player2Data;
		case 2:
			return Instance->GetPlayData()->Player3Data;
		default:
			return Instance->GetPlayData()->Player4Data;
	}
}
