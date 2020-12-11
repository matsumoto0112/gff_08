// Fill out your copyright notice in the Description page of Project Settings.

#include "StringUtils.h"

FString UStringUtils::GetEvNumsFromMes(const FString message) {
	FString m("");
	const FRegexPattern pattern = FRegexPattern(FString(TEXT(" /^[^a-z^A-Z^0-9]+$/")));
	FRegexMatcher matcher(pattern, message);
	while (matcher.FindNext()) {
		FString numStr = matcher.GetCaptureGroup(1);
		if (numStr.IsNumeric()) {
		}
		m += numStr;
	}

	return m;
}