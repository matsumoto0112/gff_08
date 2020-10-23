#pragma once

namespace strix { namespace net { namespace ssl {

class SSLEngineResult
{
public:
	enum class Status
	{
		OK,
		Closed,
	};

	enum class HandshakeStatus
	{
		NotHandshaking,
		Finished,
		NeedWrap,
		NeedUnwrap,
	};

	SSLEngineResult()
		: m_status(SSLEngineResult::Status::Closed),
		  m_handshakeStatus(SSLEngineResult::HandshakeStatus::NotHandshaking),
		  m_bytesConsumed(0),
		  m_bytesProduced(0)
	{
	}

	SSLEngineResult(Status status, HandshakeStatus handshakeStatus, int bytesConsumed, int bytesProduced)
		: m_status(status),
		  m_handshakeStatus(handshakeStatus),
		  m_bytesConsumed(bytesConsumed),
		  m_bytesProduced(bytesProduced)
	{
	}

	Status GetStatus() const {
		return m_status;
	}

	HandshakeStatus GetHandshakeStatus() const {
		return m_handshakeStatus;
	}

	int BytesConsumed() const {
		return m_bytesConsumed;
	}

	int BytesProduced() const {
		return m_bytesProduced;
	}

private:
	Status m_status;
	HandshakeStatus m_handshakeStatus;
	int m_bytesConsumed;
	int m_bytesProduced;
};

} } }
