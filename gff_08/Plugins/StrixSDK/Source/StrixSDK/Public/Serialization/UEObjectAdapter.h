/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include <strix/net/object/ObjectAdapter.h>
#include <strix/net/object/Number.h>
#include "Serialization/UEObjectsSerializers.h"

namespace strix { namespace net { namespace object {

/** Helper class used for creating Strix Object pointers from Unreal types.
 */
class UEObjectAdapter : public ObjectAdapter
{
public:
	UEObjectAdapter(FVector& val);
	UEObjectAdapter(FRotator& val);
	UEObjectAdapter(FTransform& val);
	UEObjectAdapter(FString& val);
	UEObjectAdapter(FText& val);
	UEObjectAdapter(FQuat& val);

	UEObjectAdapter(TArray<bool>& val);
	UEObjectAdapter(TArray<uint8>& val);
	UEObjectAdapter(TArray<int32>& val);
	UEObjectAdapter(TArray<float>& val);
	UEObjectAdapter(TArray<FVector>& val);
	UEObjectAdapter(TArray<FQuat>&);
	UEObjectAdapter(TArray<FRotator>& val);
	UEObjectAdapter(TArray<FTransform>& val);
	UEObjectAdapter(TArray <strix::net::object::ObjectPtr>& val);
	UEObjectAdapter(TArray<FString>& val);
	UEObjectAdapter(TArray<FText>& val);

	UEObjectAdapter(TSet<uint8>& val);
	UEObjectAdapter(TSet<int32>& val);
	UEObjectAdapter(TSet<float>& val);
	UEObjectAdapter(TSet<FVector>& val);
	UEObjectAdapter(TSet<FString>& val);

	UEObjectAdapter(TMap<int, bool>& val);
	UEObjectAdapter(TMap<int, uint8>& val);
	UEObjectAdapter(TMap<int, int>& val);
	UEObjectAdapter(TMap<int, float>& val);
	UEObjectAdapter(TMap<int, FVector>& val);
	UEObjectAdapter(TMap<int, FRotator>& val);
	UEObjectAdapter(TMap<int, strix::net::object::ObjectPtr>& val);
	UEObjectAdapter(TMap<int, FString>& val);

	UEObjectAdapter(TMap<FString, bool>& val);
	UEObjectAdapter(TMap<FString, uint8>& val);
	UEObjectAdapter(TMap<FString, int>& val);
	UEObjectAdapter(TMap<FString, float>& val);
	UEObjectAdapter(TMap<FString, FVector>& val);
	UEObjectAdapter(TMap<FString, FRotator>& val);
	UEObjectAdapter(TMap<FString, strix::net::object::ObjectPtr>& val);
	UEObjectAdapter(TMap<FString, FString>& val);

	UEObjectAdapter(FStrixNetworkId& val);

	std::shared_ptr<FTransformTArrayObject> BuildTransformArray(TArray<FTransform>& val)
	{
	    TArray<FTransformObject> objects;
	    for (auto transform : val)
	    {
		FTransformObject transformObject = FTransformObject(transform);
		objects.Add(transformObject);
	    }
	    return std::make_shared<FTransformTArrayObject>(objects);
	}

	std::shared_ptr<FTextTArrayObject> BuildTextArray(TArray<FText>& val)
	{
	    TArray<FTextObject> objects;
	    for (auto text : val)
	    {
		FTextObject textObject = FTextObject(text);
		objects.Add(textObject);
	    }
	    return std::make_shared<FTextTArrayObject>(objects);
	}
};

} } }
