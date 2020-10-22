/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Rpc/UERpcProcedureArg.h"

#include <strix/client/ingame/rpc/RpcProcedure.h>

namespace strix { namespace client { namespace ingame { namespace rpc {

/** Strix RPC procedure implementation for use with Unreal Engine.
 *  Uses UFunctions internally.
 */
class UERpcProcedure : public RpcProcedure
{
public:
	UERpcProcedure(UObject* object, FString functionName);

	UERpcProcedure(UObject* object, FString functionName, int procedureHash);

	UERpcProcedure(UObject* object, FString functionName, rpc::permission::RpcPermission rpcPermission);

	UERpcProcedure(UObject* object, FString functionName, int procedureHash, rpc::permission::RpcPermission rpcPermission);

	/** Override of the Call function that converts received Strix objects
	 *  to ones used by Unreal and calls the stored UFunction.
	 *	@param	args	Arguments to call the function with
	 */
	void Call(strix::net::object::ObjectVector args) override;

	/** Getter of the IsValid property
	 *	@returns	The value of the IsValid property
	 */
	bool IsValid()
	{
		return m_isValid;
	}

private:
	/** Internal initialization function that processes the stored UFunction
	 *  and the parameters of it. If this operation was successful the IsValid
	 *  property is set to true.
	 */
	void Init(UObject* object, FString& functionName);

	std::vector<std::shared_ptr<UERpcProcedureArgBase>> m_functionArgs;
	UObject* m_object;
	UFunction* m_function;

	/** Used mostly to check if the argument list was processed successfully
	 */
	bool m_isValid = false;

	int m_contextArgIndex = -1;
};

} } } }