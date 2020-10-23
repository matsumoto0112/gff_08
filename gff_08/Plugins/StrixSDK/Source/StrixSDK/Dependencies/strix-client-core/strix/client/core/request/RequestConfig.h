#pragma once

#include <chrono>
#include <memory>

namespace strix { namespace client { namespace core { namespace request {
	
/**
 *  Configuration information for requests
 */
class RequestConfig {
public:

    /**
     *  Get the timeout of this config
     *  @returns	The timeout in milliseconds
     */
    std::chrono::milliseconds GetTimeout()
    {
	 return m_timeout;
    }

    /**
     *  Set the timeout of this config
     *  @param	timeout	The timeout in milliseconds
     */
    void SetTimeout(const std::chrono::milliseconds &timeout)
    {
	 m_timeout = timeout;
    }

    /**
     *  Construct a config with a default 30 second timeout
     */
    RequestConfig() : m_timeout(30000) {}

private:
  std::chrono::milliseconds m_timeout;
};

typedef std::shared_ptr<RequestConfig> RequestConfigPtr;

} } } }
