// Fill out your copyright notice in the Description page of Project Settings.

#include "BoatDataAsset.h"

void UBoatDataAsset::Import() {
#if WITH_EDITORONLY_DATA
	if (!DataTable) {
		return;
	}
	if (!DataTable->GetRowStruct()->IsChildOf(FBoatParameter::StaticStruct())) {
		return;
	}

	Data.Empty();
	const TArray<FName> Names = DataTable->GetRowNames();

	for (int32 i = 0; i < Names.Num(); i++) {
		const FBoatParameter* Record = DataTable->FindRow<FBoatParameter>(Names[i], FString());

		FBoatParameterRecord Asset;
		Asset.BoatID = i;
		Asset.BoatMesh = Record->BoatMesh;
		Asset.MaxSpeed = Record->MaxSpeed;
		Asset.Acceleration = Record->Acceleration;
		Asset.Control = Record->Control;
		Asset.Mass = Record->Mass;

		Data.Push(Asset);
	}
#endif
}
