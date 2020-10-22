/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Adapter/StrixNetworkId.h"

#include <strix/net/object/ComparableWrapperObject.h>
#include <strix/net/serialization/serializer/SerializerImpl.h>

namespace strix { namespace net { namespace object {

// Type name declarations to avoid RTTI usage
template <>
class TypeNameFactory<FVector>
{
public:
	static std::string GetTypeName(bool)
	{
		return "FVector";
	}
};

template <>
class TypeNameFactory<FRotator>
{
public:
	static std::string GetTypeName(bool)
	{
		return "FRotator";
	}
};

template <>
class TypeNameFactory<FTransform>
{
public:
	static std::string GetTypeName(bool)
	{
		return "FTransform";
	}
};

template <>
class TypeNameFactory<FString>
{
public:
	static std::string GetTypeName(bool)
	{
		return "FString";
	}
};

template <>
class TypeNameFactory<FText>
{
public:
	static std::string GetTypeName(bool)
	{
		return "FText";
	}
};

template <>
class TypeNameFactory<FQuat>
{
public:
	static std::string GetTypeName(bool)
	{
		return "FQuat";
	}
};

template<typename InElementType, typename InAllocator>
class TypeNameFactory<TArray<InElementType, InAllocator>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "TArray<" + TypeNameFactory<InElementType>::GetTypeName(true) + ">";
	}
};

template<typename InElementType, typename KeyFuncs, typename Allocator>
class TypeNameFactory<TSet<InElementType, KeyFuncs, Allocator>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "TSet<" + TypeNameFactory<InElementType>::GetTypeName(true) + ">";
	}
};

template<typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs>
class TypeNameFactory<TMap<KeyType, ValueType, SetAllocator, KeyFuncs>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "TMap<" + TypeNameFactory<KeyType>::GetTypeName(true)
			+ ", " + TypeNameFactory<ValueType>::GetTypeName(true) + ">";
	}
};

// Base UE Classes
const int FVectorClassId =    -30;
const int FRotatorClassId =   -31;
const int FTransformClassId = -32;
const int FStringClassId =    -33;
const int FTextClassId =      -34;
const int FQuatClassId =      -35;

// TArray Classes
const int BoolTArrayClassId =       -40;
const int ByteTArrayClassId =       -41;
const int IntTArrayClassId =        -42;
const int FloatTArrayClassId =      -43;
const int FVectorTArrayClassId =    -44;
const int FRotatorTArrayClassId =   -45;
const int ObjectTArrayClassId =     -46;
const int FStringTArrayClassId =    -47;
const int FQuatTArrayClassId =      -48;
const int FTransformTArrayClassId = -49;

// TSet Classes
const int ByteTSetClassId =     -50;
const int IntTSetClassId =      -51;
const int FloatTSetClassId =    -52;
const int FVectorTSetClassId =  -53;
const int FStringTSetClassId =  -54;

// Integer key TMap Classes
const int IntKeyBoolTMapClassId =     -60;
const int IntKeyByteTMapClassId =     -61;
const int IntKeyIntTMapClassId =      -62;
const int IntKeyFloatTMapClassId =    -63;
const int IntKeyFVectorTMapClassId =  -64;
const int IntKeyFRotatorTMapClassId = -65;
const int IntKeyObjectTMapClassId =   -66;
const int IntKeyFStringTMapClassId =  -67;

// String key TMap Classes
const int StringKeyBoolTMapClassId =     -70;
const int StringKeyByteTMapClassId =     -71;
const int StringKeyIntTMapClassId =      -72;
const int StringKeyFloatTMapClassId =    -73;
const int StringKeyFVectorTMapClassId =  -74;
const int StringKeyFRotatorTMapClassId = -75;
const int StringKeyObjectTMapClassId =   -76;
const int StringKeyFStringTMapClassId =  -77;

// TArray Classes (second)
const int FTextTArrayClassId = -80;

// FStrix structs
const int FNetworkObjectIdClassId = -90;

typedef ComparableWrapperObjectImpl<FVector,    FVectorClassId>    FVectorObject;
typedef ComparableWrapperObjectImpl<FRotator,   FRotatorClassId>   FRotatorObject;
typedef ComparableWrapperObjectImpl<FString,    FStringClassId>    FStringObject;

