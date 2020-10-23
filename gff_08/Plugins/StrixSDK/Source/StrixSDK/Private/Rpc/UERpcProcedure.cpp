/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Rpc/UERpcProcedure.h"

#include "UObject/Object.h"
#include "UObject/UnrealType.h"

#include <strix/net/util/SuperFastHash.h>

namespace strix { namespace client { namespace ingame { namespace rpc {

UERpcProcedure::UERpcProcedure(UObject* object, FString functionName) : RpcProcedure(strix::net::util::SuperFastHash::Fast(TCHAR_TO_UTF8(*functionName)))
{
	Init(object, functionName);
}

UERpcProcedure::UERpcProcedure(UObject* object, FString functionName, int procedureHash) : RpcProcedure(procedureHash)
{
	Init(object, functionName);
}

UERpcProcedure::UERpcProcedure(UObject* object, FString functionName, rpc::permission::RpcPermission rpcPermission) : RpcProcedure(strix::net::util::SuperFastHash::Fast(TCHAR_TO_UTF8(*functionName)), rpcPermission)
{
	Init(object, functionName);
}

UERpcProcedure::UERpcProcedure(UObject* object, FString functionName, int procedureHash, rpc::permission::RpcPermission rpcPermission) : RpcProcedure(procedureHash, rpcPermission)
{
	Init(object, functionName);
}

void UERpcProcedure::Call(strix::net::object::ObjectVector args)
{
	if (m_object && m_function)
	{
		int argsSize = args.Get().size();
		if (argsSize != m_functionArgs.size())
		{
			UE_LOG(LogTemp, Warning, TEXT("UERpcProcedure::Call - Registered RPC args differ from the received ones"));
			return;
		}

		// Move the context argument to the correct position.
		if(m_contextArgIndex != -1)
		{
			args.Get().insert(args.Get().begin() + m_contextArgIndex, args.Get().back());
			args.Get().pop_back();
		}

		// ToDo: check for memory leaks, especially on failed calls
		uint8* buffer = (uint8*)FMemory_Alloca(m_function->ParmsSize);
		uint8* savedCode = NULL;
		FMemory::Memzero(buffer, m_function->ParmsSize);

		int i = 0;
		for (TFieldIterator<UProperty> propertyIt(m_function); propertyIt && (propertyIt->PropertyFlags & (CPF_Parm | CPF_ReturnParm )) == CPF_Parm; ++propertyIt)
		{
			UProperty* property = *propertyIt;

			// ToDo: for some reason arrays are always marked with the OutParm flag, look for a better way to check those
			UArrayProperty* arrayProp = Cast<UArrayProperty>(property);
			if (!arrayProp)
			{
				if (property->PropertyFlags & CPF_OutParm)
					continue;
			}

			uint8* currentPropAddr = propertyIt->ContainerPtrToValuePtr<uint8>(buffer);

			if (!m_functionArgs[i]->TryWriteToByteBuffer(args.Get()[i], currentPropAddr))
			{
				UE_LOG(LogTemp, Warning, TEXT("UERpcProcedure::Call - Registered RPC args differ from the received ones"));
				return;
			}

			++i;
		}

		m_object->ProcessEvent(m_function, buffer);
	}
}

void UERpcProcedure::Init(UObject * object, FString& functionName)
{
	FName const name(*functionName);

	if (object)
	{
		UFunction* const function = object->FindFunction(name);

		if (function)
		{
			m_object = object;
			m_function = function;
			int argIndex = -1;

			for (TFieldIterator<UProperty> propertyIt(m_function); propertyIt && (propertyIt->PropertyFlags & (CPF_Parm | CPF_ReturnParm)) == CPF_Parm; ++propertyIt)
			{
				argIndex++;
				UProperty* rpcProperty = *propertyIt;

				std::shared_ptr<UERpcProcedureArgBase> functionProp = nullptr;

				if (UArrayProperty* arrayProp = Cast<UArrayProperty>(rpcProperty))
				{
					functionProp = UERpcProcedureArgFactory::ConstructUERpcProcedureArrayArg(arrayProp->Inner);
				}
				else
				{
					// ToDo: for some reason arrays are always marked with the OutParm flag, look for a better way to check those
					if (rpcProperty->PropertyFlags & CPF_OutParm)
						continue;

					if (USetProperty* setProp = Cast<USetProperty>(rpcProperty))
					{
						functionProp = UERpcProcedureArgFactory::ConstructUERpcProcedureSetArg(setProp->ElementProp);
					}
					else if (UMapProperty* mapProp = Cast<UMapProperty>(rpcProperty))
					{
						functionProp = UERpcProcedureArgFactory::ConstructUERpcProcedureMapArg(mapProp->KeyProp, mapProp->ValueProp);
					}
					else
					{
						functionProp = UERpcProcedureArgFactory::ConstructUERpcProcedureArg(rpcProperty);
					}

					// Set context available if a strix rpc context is found.
					if (rpcProperty->GetFName().Compare(TEXT("context")) == 0)
					{
						if (UStructProperty *structProp = Cast<UStructProperty>(rpcProperty))
						{
							if (structProp->Struct == TBaseStructure<FStrixRpcContext>::Get())
							{
								m_isContextRequired = true;
								m_contextArgIndex = argIndex;
							}
						}
					}
				}

				if (functionProp)
				{
					m_functionArgs.push_back(std::move(functionProp));
					continue;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("UERpcProcedure::Init - Property type not supported %s"), *(rpcProperty->GetName()));
					return;
				}
			}

			m_isValid = true;
		}
	}
}

} } } }
