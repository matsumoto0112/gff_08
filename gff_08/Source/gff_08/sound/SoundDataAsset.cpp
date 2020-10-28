// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundDataAsset.h"

void USoundDataAsset::Import() {
#if WITH_EDITORONLY_DATA
	if (!DataTable) {
		return;
	}
	if (!DataTable->GetRowStruct()->IsChildOf(FSoundData::StaticStruct())) {
		return;
	}

	Data.Empty();
	const TArray<FName> Names = DataTable->GetRowNames();

	for (int32 i = 0; i < Names.Num(); i++) {
		const FSoundData* Record = DataTable->FindRow<FSoundData>(Names[i], FString());

		FSoundDataAssetRecord Asset;
		Asset.Sound = Record->Sound;
		Asset.SoundAttenuation = Record->SoundAttenuation;

		Data.Emplace(Record->SoudnType, Asset);
	}
#endif
}
