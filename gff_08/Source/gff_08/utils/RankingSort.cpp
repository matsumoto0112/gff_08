// Fill out your copyright notice in the Description page of Project Settings.

#include "RankingSort.h"

#include "gff_08/utils/MyGameInstance.h"

FAllRacersGamePlayData URankingSort::SortByLapTimes(const FAllRacersGamePlayData& RacersPlayData) {
	FAllRacersGamePlayData Res = RacersPlayData;

	auto GetSumTimes = [](const TArray<float>& Times) {
		if (Times.Num() == 3) {
			float Res = 0.0f;
			for (auto&& Time : Times) {
				Res += Time;
			}
			return Res;
		} else {
			return FLT_MAX;
		}
	};

	//Res.AllRacersData.Sort([GetSumTimes](const auto& A, const auto& B) {
	//	const float SumLapTimes_A = GetSumTimes(A.LapTimes);
	//	const float SumLapTimes_B = GetSumTimes(B.LapTimes);
	//	return SumLapTimes_A < SumLapTimes_B;
	//});

	const int32 MyPlayerIndex = UMyGameInstance::GetInstance()->GetUserData()->GetPlayerIndex();
	//Res.MyBoatIndex =
	//	Res.AllRacersData.IndexOfByPredicate([MyPlayerIndex](const auto& A) { return A.PlayerIndex == MyPlayerIndex; });

	return Res;
}
