/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Serialization/UEObjectAdapter.h"

#include "Serialization/UEObjectsSerializers.h"

namespace strix { namespace net { namespace object {

UEObjectAdapter::UEObjectAdapter(FVector& val) : ObjectAdapter(std::make_shared<FVectorObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(FRotator & val) : ObjectAdapter(std::make_shared<FRotatorObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(FTransform & val) : ObjectAdapter(std::make_shared<FTransformObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(FString & val) : ObjectAdapter(std::make_shared<FStringObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(FText & val) : ObjectAdapter(std::make_shared<FTextObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(FQuat& val) : ObjectAdapter(std::make_shared<FQuatObject>(val)) {}

UEObjectAdapter::UEObjectAdapter(TArray<bool>& val) : ObjectAdapter(std::make_shared<BoolTArrayObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TArray<uint8>& val) : ObjectAdapter(std::make_shared<ByteTArrayObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TArray<int32>& val) : ObjectAdapter(std::make_shared<IntTArrayObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TArray<float>& val) : ObjectAdapter(std::make_shared<FloatTArrayObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TArray<FVector>& val) : ObjectAdapter(std::make_shared<FVectorTArrayObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TArray<FQuat>& val) : ObjectAdapter(std::make_shared<FQuatTArrayObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TArray<FRotator>& val) : ObjectAdapter(std::make_shared<FRotatorTArrayObject>(val)) {}

UEObjectAdapter::UEObjectAdapter(TArray<FTransform>& val) : ObjectAdapter(BuildTransformArray(val)) {}

UEObjectAdapter::UEObjectAdapter(TArray<strix::net::object::ObjectPtr>& val) : ObjectAdapter(std::make_shared<ObjectTArrayObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TArray<FString>& val) : ObjectAdapter(std::make_shared<FStringTArrayObject>(val)) {}

UEObjectAdapter::UEObjectAdapter(TArray<FText>& val) : ObjectAdapter(BuildTextArray(val)) {}

UEObjectAdapter::UEObjectAdapter(TSet<uint8>& val) : ObjectAdapter(std::make_shared<ByteTSetObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TSet<int32>& val) : ObjectAdapter(std::make_shared<IntTSetObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TSet<float>& val) : ObjectAdapter(std::make_shared<FloatTSetObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TSet<FVector>& val) : ObjectAdapter(std::make_shared<FVectorTSetObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TSet<FString>& val) : ObjectAdapter(std::make_shared<FStringTSetObject>(val)) {}

UEObjectAdapter::UEObjectAdapter(TMap<int, bool>& val) : ObjectAdapter(std::make_shared<IntKeyBoolTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<int, uint8>& val) : ObjectAdapter(std::make_shared<IntKeyByteTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<int, int>& val) : ObjectAdapter(std::make_shared<IntKeyIntTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<int, float>& val) : ObjectAdapter(std::make_shared<IntKeyFloatTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<int, FVector>& val) : ObjectAdapter(std::make_shared<IntKeyFVectorTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<int, FRotator>& val) : ObjectAdapter(std::make_shared<IntKeyFRotatorTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<int, strix::net::object::ObjectPtr>& val) : ObjectAdapter(std::make_shared<IntKeyObjectTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<int, FString>& val) : ObjectAdapter(std::make_shared<IntKeyFStringTMapObject>(val)) {}

UEObjectAdapter::UEObjectAdapter(TMap<FString, bool>& val) : ObjectAdapter(std::make_shared<StringKeyBoolTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<FString, uint8>& val) : ObjectAdapter(std::make_shared<StringKeyByteTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<FString, int>& val) : ObjectAdapter(std::make_shared<StringKeyIntTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<FString, float>& val) : ObjectAdapter(std::make_shared<StringKeyFloatTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<FString, FVector>& val) : ObjectAdapter(std::make_shared<StringKeyFVectorTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<FString, FRotator>& val) : ObjectAdapter(std::make_shared<StringKeyFRotatorTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<FString, strix::net::object::ObjectPtr>& val) : ObjectAdapter(std::make_shared<StringKeyObjectTMapObject>(val)) {}
UEObjectAdapter::UEObjectAdapter(TMap<FString, FString>& val) : ObjectAdapter(std::make_shared<StringKeyFStringTMapObject>(val)) {}

UEObjectAdapter::UEObjectAdapter(FStrixNetworkId& val) : ObjectAdapter(std::make_shared<FNetworkObjectIdObject>(val)) {}

} } }