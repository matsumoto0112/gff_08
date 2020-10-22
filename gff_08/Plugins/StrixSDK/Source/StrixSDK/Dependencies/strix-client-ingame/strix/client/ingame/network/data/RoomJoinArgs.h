#pragma once

#include <strix/client/ingame/network/data/RoomMemberProperties.h>

#include <memory>
#include <string>

namespace strix { namespace net { namespace channel {
enum class Protocol;
}}}

namespace strix { namespace client { namespace ingame { namespace network { namespace data {

/**
 *  Container for room join arguments
 */
class RoomJoinArgs
{
public:
	RoomJoinArgs()
		: m_portNumber(0), m_protocol(), m_roomId(0), m_memberProperties(std::make_shared<RoomMemberProperties>()) {}

	RoomJoinArgs(RoomMemberPropertiesPtr roomMemberProperties)
		: m_portNumber(0), m_protocol(), m_roomId(0), m_memberProperties(std::move(roomMemberProperties)) {}

	/**
	 *  Get the host name
	 *  @returns	The host name
	 */
	const std::string &GetHost() const { return m_host; }

	/**
	 *  Set the host name
	 *  @param	host	The host name
	 */
	void SetHost(std::string host) { m_host = std::move(host); }

	/**
	 *  Get the port number
	 *  @returns	The port number
	 */
	int GetPortNumber() const { return m_portNumber; }

	/**
	 *  Set the port number
	 *  @param	port	The port number
	 */
	void SetPortNumber(int port) { m_portNumber = port; }

	/**
	 *  Get the protocol type
	 *  @returns	The protocol
	 */
	net::channel::Protocol GetProtocol() const { return m_protocol; }

	/**
	 *  Set the protocol type
	 *  @param	protocol	The protocol
	 */
	void SetProtocol(net::channel::Protocol protocol) { m_protocol = protocol; }

	/**
	 *  Get the room id 
	 *  @returns	The room id
	 */
	long long GetRoomId() const { return m_roomId; }

	/**
	 *  Set the room id
	 *  @param	roomId	The room id
	 */
	void SetRoomId(long long roomId) { m_roomId = roomId; }

	/**
	 *  Get the password
	 *  @returns	The password
	 */
	const std::string &GetPassword() const { return m_password; }

	/**
	 *  Set the password
	 *  @param	password	The password
	 */
	void SetPassword(std::string password) { m_password = std::move(password); }

	/**
	 *  Get the authentication URL
	 *  @returns The URL
	 */
	const std::string &GetAuthUrl() const { return m_authUrl; }

	/**
	 *  Set the authentication URL
	 *  @param	authUrl	The URL
	 */
	void SetAuthUrl(std::string authUrl) { m_authUrl = std::move(authUrl); }

	/**
	 *  Get the properties of the room member who is joining
	 *  @returns	The member properties
	 */
	RoomMemberPropertiesPtr GetMemberProperties() const { return m_memberProperties; }

	/**
	 *  Set the properties of the room member who is joining
	 *  @param	memberProperties	The member properties
	 */
	void SetMemberProperties(RoomMemberPropertiesPtr memberProperties) { m_memberProperties = std::move(memberProperties); }

private:
	std::string m_host;
	int m_portNumber;
	net::channel::Protocol m_protocol;
	long long m_roomId;
	std::string m_password;
	std::string m_authUrl;
	RoomMemberPropertiesPtr m_memberProperties;
};

typedef std::shared_ptr<RoomJoinArgs> RoomJoinArgsPtr;

} } } } }
