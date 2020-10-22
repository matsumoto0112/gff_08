#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace ingame { namespace rpc { namespace message {

/**
 *  Requests a remote procedure call
 *  
 *  Strix message type - Requests sent to the server
 */
class RpcMessage : public strix::net::object::Object
{
public:
	STRIX_CLASS(RpcMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.client.ingame.rpc.message.RpcMessage")
		STRIX_PROPERTY(m_instanceId)
		STRIX_PROPERTY(m_procedureHash)
		STRIX_PROPERTY(m_arguments)
	)

	RpcMessage() {}

	virtual ~RpcMessage() {}

	/**
	 *  Get the ID of the instance to call on
	 *  @returns	The instance ID
	 */
	long long GetInstanceId()
	{
		return m_instanceId;
	}

	/**
	 *  Set the instance ID to call on
	 *  @param	instanceId	The instance ID
	 */
	void SetInstanceId(long long instanceId)
	{
		m_instanceId = instanceId;
	}

	/**
	 *  Get the hash of the registered RPC
	 *  @returns	The hash
	 */
	int GetProcedureHash()
	{
		return m_procedureHash;
	}

	/**
	 *  Set the registered RPC hash
	 *  @param	procedureHash	The hash
	 */
	void SetProcedureHash(int procedureHash)
	{
		m_procedureHash = procedureHash;
	}

	/**
	 *  Get the arguments for the call
	 *  @returns	The argument list
	 */
	strix::net::object::ObjectVector &GetArguments() {
		return m_arguments;
	}

	/**
	 *  Set the arguments for the call
	 *  @param	arguments	The argument list
	 */
	void SetArguments(const strix::net::object::ObjectVector &arguments) {
		m_arguments = arguments;
	}

	long long m_instanceId;
	int m_procedureHash;
	net::object::ObjectVector m_arguments;
};

typedef std::shared_ptr<RpcMessage> RpcMessagePtr;

} } } } }