typedef ComparableWrapperObjectImpl<TArray<bool>,                          BoolTArrayClassId>       BoolTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<uint8>,                         ByteTArrayClassId>       ByteTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<int>,                           IntTArrayClassId>        IntTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<float>,                         FloatTArrayClassId>      FloatTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<FVector>,                       FVectorTArrayClassId>    FVectorTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<FRotator>,                      FRotatorTArrayClassId>   FRotatorTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<FQuat>,                         FQuatTArrayClassId>      FQuatTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<strix::net::object::ObjectPtr>, ObjectTArrayClassId>     ObjectTArrayObject;
typedef ComparableWrapperObjectImpl<TArray<FString>,                       FStringTArrayClassId>    FStringTArrayObject;

typedef ComparableWrapperObjectImpl<TSet<uint8>,                         ByteTSetClassId>     ByteTSetObject;
typedef ComparableWrapperObjectImpl<TSet<int>,                           IntTSetClassId>      IntTSetObject;
typedef ComparableWrapperObjectImpl<TSet<float>,                         FloatTSetClassId>    FloatTSetObject;
typedef ComparableWrapperObjectImpl<TSet<FVector>,                       FVectorTSetClassId>  FVectorTSetObject;
typedef ComparableWrapperObjectImpl<TSet<FString>,                       FStringTSetClassId>  FStringTSetObject;

typedef ComparableWrapperObjectImpl<TMap<int, bool>,                          IntKeyBoolTMapClassId>     IntKeyBoolTMapObject;
typedef ComparableWrapperObjectImpl<TMap<int, uint8>,                         IntKeyByteTMapClassId>     IntKeyByteTMapObject;
typedef ComparableWrapperObjectImpl<TMap<int, int>,                           IntKeyIntTMapClassId>      IntKeyIntTMapObject;
typedef ComparableWrapperObjectImpl<TMap<int, float>,                         IntKeyFloatTMapClassId>    IntKeyFloatTMapObject;
typedef ComparableWrapperObjectImpl<TMap<int, FVector>,                       IntKeyFVectorTMapClassId>  IntKeyFVectorTMapObject;
typedef ComparableWrapperObjectImpl<TMap<int, FRotator>,                      IntKeyFRotatorTMapClassId> IntKeyFRotatorTMapObject;
typedef ComparableWrapperObjectImpl<TMap<int, strix::net::object::ObjectPtr>, IntKeyObjectTMapClassId>   IntKeyObjectTMapObject;
typedef ComparableWrapperObjectImpl<TMap<int, FString>,                       IntKeyFStringTMapClassId>  IntKeyFStringTMapObject;

typedef ComparableWrapperObjectImpl<TMap<FString, bool>,                          StringKeyBoolTMapClassId>     StringKeyBoolTMapObject;
typedef ComparableWrapperObjectImpl<TMap<FString, uint8>,                         StringKeyByteTMapClassId>     StringKeyByteTMapObject;
typedef ComparableWrapperObjectImpl<TMap<FString, int>,                           StringKeyIntTMapClassId>      StringKeyIntTMapObject;
typedef ComparableWrapperObjectImpl<TMap<FString, float>,                         StringKeyFloatTMapClassId>    StringKeyFloatTMapObject;
typedef ComparableWrapperObjectImpl<TMap<FString, FVector>,                       StringKeyFVectorTMapClassId>  StringKeyFVectorTMapObject;
typedef ComparableWrapperObjectImpl<TMap<FString, FRotator>,                      StringKeyFRotatorTMapClassId> StringKeyFRotatorTMapObject;
typedef ComparableWrapperObjectImpl<TMap<FString, strix::net::object::ObjectPtr>, StringKeyObjectTMapClassId>   StringKeyObjectTMapObject;
typedef ComparableWrapperObjectImpl<TMap<FString, FString>,                       StringKeyFStringTMapClassId>  StringKeyFStringTMapObject;

typedef ComparableWrapperObjectImpl<FStrixNetworkId, FNetworkObjectIdClassId> FNetworkObjectIdObject;

/* Custom FTransformObject implementation
* FTransform and FQuat use extended alignment (e.g. __declspec(align(n))), so they 
* cannot be used with make_shared without causing incompatibility between VS versions. 
* Instead, we can unwrap those values for serialization
 */
