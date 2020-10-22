#pragma once

#include <string>

namespace strix { namespace net { namespace channel {

class SocketChannelConfig
{
public:
	SocketChannelConfig()
		: m_host("127.0.0.1"),
		  m_port(9123),
		  m_timeout(5000),
		  m_readBufferExtendSize(65536),
		  m_maxReadBufferSize(SIZE_MAX),
		  m_maxWriteBufferSize(SIZE_MAX)
	{
	}

	virtual ~SocketChannelConfig() {}

    const std::string &GetHost() const {
        return m_host;
    }

    SocketChannelConfig &SetHost(const std::string &host) {
        m_host = host;
		return *this;
    }

    int GetPortNumber() const {
        return m_port;
    }

    SocketChannelConfig &SetPortNumber(int port) {
        m_port = port;
		return *this;
    }

    int GetTimeout() const {
        return m_timeout;
    }

    SocketChannelConfig &SetTimeout(int timeout) {
        m_timeout = timeout;
		return *this;
    }

	/**
	 * ソケットからデータを受信する際に確保するバッファサイズを取得します
	 * @return 確保するバッファサイズ
	 */
	size_t GetReadBufferExtendSize() const {
		return m_readBufferExtendSize;
	}
	
	/**
	 * ソケットからデータを受信する際に確保するバッファサイズを指定します
	 * 
	 * @param readBufferExtendSize 確保するバッファサイズ
	 * @return SocketChannelConfig このSocketChannelConfigの参照
	 */
	SocketChannelConfig &SetReadBufferExtendSize(size_t readBufferExtendSize) {
		m_readBufferExtendSize = readBufferExtendSize;
		return *this;
	}

	size_t GetMaxReadBufferSize() const {
		return m_maxReadBufferSize;
	}

	SocketChannelConfig &SetMaxReadBufferSize(size_t maxReadBufferSize) {
		m_maxReadBufferSize = maxReadBufferSize;
		return *this;
	}

	size_t GetMaxWriteBufferSize() const {
		return m_maxWriteBufferSize;
	}

	SocketChannelConfig &SetMaxWriteBufferSize(size_t maxWriteBufferSize) {
		m_maxWriteBufferSize = maxWriteBufferSize;
		return *this;
	}

private:
	std::string m_host;
    int m_port;
    int m_timeout;
	size_t m_readBufferExtendSize;
	size_t m_maxReadBufferSize;
	size_t m_maxWriteBufferSize;
};

} } }

