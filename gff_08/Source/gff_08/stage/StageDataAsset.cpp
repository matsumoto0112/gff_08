// Fill out your copyright notice in the Description page of Project Settings.

#include "StageDataAsset.h"

void UStageDataAsset::Import() {
#if WITH_EDITORONLY_DATA
	if (!DataTable) {
		return;
	}
	if (!DataTable->GetRowStruct()->IsChildOf(FStageData::StaticStruct())) {
		return;
	}

	Data.Empty();
	const TArray<FName> Names = DataTable->GetRowNames();

	for (int32 i = 0; i < Names.Num(); i++) {
		const FStageData* Record = DataTable->FindRow<FStageData>(Names[i], FString());

		FStageDataAssetRecord Asset;
		Asset.StageIndex = i;
		Asset.LapCount = Record->LapCount;
		Asset.StageName = Record->StageName;
		Asset.StageImages = Record->StageImages;
		Asset.MinimapImage = Record->MinimapImage;
		Data.Push(Asset);
	}
#endif
}
