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

bool Connection::operator==( const Connection& right)
{
	return (protocol_ == right.getPtotocol()) ? true : false;
}

} /* namespace network */