class FTransformObject : public strix::net::object::StructWrapperObjectT<FTransform>
{
public:
	STRIX_CLASS(FTransformObject, strix::net::object::StructWrapperObjectT<FTransform>)
	(
		STRIX_CLASS_ID(FTransformClassId)
		STRIX_PROPERTY(m_rotW)
		STRIX_PROPERTY(m_rotX)
		STRIX_PROPERTY(m_rotY)
		STRIX_PROPERTY(m_rotZ)
		STRIX_PROPERTY(m_translation)
		STRIX_PROPERTY(m_scale)
	)

	FTransformObject() = default;

	FTransformObject(const FTransform &other)
	{
		FQuat rotation = other.GetRotation();
		m_rotW = rotation.W;
		m_rotX = rotation.X;
		m_rotY = rotation.Y;
		m_rotZ = rotation.Z;
		m_scale = other.GetScale3D();
		m_translation = other.GetTranslation();
	}

	FTransform Get() const override
	{
		return FTransform(
			FQuat(m_rotX, m_rotY, m_rotZ, m_rotW), 
			m_translation, 
			m_scale
		);
	}

protected:
	float m_rotW;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
	FVector m_scale;
	FVector m_translation;
};

typedef ComparableWrapperObjectImpl<TArray<FTransformObject>, FTransformTArrayClassId> FTransformTArrayObject;

class FQuatObject : public strix::net::object::StructWrapperObjectT<FQuat>
{
public:
	STRIX_CLASS(FQuatObject, strix::net::object::StructWrapperObjectT<FQuat>)
	(
		STRIX_CLASS_ID(FQuatClassId)
		STRIX_PROPERTY(m_rotW)
		STRIX_PROPERTY(m_rotX)
		STRIX_PROPERTY(m_rotY)
		STRIX_PROPERTY(m_rotZ)
	)

	FQuatObject() = default;

	FQuatObject(const FQuat &other)
	{
		m_rotW = other.W;
		m_rotX = other.X;
		m_rotY = other.Y;
		m_rotZ = other.Z;
	}

	FQuat Get() const override
	{
		return FQuat(m_rotX, m_rotY, m_rotZ, m_rotW);
	}

protected:
	float m_rotW;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
};

/**
 *  FText is not comparable, so we have to define a separate wrapper object for it
 */
class FTextObject : public strix::net::object::StructWrapperObjectT<FText>
{
public:
    STRIX_CLASS(FTextObject, strix::net::object::StructWrapperObjectT<FText>)
    (
	STRIX_CLASS_ID(FTextClassId)
	STRIX_PROPERTY(m_text)
    )

    FTextObject() = default;

    FTextObject(const FText &other)
    {
	m_text = other;
    }

    FText Get() const override
    {
	return m_text;
    }

protected:
    FText m_text;
};

typedef ComparableWrapperObjectImpl<TArray<FTextObject>, FTextTArrayClassId>      FTextTArrayObject;

} } }

template<>
class strix::net::serialization::serializer::SerializerImpl<FStrixNetworkId, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const FStrixNetworkId &value)
	{
		bool res = encoder.WriteLongLong(value.m_networkObjectId);
		return res;
	}

	bool Deserialize(io::Decoder &decoder, FStrixNetworkId &value) {
		int64 id = -1;
		bool res = decoder.ReadLongLong(id);
		std::stringstream ss;
		ss << id;
		value.m_networkObjectId = id;
		value.StringId = FString(UTF8_TO_TCHAR(ss.str().c_str()));
		return res;
	}
};

template<>
class strix::net::serialization::serializer::SerializerImpl<FVector, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const FVector &value)
	{
		bool res = encoder.WriteFloat(value.X);
		res &= encoder.WriteFloat(value.Y);
		res &= encoder.WriteFloat(value.Z);

		return res;
	}

	bool Deserialize(io::Decoder &decoder, FVector &value) {
		bool res = decoder.ReadFloat(value.X);
		res &= decoder.ReadFloat(value.Y);
		res &= decoder.ReadFloat(value.Z);

		return res;
	}
};

