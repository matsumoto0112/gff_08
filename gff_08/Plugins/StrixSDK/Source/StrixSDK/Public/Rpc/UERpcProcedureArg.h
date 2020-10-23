/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreUObject.h"
#include "Serialization/UEObjectsSerializers.h"
#include "Adapter/StrixRpcContext.h"

#include <strix/client/ingame/rpc/RpcContext.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/net/object/Number.h>


namespace strix { namespace client { namespace ingame { namespace rpc {

/** Wrapper class for RPC arguments.
 *  Serves as a bridge between Strix and Unreal types.
 */
class UERpcProcedureArgBase
{
public:
	virtual ~UERpcProcedureArgBase() = default;
	virtual bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) = 0;
};

template <typename T>
class UERpcProcedureArg : public UERpcProcedureArgBase
{
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		return false;
	}
};

template <>
class UERpcProcedureArg <UBoolProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::BooleanObject>())
		{
			std::shared_ptr<strix::net::object::BooleanObject> casted = std::static_pointer_cast<strix::net::object::BooleanObject>(object);

			TPropertyTypeFundamentals<bool>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <UByteProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::ByteObject>())
		{
			std::shared_ptr<strix::net::object::ByteObject> casted = std::static_pointer_cast<strix::net::object::ByteObject>(object);

			TPropertyTypeFundamentals<uint8>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		if(object->InstanceOf<strix::net::object::UByteObject>())
		{
			std::shared_ptr<strix::net::object::UByteObject> casted = std::static_pointer_cast<strix::net::object::UByteObject>(object);

			TPropertyTypeFundamentals<uint8>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <UIntProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntegerObject>())
		{
			std::shared_ptr<strix::net::object::IntegerObject> casted = std::static_pointer_cast<strix::net::object::IntegerObject>(object);

			TPropertyTypeFundamentals<int>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <UFloatProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FloatObject>())
		{
			std::shared_ptr<strix::net::object::FloatObject> casted = std::static_pointer_cast<strix::net::object::FloatObject>(object);

			TPropertyTypeFundamentals<float>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <UStrProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FStringObject>())
		{
			std::shared_ptr<strix::net::object::FStringObject> casted = std::static_pointer_cast<strix::net::object::FStringObject>(object);

			TPropertyTypeFundamentals<FString>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <UTextProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FTextObject>())
		{
			std::shared_ptr<strix::net::object::FTextObject> casted = std::static_pointer_cast<strix::net::object::FTextObject>(object);

			TPropertyTypeFundamentals<FText>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <FVector> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FVectorObject>())
		{
			std::shared_ptr<strix::net::object::FVectorObject> casted = std::static_pointer_cast<strix::net::object::FVectorObject>(object);

			TPropertyTypeFundamentals<FVector>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <FQuat> : public UERpcProcedureArgBase
{
public:
    bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
    {
	if (object->InstanceOf<strix::net::object::FQuatObject>())
	{
	    std::shared_ptr<strix::net::object::FQuatObject> casted = std::static_pointer_cast<strix::net::object::FQuatObject>(object);

	    TPropertyTypeFundamentals<FQuat>::SetPropertyValue(buffer, casted->Get());

	    return true;
	}
	return false;
    }
};

template <>
class UERpcProcedureArg <FRotator> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FRotatorObject>())
		{
			std::shared_ptr<strix::net::object::FRotatorObject> casted = std::static_pointer_cast<strix::net::object::FRotatorObject>(object);

			TPropertyTypeFundamentals<FRotator>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArg <FTransform> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FTransformObject>())
		{
			std::shared_ptr<strix::net::object::FTransformObject> casted = std::static_pointer_cast<strix::net::object::FTransformObject>(object);

			TPropertyTypeFundamentals<FTransform>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template<>
class UERpcProcedureArg <FStrixRpcContext> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if(object->InstanceOf<RpcContext>())
		{
			std::shared_ptr<RpcContext> casted = std::static_pointer_cast<RpcContext>(object);

			FStrixRpcContext context(casted->GetSender()->GetPrimaryKey(), casted->GetSender()->GetRoomId());

			TPropertyTypeFundamentals<FStrixRpcContext>::SetPropertyValue(buffer, context);

			return true;
		}
		return false;
	}
};

template<>
class UERpcProcedureArg<FStrixNetworkId> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<net::object::FNetworkObjectIdObject>())
		{
			std::shared_ptr<net::object::FNetworkObjectIdObject> casted = std::static_pointer_cast<net::object::FNetworkObjectIdObject>(object);

			TPropertyTypeFundamentals<FStrixNetworkId>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <typename T>
class UERpcProcedureArrayArg : public UERpcProcedureArgBase
{
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <UBoolProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::BoolTArrayObject>())
		{
			std::shared_ptr<strix::net::object::BoolTArrayObject> casted = std::static_pointer_cast<strix::net::object::BoolTArrayObject>(object);

			TPropertyTypeFundamentals<TArray<bool>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <UByteProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::ByteTArrayObject>())
		{
			std::shared_ptr<strix::net::object::ByteTArrayObject> casted = std::static_pointer_cast<strix::net::object::ByteTArrayObject>(object);

			TPropertyTypeFundamentals<TArray<uint8>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <UIntProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntTArrayObject>())
		{
			std::shared_ptr<strix::net::object::IntTArrayObject> casted = std::static_pointer_cast<strix::net::object::IntTArrayObject>(object);

			TPropertyTypeFundamentals<TArray<int>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <UFloatProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FloatTArrayObject>())
		{
			std::shared_ptr<strix::net::object::FloatTArrayObject> casted = std::static_pointer_cast<strix::net::object::FloatTArrayObject>(object);

			TPropertyTypeFundamentals<TArray<float>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <UStrProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FStringTArrayObject>())
		{
			std::shared_ptr<strix::net::object::FStringTArrayObject> casted = std::static_pointer_cast<strix::net::object::FStringTArrayObject>(object);

			TPropertyTypeFundamentals<TArray<FString>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <FVector> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FVectorTArrayObject>())
		{
			std::shared_ptr<strix::net::object::FVectorTArrayObject> casted = std::static_pointer_cast<strix::net::object::FVectorTArrayObject>(object);

			TPropertyTypeFundamentals<TArray<FVector>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <FRotator> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FRotatorTArrayObject>())
		{
			std::shared_ptr<strix::net::object::FRotatorTArrayObject> casted = std::static_pointer_cast<strix::net::object::FRotatorTArrayObject>(object);

			TPropertyTypeFundamentals<TArray<FRotator>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureArrayArg <FQuat> : public UERpcProcedureArgBase
{
public:
    bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
    {
	if (object->InstanceOf<strix::net::object::FQuatTArrayObject>())
	{
	    std::shared_ptr<strix::net::object::FQuatTArrayObject> casted = std::static_pointer_cast<strix::net::object::FQuatTArrayObject>(object);

	    TPropertyTypeFundamentals<TArray<FQuat>>::SetPropertyValue(buffer, casted->Get());

	    return true;
	}
	return false;
    }
};

template <>
class UERpcProcedureArrayArg <FTransform> : public UERpcProcedureArgBase
{
public:
    bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
    {
	if (object->InstanceOf<strix::net::object::FTransformTArrayObject>())
	{
	    std::shared_ptr<strix::net::object::FTransformTArrayObject> casted = std::static_pointer_cast<strix::net::object::FTransformTArrayObject>(object);

	    TArray<FTransform> transforms;
	    for(auto transform : casted->Get())
	    {
		transforms.Add(transform.Get());
	    }

	    TPropertyTypeFundamentals<TArray<FTransform>>::SetPropertyValue(buffer, transforms);

	    return true;
	}
	return false;
    }
};

template <>
class UERpcProcedureArrayArg <UTextProperty> : public UERpcProcedureArgBase
{
public:
    bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
    {
	if (object->InstanceOf<strix::net::object::FTextTArrayObject>())
	{
	    std::shared_ptr<strix::net::object::FTextTArrayObject> casted = std::static_pointer_cast<strix::net::object::FTextTArrayObject>(object);

	    TArray<FText> texts;
	    for(auto text : casted->Get())
	    {
		texts.Add(text.Get());
	    }

	    TPropertyTypeFundamentals<TArray<FText>>::SetPropertyValue(buffer, texts);

	    return true;
	}
	return false;
    }
};

template <typename T>
class UERpcProcedureSetArg : public UERpcProcedureArgBase
{
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		return false;
	}
};

template <>
class UERpcProcedureSetArg <UByteProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::ByteTSetObject>())
		{
			std::shared_ptr<strix::net::object::ByteTSetObject> casted = std::static_pointer_cast<strix::net::object::ByteTSetObject>(object);

			TPropertyTypeFundamentals<TSet<uint8>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureSetArg <UIntProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntTSetObject>())
		{
			std::shared_ptr<strix::net::object::IntTSetObject> casted = std::static_pointer_cast<strix::net::object::IntTSetObject>(object);

			TPropertyTypeFundamentals<TSet<int>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureSetArg <UFloatProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FloatTSetObject>())
		{
			std::shared_ptr<strix::net::object::FloatTSetObject> casted = std::static_pointer_cast<strix::net::object::FloatTSetObject>(object);

			TPropertyTypeFundamentals<TSet<float>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureSetArg <UStrProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FStringTSetObject>())
		{
			std::shared_ptr<strix::net::object::FStringTSetObject> casted = std::static_pointer_cast<strix::net::object::FStringTSetObject>(object);

			TPropertyTypeFundamentals<TSet<FString>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureSetArg <FVector> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::FVectorTSetObject>())
		{
			std::shared_ptr<strix::net::object::FVectorTSetObject> casted = std::static_pointer_cast<strix::net::object::FVectorTSetObject>(object);

			TPropertyTypeFundamentals<TSet<FVector>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <typename T, typename R>
class UERpcProcedureMapArg : public UERpcProcedureArgBase
{
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UIntProperty, UBoolProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntKeyBoolTMapObject>())
		{
			std::shared_ptr<strix::net::object::IntKeyBoolTMapObject> casted = std::static_pointer_cast<strix::net::object::IntKeyBoolTMapObject>(object);

			TPropertyTypeFundamentals<TMap<int, bool>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UIntProperty, UByteProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntKeyByteTMapObject>())
		{
			std::shared_ptr<strix::net::object::IntKeyByteTMapObject> casted = std::static_pointer_cast<strix::net::object::IntKeyByteTMapObject>(object);

			TPropertyTypeFundamentals<TMap<int, uint8>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UIntProperty, UIntProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntKeyIntTMapObject>())
		{
			std::shared_ptr<strix::net::object::IntKeyIntTMapObject> casted = std::static_pointer_cast<strix::net::object::IntKeyIntTMapObject>(object);

			TPropertyTypeFundamentals<TMap<int, int>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UIntProperty, UFloatProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntKeyFloatTMapObject>())
		{
			std::shared_ptr<strix::net::object::IntKeyFloatTMapObject> casted = std::static_pointer_cast<strix::net::object::IntKeyFloatTMapObject>(object);

			TPropertyTypeFundamentals<TMap<int, float>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UIntProperty, UStrProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntKeyFStringTMapObject>())
		{
			std::shared_ptr<strix::net::object::IntKeyFStringTMapObject> casted = std::static_pointer_cast<strix::net::object::IntKeyFStringTMapObject>(object);

			TPropertyTypeFundamentals<TMap<int, FString>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UIntProperty, FVector> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntKeyFVectorTMapObject>())
		{
			std::shared_ptr<strix::net::object::IntKeyFVectorTMapObject> casted = std::static_pointer_cast<strix::net::object::IntKeyFVectorTMapObject>(object);

			TPropertyTypeFundamentals<TMap<int, FVector>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UIntProperty, FRotator> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::IntKeyFRotatorTMapObject>())
		{
			std::shared_ptr<strix::net::object::IntKeyFRotatorTMapObject> casted = std::static_pointer_cast<strix::net::object::IntKeyFRotatorTMapObject>(object);

			TPropertyTypeFundamentals<TMap<int, FRotator>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UStrProperty, UBoolProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::StringKeyBoolTMapObject>())
		{
			std::shared_ptr<strix::net::object::StringKeyBoolTMapObject> casted = std::static_pointer_cast<strix::net::object::StringKeyBoolTMapObject>(object);

			TPropertyTypeFundamentals<TMap<FString, bool>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UStrProperty, UByteProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::StringKeyByteTMapObject>())
		{
			std::shared_ptr<strix::net::object::StringKeyByteTMapObject> casted = std::static_pointer_cast<strix::net::object::StringKeyByteTMapObject>(object);

			TPropertyTypeFundamentals<TMap<FString, uint8>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UStrProperty, UIntProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::StringKeyIntTMapObject>())
		{
			std::shared_ptr<strix::net::object::StringKeyIntTMapObject> casted = std::static_pointer_cast<strix::net::object::StringKeyIntTMapObject>(object);

			TPropertyTypeFundamentals<TMap<FString, int>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UStrProperty, UFloatProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::StringKeyFloatTMapObject>())
		{
			std::shared_ptr<strix::net::object::StringKeyFloatTMapObject> casted = std::static_pointer_cast<strix::net::object::StringKeyFloatTMapObject>(object);

			TPropertyTypeFundamentals<TMap<FString, float>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UStrProperty, UStrProperty> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::StringKeyFStringTMapObject>())
		{
			std::shared_ptr<strix::net::object::StringKeyFStringTMapObject> casted = std::static_pointer_cast<strix::net::object::StringKeyFStringTMapObject>(object);

			TPropertyTypeFundamentals<TMap<FString, FString>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UStrProperty, FVector> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::StringKeyFVectorTMapObject>())
		{
			std::shared_ptr<strix::net::object::StringKeyFVectorTMapObject> casted = std::static_pointer_cast<strix::net::object::StringKeyFVectorTMapObject>(object);

			TPropertyTypeFundamentals<TMap<FString, FVector>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

template <>
class UERpcProcedureMapArg <UStrProperty, FRotator> : public UERpcProcedureArgBase
{
public:
	bool TryWriteToByteBuffer(strix::net::object::ObjectPtr object, uint8* buffer) override
	{
		if (object->InstanceOf<strix::net::object::StringKeyFRotatorTMapObject>())
		{
			std::shared_ptr<strix::net::object::StringKeyFRotatorTMapObject> casted = std::static_pointer_cast<strix::net::object::StringKeyFRotatorTMapObject>(object);

			TPropertyTypeFundamentals<TMap<FString, FRotator>>::SetPropertyValue(buffer, casted->Get());

			return true;
		}
		return false;
	}
};

// ToDo: think about properly using template specialization (if possible)
/** Helper class used for creating RPC arguments from Unreal properties.
 */
class UERpcProcedureArgFactory
{
public:
	/** Create RPC argument structure based on the type of an Unreal Property
	 *	@param	property	UProperty to get the type from
	 *	@returns	The created RPC argument of specified type
	 */
	static std::shared_ptr<UERpcProcedureArgBase> ConstructUERpcProcedureArg(UProperty* property)
	{
		if (UBoolProperty *boolProp = Cast<UBoolProperty>(property))
		{
			return std::make_shared<UERpcProcedureArg<UBoolProperty>>();
		}

		if (UByteProperty *byteProp = Cast<UByteProperty>(property))
		{
			return std::make_shared<UERpcProcedureArg<UByteProperty>>();
		}

		if (UIntProperty *intProp = Cast<UIntProperty>(property))
		{
			return std::make_shared<UERpcProcedureArg<UIntProperty>>();
		}

		if (UFloatProperty *floatProp = Cast<UFloatProperty>(property))
		{
			return std::make_shared<UERpcProcedureArg<UFloatProperty>>();
		}

		if (UStrProperty *stringProp = Cast<UStrProperty>(property))
		{
			return std::make_shared<UERpcProcedureArg<UStrProperty>>();
		}

		if (UTextProperty *textProp = Cast<UTextProperty>(property))
		{
			return std::make_shared<UERpcProcedureArg<UTextProperty>>();
		}

		if (UStructProperty *structProp = Cast<UStructProperty>(property))
		{
			if (structProp->Struct == TBaseStructure<FVector>::Get())
			{
				return std::make_shared<UERpcProcedureArg<FVector>>();
			}

			if (structProp->Struct == TBaseStructure<FRotator>::Get())
			{
				return std::make_shared<UERpcProcedureArg<FRotator>>();
			}

			if (structProp->Struct == TBaseStructure<FTransform>::Get())
			{
				return std::make_shared<UERpcProcedureArg<FTransform>>();
			}

			if (structProp->Struct == TBaseStructure<FQuat>::Get())
			{
				return std::make_shared<UERpcProcedureArg<FQuat>>();
			}

			if(structProp->Struct == TBaseStructure<FStrixRpcContext>::Get())
			{
				return std::make_shared<UERpcProcedureArg<FStrixRpcContext>>();
			}

			if (structProp->Struct == TBaseStructure<FStrixNetworkId>::Get())
			{
				return std::make_shared<UERpcProcedureArg<FStrixNetworkId>>();
			}
		}

		return nullptr;
	}

	/** Create RPC array argument structure based on the type of an Unreal Property
	 *	@param	property	UProperty to get the type from
	 *	@returns	The created RPC argument of specified type
	 */
	static std::shared_ptr<UERpcProcedureArgBase> ConstructUERpcProcedureArrayArg(UProperty* property)
	{
		if (UBoolProperty *boolProp = Cast<UBoolProperty>(property))
		{
			return std::make_shared<UERpcProcedureArrayArg<UBoolProperty>>();
		}

		if (UByteProperty *byteProp = Cast<UByteProperty>(property))
		{
			return std::make_shared<UERpcProcedureArrayArg<UByteProperty>>();
		}

		if (UIntProperty *intProp = Cast<UIntProperty>(property))
		{
			return std::make_shared<UERpcProcedureArrayArg<UIntProperty>>();
		}

		if (UFloatProperty *floatProp = Cast<UFloatProperty>(property))
		{
			return std::make_shared<UERpcProcedureArrayArg<UFloatProperty>>();
		}

		if (UStrProperty *stringProp = Cast<UStrProperty>(property))
		{
			return std::make_shared<UERpcProcedureArrayArg<UStrProperty>>();
		}

		if (UTextProperty *textProp = Cast<UTextProperty>(property))
		{
			return std::make_shared<UERpcProcedureArrayArg<UTextProperty>>();
		}

		if (UStructProperty *structProp = Cast<UStructProperty>(property))
		{
			if (structProp->Struct == TBaseStructure<FVector>::Get())
			{
				return std::make_shared<UERpcProcedureArrayArg<FVector>>();
			}

			if (structProp->Struct == TBaseStructure<FRotator>::Get())
			{
				return std::make_shared<UERpcProcedureArrayArg<FRotator>>();
			}

			if (structProp->Struct == TBaseStructure<FQuat>::Get())
			{
				return std::make_shared<UERpcProcedureArrayArg<FQuat>>();
			}

			if (structProp->Struct == TBaseStructure<FTransform>::Get())
			{
				return std::make_shared<UERpcProcedureArrayArg<FTransform>>();
			}
		}

		return nullptr;
	}

	/** Create RPC set argument structure based on the type of an Unreal Property
	 *	@param	property	UProperty to get the type from
	 *	@returns	The created RPC argument of specified type
	 */
	static std::shared_ptr<UERpcProcedureArgBase> ConstructUERpcProcedureSetArg(UProperty* property)
	{
		if (UByteProperty *byteProp = Cast<UByteProperty>(property))
		{
			return std::make_shared<UERpcProcedureSetArg<UByteProperty>>();
		}

		if (UIntProperty *intProp = Cast<UIntProperty>(property))
		{
			return std::make_shared<UERpcProcedureSetArg<UIntProperty>>();
		}

		if (UFloatProperty *floatProp = Cast<UFloatProperty>(property))
		{
			return std::make_shared<UERpcProcedureSetArg<UFloatProperty>>();
		}

		if (UStrProperty *stringProp = Cast<UStrProperty>(property))
		{
			return std::make_shared<UERpcProcedureSetArg<UStrProperty>>();
		}

		if (UStructProperty *structProp = Cast<UStructProperty>(property))
		{
			if (structProp->Struct == TBaseStructure<FVector>::Get())
			{
				return std::make_shared<UERpcProcedureSetArg<FVector>>();
			}

			if (structProp->Struct == TBaseStructure<FQuat>::Get())
			{
				return  std::make_shared<UERpcProcedureSetArg<FQuat>>();
			}
		}

		return nullptr;
	}

	/** Create RPC map argument structure based on the type of the key and value
	 *	@param	keyProperty	UProperty to get the key type from
	 *	@param	keyProperty	UProperty to get the value type from
	 *	@returns	The created RPC argument of specified type
	 */
	static std::shared_ptr<UERpcProcedureArgBase> ConstructUERpcProcedureMapArg(UProperty* keyProperty, UProperty* valueProperty)
	{
		int keyType = 0;
		if (UIntProperty *intProp = Cast<UIntProperty>(keyProperty))
		{
			keyType = 1;
		}
		else if (UStrProperty *stringProp = Cast<UStrProperty>(keyProperty))
		{
			keyType = 2;
		}

		if (keyType == 0)
			return nullptr;

		if (UBoolProperty *boolProp = Cast<UBoolProperty>(valueProperty))
		{
			if (keyType == 1)
				return std::make_shared<UERpcProcedureMapArg<UIntProperty, UBoolProperty>>();
			else
				return std::make_shared<UERpcProcedureMapArg<UStrProperty, UBoolProperty>>();
		}

		if (UByteProperty *byteProp = Cast<UByteProperty>(valueProperty))
		{
			if (keyType == 1)
				return std::make_shared<UERpcProcedureMapArg<UIntProperty, UByteProperty>>();
			else
				return std::make_shared<UERpcProcedureMapArg<UStrProperty, UByteProperty>>();
		}

		if (UIntProperty *intProp = Cast<UIntProperty>(valueProperty))
		{
			if (keyType == 1)
				return std::make_shared<UERpcProcedureMapArg<UIntProperty, UIntProperty>>();
			else
				return std::make_shared<UERpcProcedureMapArg<UStrProperty, UIntProperty>>();
		}

		if (UFloatProperty *floatProp = Cast<UFloatProperty>(valueProperty))
		{
			if (keyType == 1)
				return std::make_shared<UERpcProcedureMapArg<UIntProperty, UFloatProperty>>();
			else
				return std::make_shared<UERpcProcedureMapArg<UStrProperty, UFloatProperty>>();
		}

		if (UStrProperty *stringProp = Cast<UStrProperty>(valueProperty))
		{
			if (keyType == 1)
				return std::make_shared<UERpcProcedureMapArg<UIntProperty, UStrProperty>>();
			else
				return std::make_shared<UERpcProcedureMapArg<UStrProperty, UStrProperty>>();
		}

		if (UStructProperty *structProp = Cast<UStructProperty>(valueProperty))
		{
			if (structProp->Struct == TBaseStructure<FVector>::Get())
			{
				if (keyType == 1)
					return std::make_shared<UERpcProcedureMapArg<UIntProperty, FVector>>();
				else
					return std::make_shared<UERpcProcedureMapArg<UStrProperty, FVector>>();
			}

			if (structProp->Struct == TBaseStructure<FRotator>::Get())
			{
				if (keyType == 1)
					return std::make_shared<UERpcProcedureMapArg<UIntProperty, FRotator>>();
				else
					return std::make_shared<UERpcProcedureMapArg<UStrProperty, FRotator>>();
			}
		}

		return nullptr;
	}
};

} } } }
