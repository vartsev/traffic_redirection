#include "networkmanager.h"
#include "configuration/configurationmanager.h"

#include <iostream>
#include <stdint.h>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

namespace network
{

NetworkManager::NetworkManager()
{
	init();
}

NetworkManager::~NetworkManager()
{

}

bool NetworkManager::init()
{
//	udpClient_.setHandlerUdpPacket( boost::bind( &network::NetworkManager::receiveUdpPacket, this, _1));

	try
	{
		boost::property_tree::ptree root = configuration::ConfigurationManager::getInstance().readFromFile();

//		std::string ipAddress = root.get_child( configuration::ConfigurationManager::UDP_PARAMETER_NAME).
//								get_child( configuration::ConfigurationManager::PARTNER_IP_PARAMETER_NAME).
//								get_value<std::string>(configuration::ConfigurationManager::DEFAULT_PARTNER_IP);
//
//		uint16_t portForWrite = boost::lexical_cast<uint16_t>( root.get_child( configuration::ConfigurationManager::UDP_PARAMETER_NAME).
//				get_child( configuration::ConfigurationManager::PORT_FOR_WRITE_PARAMETER_NAME).
//				get_value<std::string>( configuration::ConfigurationManager::DEFAULT_PORT_FOR_WRITE));
//
//		uint16_t portForRead = boost::lexical_cast<uint16_t>( root.get_child( configuration::ConfigurationManager::UDP_PARAMETER_NAME).
//				get_child( configuration::ConfigurationManager::PORT_FOR_READ_PARAMETER_NAME).
//				get_value<std::string>( configuration::ConfigurationManager::DEFAULT_PORT_FOR_READ));
//
//		uint16_t time = boost::lexical_cast<uint32_t>( root.get_child( configuration::ConfigurationManager::RECONNECT_TIME_PARAMETER_NAME).get_value<std::string>( "500"));
//
//		udpClient_.init( ipAddress, portForWrite, portForRead, time);
//
//		std::cout << "UdpClient ip: " << ipAddress << "   portForWrite: " << portForWrite << "   portForRead: " << portForRead << std::endl;
//
//		BOOST_FOREACH( boost::property_tree::ptree::const_iterator::value_type item, root.get_child( configuration::ConfigurationManager::TCP_PARAMETER_NAME))
//		{
//			try
//			{
//				TcpClientPtr ptr( new network::TcpClient());
//				ptr->setHandlerTcpPacket( boost::bind( &network::NetworkManager::receiveTcpPacket, this, _1));
//				ipAddress = item.second.get_child( configuration::ConfigurationManager::PARTNER_IP_PARAMETER_NAME).get_value<std::string>();
//				portForWrite = boost::lexical_cast<uint16_t>( item.second.get_child( "Port").get_value<std::string>());
//				ptr->init( ipAddress, portForWrite, time);
//				tcpClientVector_.push_back( ptr);
//				std::cout << "TcpClient ip: " << ipAddress << "   port: " << portForWrite << std::endl;
//			}
//			catch( std::exception& e)
//			{
//				std::cout << "NetworkManager::init 2 error: " << e.what() << std::endl;
//				return false;
//			}
//		}
//
//		std::cout << "ReconnectInterval: " << time << std::endl;
	}
	catch( std::exception& e)
	{
		std::cout << "NetworkManager::init 1 error: " << e.what() << std::endl;
		return false;
	}

	return true;
}

bool NetworkManager::receiveUdpPacket( const std::string& packet)
{
	sendTcpPacket( packet);
	return true;
}

bool NetworkManager::receiveTcpPacket( const std::string& packet)
{
	sendUdpPacket( packet);
	return true;
}

void NetworkManager::sendUdpPacket( const std::string& packet)
{
//	if( !configuration::ConfigurationManager::getInstance().isTcpToUdp())
//		return;

	udpClient_.sendPacket( packet);
}

void NetworkManager::sendTcpPacket( const std::string& packet)
{
//	if( !configuration::ConfigurationManager::getInstance().isUdpToTcp())
//		return;

	for( TcpClientVector::iterator it = tcpClientVector_.begin(); it != tcpClientVector_.end(); ++it)
		it->get()->sendPacket( packet);
}

} /* namespace network */
