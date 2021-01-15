// Fill out your copyright notice in the Description page of Project Settings.

#include "RankingSort.h"

#include "gff_08/utils/MyGameInstance.h"

TArray<FGamePlayData> URankingSort::GetPlayDatasSortedByRanking() {
	auto Data = UMyGameInstance::GetInstance()->GetPlayData();
	auto GetSumTimes = [](const TArray<float>& Times) -> TTuple<int32, float> {
		float Res = 0.0f;
		for (int32 i = 0; i < 3; i++) {
			if (!Times.IsValidIndex(i)) {
				return TTuple<int32, float>{i, Res};
			}
			if (Times[i] == 0.0f) {
				return TTuple<int32, float>{i, Res};
			}
			Res += Times[i];
		}

		return TTuple<int32, float>{3, Res};
	};

	TArray<FGamePlayData> Res;
	Res.Push(Data->Player1Data);
	Res.Push(Data->Player2Data);
	Res.Push(Data->Player3Data);
	Res.Push(Data->Player4Data);
	Res.Sort([GetSumTimes](const auto& A, const auto& B) {
		const auto Res_A = GetSumTimes(A.LapTimes);
		const int32 LapCount_A = Res_A.Get<0>();
		const float SumLapTimes_A = Res_A.Get<1>();

		const auto Res_B = GetSumTimes(B.LapTimes);
		const int32 LapCount_B = Res_B.Get<0>();
		const float SumLapTimes_B = Res_B.Get<1>();

		if (LapCount_A == LapCount_B) {
			return SumLapTimes_A < SumLapTimes_B;
		} else {
			return LapCount_A > LapCount_B;
		}
	});

	for (auto&& R : Res) {
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green,
			FString::Format(TEXT("{0}'s data ({1}, {2}, {3})"), {R.PlayerIndex, R.LapTimes[0], R.LapTimes[1], R.LapTimes[2]}));
	}
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
