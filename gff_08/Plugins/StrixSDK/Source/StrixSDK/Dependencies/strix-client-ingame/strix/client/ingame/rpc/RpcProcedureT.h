#pragma once

#include <strix/client/ingame/rpc/RpcProcedure.h>
#include <strix/client/core/util/ObjectConverter.h>	

#include <strix/net/object/Number.h>
#include <strix/net/logging/Logger.h>

#include <functional>

namespace strix { namespace client { namespace ingame { namespace rpc {

template <typename ...TFuncArgs>
class RpcProcedureT : public RpcProcedure 
{

STRIX_NET_LOGGER("strix.client.ingame.rpc");

public:
	RpcProcedureT(int procedureHash, std::function<void(TFuncArgs...)> function) : RpcProcedure(procedureHash), m_function(function), m_argsConversionResult(true) {}

	RpcProcedureT(int procedureHash, rpc::permission::RpcPermission rpcPermission, std::function<void(TFuncArgs...)> function) : RpcProcedure(procedureHash, rpcPermission), m_function(function), m_argsConversionResult(true) {}

	virtual ~RpcProcedureT() {}

	/**
	 *  Call the procedure with arguments
	 *  @param	args	The arguments for the procedure
	 */
	void Call(strix::net::object::ObjectVector args) override
	{
		if (m_function)
		{
			CallT(m_function, args);
		}
	}

private:
	template <typename T>
	T Cast(strix::net::object::ObjectPtr element)
	{
		T value;
		if (!core::util::ObjectConverter::TryConvertObjectToValue(element, value))
		{
			m_argsConversionResult = false;
		}

		return value;
	}

	template <typename ...TArgs, std::size_t... I>
	auto CallTImpl(std::function<void(TArgs...)> func, strix::net::object::ObjectVector args, std::index_sequence<I...>)
	{
		std::tuple<TArgs...> tuple = std::make_tuple(Cast<typename std::tuple_element<I, std::tuple<TArgs...>>::type>(args.Get()[I])...);
		
		if (m_argsConversionResult)
		{
			func(std::get<I>(tuple)...);
		}
		else
		{
			m_argsConversionResult = true;
			STRIX_NET_LOG_WARNING("Received argument types do not match the argument list of the stored function");
		}
	}

	template <typename TArray, typename ...TArgs>
	auto CallT(std::function<void(TArgs...)> func, TArray arr)
	{
		if (arr.Get().size() < sizeof...(TArgs))
		{
			STRIX_NET_LOG_WARNING("Too few arguments for the function call");
			return;
		}

		CallTImpl(func, arr, std::index_sequence_for<TArgs...>());
	}

	std::function<void(TFuncArgs...)> m_function;
	bool m_argsConversionResult;
};

} } } }
