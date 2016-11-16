#include "connection.h"
#include "configuration/configurationmanager.h"

namespace network
{

Connection::Connection( const std::string& protocol, const std::string& ip, uint16_t port):
			protocol_( protocol),
			ip_( ip),
			port_( port)
{
	if( protocol == configuration::ConfigurationManager::UDP_PARAMETER_NAME)
		udpClientPtr_ = UdpClientPtr( new UdpClient());
	else if( protocol == configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME)
		tcpClientPtr_ = TcpClientPtr( new TcpClient());
	else if( protocol == configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME)
		tcpServerPtr_ = TcpServerPtr( new TcpServer());
}

Connection::~Connection()
{}

const std::string& Connection::getPtotocol() const
{
	return protocol_;
}

const std::string& Connection::getIp() const
{
	return ip_;
}

const uint16_t Connection::getPort() const
{
	return port_;
}

bool Connection::operator==( const Connection& right) const
{
	if( protocol_ == right.getPtotocol() && ip_ == right.getIp() && port_== right.getPort())
		return true;

	return false;
}

bool Connection::operator<( const Connection& right) const
{
//	return port_ < right.getPort();

	if( port_ <= right.getPort() && !(*this == right))
		return true;

	return false;
}

} /* namespace network */
