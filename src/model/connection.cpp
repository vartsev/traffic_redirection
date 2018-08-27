#include "connection.h"
#include "configuration/configurationmanager.h"

namespace model
{

Connection::Connection( const std::string& protocol, const std::string& ip, uint16_t port, bool isSource):
			protocol_( protocol),
			ip_( ip),
			port_( port),
			isSource_( isSource),
			udpClientPtr_( nullptr),
			tcpClientPtr_( nullptr),
			tcpServerPtr_( nullptr)
{
}

Connection::~Connection()
{}

bool Connection::activate()
{
	bool result = false;
	if( protocol_ == configuration::ConfigurationManager::UDP_PARAMETER_NAME)
	{
		udpClientPtr_ = network::UdpClientPtr( new network::UdpClient());
		if( isSource_)
			result = udpClientPtr_->init( ip_, 0, port_);
		else
			result = udpClientPtr_->init( ip_, port_, 0);

		udpClientPtr_->setHandlerSending( std::bind( &Connection::handleSending,
						this, std::placeholders::_1, std::placeholders::_2));
	}
	else if( protocol_ == configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME)
	{
		tcpClientPtr_ = network::TcpClientPtr( new network::TcpClient());
		result = tcpClientPtr_->init( ip_, port_, configuration::ConfigurationManager::getReconnectionInterval());

		tcpClientPtr_->setHandlerSending( std::bind( &Connection::handleSending,
						this, std::placeholders::_1, std::placeholders::_2));
	}
	else if( protocol_ == configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME)
	{
		tcpServerPtr_ = network::TcpServerPtr( new network::TcpServer());
		result = tcpServerPtr_->init( port_);

		tcpServerPtr_->setHandlerSending( std::bind( &Connection::handleSending,
						this, std::placeholders::_1, std::placeholders::_2));
	}

	return result;
}

bool Connection::deactivate()
{
	if( protocol_ == configuration::ConfigurationManager::UDP_PARAMETER_NAME)
	{
		udpClientPtr_->~UdpClient();
		udpClientPtr_ = nullptr;
	}
	else if( protocol_ == configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME)
	{
		tcpClientPtr_->~TcpClient();
		tcpClientPtr_ = nullptr;
	}
	else if( protocol_ == configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME)
	{
		tcpServerPtr_->~TcpServer();
		tcpServerPtr_ = nullptr;
	}
	else
		return false;

	return true;
}

void Connection::sendPacket( const std::string& packet)
{
	if( udpClientPtr_)
		udpClientPtr_->sendPacket( packet);

	else if( tcpClientPtr_)
		tcpClientPtr_->sendPacket( packet);

	else if( tcpServerPtr_)
		tcpServerPtr_->sendPacket( packet);
}

void Connection::setHandlerPacket( const network::HandlePacketCallBack& handlePacket)
{
	if( udpClientPtr_ && protocol_ == configuration::ConfigurationManager::UDP_PARAMETER_NAME)
		udpClientPtr_->setHandlerPacket( handlePacket);
	else if( tcpClientPtr_ && protocol_ == configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME)
		tcpClientPtr_->setHandlerPacket( handlePacket);
	else if( tcpServerPtr_ && protocol_ == configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME)
		tcpServerPtr_->setHandlerPacket( handlePacket);
}

void Connection::setSendingResult( const SendingResult& callback)
{
	sendingResult_ = callback;
}

bool Connection::handleSending( bool state, const std::string& packet)
{
	return sendingResult_( *this, state, packet);
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

bool Connection::isSource() const
{
	return isSource_;
}

bool Connection::operator==( const Connection& right) const
{
	if( protocol_ == right.getPtotocol() &&
			ip_ == right.getIp() &&
			port_== right.getPort() &&
			isSource_ == right.isSource())
		return true;

	return false;
}

} /* namespace model */
