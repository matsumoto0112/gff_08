#pragma once

#include <strix/net/object/WrapperObject.h>
#include <strix/client/ingame/rpc/permission/RpcPermission.h>

namespace strix { namespace client { namespace ingame { namespace rpc {
	
/**
 *  Model of a Remote Procedure Call 
 */
class RpcProcedure {
public:
	RpcProcedure(int procedureHash) : m_procedureHash(procedureHash), m_isContextRequired(false), m_rpcPermission(rpc::permission::RpcPermission::AllowAll) {}

	RpcProcedure(int procedureHash, rpc::permission::RpcPermission rpcPermission) : m_procedureHash(procedureHash), m_isContextRequired(false), m_rpcPermission(rpcPermission) {}

	virtual ~RpcProcedure() {}

	/**
	 *  Get the procedure hash
	 *  @returns	The hash
	 */
	int GetProcedureHash()
	{
		return m_procedureHash;
	}

	/**
	 *  Get if the RPC needs contextual information (e.g, it's sender) when calling
	 *  @returns	True if context required
	 */
	virtual bool GetIsContextRequired()
	{
		return m_isContextRequired;
	}

	/**
	 *  Get who can send or invoke this RPC
	 *  @returns	The permission value
	 */
	rpc::permission::RpcPermission GetRpcPermission()
	{
		return m_rpcPermission;
	}

	/**
	 *  Set who can send or invoke this RPC
	 *  @param	permission	The permission value
	 */
	void SetRpcPermission(rpc::permission::RpcPermission permission)
	{
		m_rpcPermission = permission;
	}

	/**
	 *  Call the procedure with arguments
	 *  @param	args	The arguments for the procedure
	 */
	virtual void Call(strix::net::object::ObjectVector args) = 0;

protected:
	int m_procedureHash;
	bool m_isContextRequired;
	rpc::permission::RpcPermission m_rpcPermission;
};

typedef std::shared_ptr<RpcProcedure> RpcProcedurePtr;

} } } }
