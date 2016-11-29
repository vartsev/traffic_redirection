#include "connection.h"
#include "configuration/configurationmanager.h"

namespace model
{

Connection::Connection( const std::string& protocol, const std::string& ip, uint16_t port):
			protocol_( protocol),
			ip_( ip),
			port_( port)
{
	if( protocol == configuration::ConfigurationManager::UDP_PARAMETER_NAME)
	{
		udpClientPtr_ = network::UdpClientPtr( new network::UdpClient());
		udpClientPtr_->init( ip, port, port, configuration::ConfigurationManager::getReconnectionInterval());
		udpClientPtr_->setHandlerPacket( handlePacket_);
	}
	else if( protocol == configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME)
	{
		tcpClientPtr_ = network::TcpClientPtr( new network::TcpClient());
		tcpClientPtr_->init( ip, port, configuration::ConfigurationManager::getReconnectionInterval());
		tcpClientPtr_->setHandlerPacket( handlePacket_);
	}
	else if( protocol == configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME)
	{
		tcpServerPtr_ = network::TcpServerPtr( new network::TcpServer());
		tcpServerPtr_->init( port);
		tcpServerPtr_->setHandlerPacket( handlePacket_);
	}
}

Connection::~Connection()
{}

void Connection::sendPacket( const std::string& packet)
{
	if( udpClientPtr_.get())
		udpClientPtr_->sendPacket( packet);

	else if( tcpClientPtr_.get())
		tcpClientPtr_->sendPacket( packet);

	else if( tcpServerPtr_.get())
		tcpServerPtr_->sendPacket( packet);
}

void Connection::setHandlerPacket( const network::CallBack& handlePacket)
{
	handlePacket_ = handlePacket;
}

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

} /* namespace model */