template<>
class strix::net::serialization::serializer::SerializerImpl<FRotator, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const FRotator &value)
	{
		bool res = encoder.WriteFloat(value.Pitch);
		res &= encoder.WriteFloat(value.Yaw);
		res &= encoder.WriteFloat(value.Roll);

		return res;
	}

	bool Deserialize(io::Decoder &decoder, FRotator &value) {
		bool res = decoder.ReadFloat(value.Pitch);
		res &= decoder.ReadFloat(value.Yaw);
		res &= decoder.ReadFloat(value.Roll);

		return res;
	}
};

template<>
class strix::net::serialization::serializer::SerializerImpl<FTransform, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const FTransform &value)
	{
		bool res = encoder.WriteFloat(value.GetRotation().W);
		res &= encoder.WriteFloat(value.GetRotation().X);
		res &= encoder.WriteFloat(value.GetRotation().Y);
		res &= encoder.WriteFloat(value.GetRotation().Z);
		res &= encoder.WriteFloat(value.GetScale3D().X);
		res &= encoder.WriteFloat(value.GetScale3D().Y);
		res &= encoder.WriteFloat(value.GetScale3D().Z);
		res &= encoder.WriteFloat(value.GetTranslation().X);
		res &= encoder.WriteFloat(value.GetTranslation().Y);
		res &= encoder.WriteFloat(value.GetTranslation().Z);

		return res;
	}

	bool Deserialize(io::Decoder &decoder, FTransform &value) {
		FQuat rotation;
		FVector scale3D;
		FVector translation;

		bool res = decoder.ReadFloat(rotation.W);
		res &= decoder.ReadFloat(rotation.X);
		res &= decoder.ReadFloat(rotation.Y);
		res &= decoder.ReadFloat(rotation.Z);
		res &= decoder.ReadFloat(scale3D.X);
		res &= decoder.ReadFloat(scale3D.Y);
		res &= decoder.ReadFloat(scale3D.Z);
		res &= decoder.ReadFloat(translation.X);
		res &= decoder.ReadFloat(translation.Y);
		res &= decoder.ReadFloat(translation.Z);

		value.SetRotation(rotation);
		value.SetScale3D(scale3D);
		value.SetTranslation(translation);

		return res;
	}
};

template<>
class strix::net::serialization::serializer::SerializerImpl<FString, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const FString &value)
	{
		return encoder.WriteString(TCHAR_TO_UTF8(*value));
	}

	bool Deserialize(io::Decoder &decoder, FString &value) {
		std::string temp;
		bool res = decoder.ReadString(temp);
		
		value = UTF8_TO_TCHAR(temp.c_str());

		return res;
	}
};

template<>
class strix::net::serialization::serializer::SerializerImpl<FText, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const FText &value)
	{
		return encoder.WriteString(TCHAR_TO_UTF8(*(value.ToString())));
	}

	bool Deserialize(io::Decoder &decoder, FText &value) {
		std::string temp;
		bool res = decoder.ReadString(temp);

		value = FText::FromString(UTF8_TO_TCHAR(temp.c_str()));

		return res;
	}
};

template<>
class strix::net::serialization::serializer::SerializerImpl<FQuat, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const FQuat &value)
	{
		bool res = encoder.WriteFloat(value.W);
		res &= encoder.WriteFloat(value.X);
		res &= encoder.WriteFloat(value.Y);
		res &= encoder.WriteFloat(value.Z);

		return res;
	}

	bool Deserialize(io::Decoder &decoder, FQuat &value) {
		bool res = decoder.ReadFloat(value.W);
		res &= decoder.ReadFloat(value.X);
		res &= decoder.ReadFloat(value.Y);
		res &= decoder.ReadFloat(value.Z);

		return res;
	}
};

template <typename T, typename InAllocator>
class strix::net::serialization::serializer::SerializerImpl<TArray<T, InAllocator>, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const TArray<T, InAllocator> &value) {
		int32 size = value.Num();

		if (!encoder.WriteArrayBegin(size))
			return false;

		for (size_t i = 0; i < size; ++i)
		{
			if (!encoder.WriteArrayItemBegin(i))
				return false;

			if (!SerializerImpl<T>().Serialize(encoder, value[i]))
				return false;

			if (!encoder.WriteArrayItemEnd(i))
				return false;
		}

