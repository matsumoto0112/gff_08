/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "Serialization/UEObjectsSerializers.h"

#include <strix/client/ingame/rpc/RpcProcedureT.h>
#include <strix/net/util/SuperFastHash.h>

/** Class containing various utility functions for linking Strix specific objects
 *  with Unreal Editor.
 */
class StrixUtil
{
public:

	/** Create the default RPCProcedure object bound to a function
	 *	@param	procedureHash	RPC Procedure hash code
	 *	@param	func	Function to bind to
	 *	@returns	Created RPCProcedure object
	 */
	template <typename ...TFuncArgs>
	static std::shared_ptr<strix::client::ingame::rpc::RpcProcedureT<TFuncArgs...>> MakeRpcProcedure(int procedureHash, std::function<void(TFuncArgs...)> func)
	{
		return std::make_shared<strix::client::ingame::rpc::RpcProcedureT<TFuncArgs...>>(procedureHash, func);
	}

	/** Create the default RPCProcedure object bound to a function
	 *	@param	procedureName	RPC Procedure name (will be used to calculate the hash code)
	 *	@param	func	Function to bind to
	 *	@returns	Created RPCProcedure object
	 */
	template <typename ...TFuncArgs>
	static std::shared_ptr<strix::client::ingame::rpc::RpcProcedureT<TFuncArgs...>> MakeRpcProcedure(const std::string procedureName, std::function<void(TFuncArgs...)> func)
	{
		return MakeRpcProcedure(GetHashValue(procedureName), func);
	}

	/** Calculate the default hash code from string
	 *	@param	source	The string to calculate the hash from
	 *	@returns Calculated hash code
	 */
	static int GetHashValue(const std::string source)
	{
		return strix::net::util::SuperFastHash::Fast(source.c_str());
	}
};