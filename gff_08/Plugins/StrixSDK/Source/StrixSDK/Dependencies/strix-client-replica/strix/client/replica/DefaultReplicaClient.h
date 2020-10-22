#pragma once

#include <strix/client/replica/ReplicaClient.h>
#include <strix/client/replica/model/Replica.h>

namespace strix { namespace client { namespace replica {

/**
 *  Default implementation of replica client
 */
class DefaultReplicaClient : public ReplicaClient
{
public:
	DefaultReplicaClient() : ReplicaClient(replica::model::Replica::s_GetMetaClass())
	{
	}

	virtual ~DefaultReplicaClient() = default;
};

typedef std::shared_ptr<DefaultReplicaClient> DefaultReplicaClientPtr;

} } }