		if (!encoder.WriteArrayEnd())
			return false;

		return true;
	}
	bool Deserialize(strix::net::io::Decoder &decoder, TArray<T, InAllocator> &value) {
		int len;
		if (!decoder.ReadArrayBegin(len))
			return false;

		value.Reserve(len);

		for (int i = 0; i<len; i++)
		{
			T v;
			if (!SerializerImpl<T>().Deserialize(decoder, v))
				return false;
			value.Add(v);
		}

		if (!decoder.ReadArrayEnd())
			return false;

		return true;
	}
};

template <typename T, typename KeyFuncs, typename Allocator>
class strix::net::serialization::serializer::SerializerImpl<TSet<T, KeyFuncs, Allocator>, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const TSet<T, KeyFuncs, Allocator> &value) {
		int32 size = value.Num();

		if (!encoder.WriteArrayBegin(size))
			return false;

		int index = 0;
		for (T element : value)
		{
			if (!encoder.WriteArrayItemBegin(index))
				return false;

			if (!SerializerImpl<T>().Serialize(encoder, element))
				return false;

			if (!encoder.WriteArrayItemEnd(index))
				return false;
			
			++index;
		}

		if (!encoder.WriteArrayEnd())
			return false;

		return true;
	}
	bool Deserialize(strix::net::io::Decoder &decoder, TSet<T, KeyFuncs, Allocator> &value) {
		int len;
		if (!decoder.ReadArrayBegin(len))
			return false;

		value.Reserve(len);

		for (int i = 0; i<len; i++)
		{
			T v;
			if (!SerializerImpl<T>().Deserialize(decoder, v))
				return false;
			value.Add(v);
		}

		if (!decoder.ReadArrayEnd())
			return false;

		return true;
	}
};

template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs>
class strix::net::serialization::serializer::SerializerImpl<TMap<KeyType, ValueType, SetAllocator, KeyFuncs>, false>
{
public:
	bool Serialize(strix::net::io::Encoder &encoder, const TMap<KeyType, ValueType, SetAllocator, KeyFuncs> &value) {
		int32 size = value.Num();

		if (!encoder.WriteMapBegin(size))
			return false;

		int index = 0;
		for (const auto& entry : value)
		{
			if (!encoder.WriteMapKeyBegin(index))
				return false;

			if (!SerializerImpl<KeyType>().Serialize(encoder, entry.Key))
				return false;

			if (!encoder.WriteMapKeyEnd(index))
				return false;

			if (!encoder.WriteMapValueBegin(index))
				return false;

			if (!SerializerImpl<ValueType>().Serialize(encoder, entry.Value))
				return false;

			if (!encoder.WriteMapValueEnd(index))
				return false;

			++index;
		}

		if (!encoder.WriteMapEnd())
			return false;

		return true;
	}
	bool Deserialize(strix::net::io::Decoder &decoder, TMap<KeyType, ValueType, SetAllocator, KeyFuncs> &value) {
		int len;
		if (!decoder.ReadMapBegin(len))
			return false;

		value.Reserve(len);

		for (int index = 0; index < len; ++index)
		{
			KeyType k;
			ValueType v;
			
			if (!decoder.ReadMapKeyBegin(index))
				return false;

			if (!SerializerImpl<KeyType>().Deserialize(decoder, k))
				return false;

			if (!decoder.ReadMapKeyEnd(index))
				return false;

			if (!decoder.ReadMapValueBegin(index))
				return false;

			if (!SerializerImpl<ValueType>().Deserialize(decoder, v))
				return false;

			if (!decoder.ReadMapValueEnd(index))
				return false;

			value.Add(k, v);
		}

		if (!decoder.ReadMapEnd())
			return false;

		return true;
	}
};

/** Collection of necessary classes/wrappers for Unreal specific objects.
 *  Used for sending Relay messages (for example RPCs.).
 *  
 *  Currently the deserialization of those is NOT supported on the server side.
 */
class UEObjectsSerializers
{
public:
	static void Init()
	{
		strix::net::object::MetaClassT<strix::net::object::FTransformObject>::Get();
		strix::net::object::MetaClassT<strix::net::object::FQuatObject>::Get();
	}
};
