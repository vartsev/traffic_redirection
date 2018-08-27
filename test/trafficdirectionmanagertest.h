#ifndef TRAFFICDIRECTIONMANAGERTEST_H_
#define TRAFFICDIRECTIONMANAGERTEST_H_

#include "network/udpclient.h"
#include "network/tcpclient.h"
#include "network/tcpserver.h"
#include "model/trafficdirectionmanager.h"

#include <boost/lexical_cast.hpp>

namespace model
{

class TrafficDirectionManagerTest
{
public:
	TrafficDirectionManagerTest()
	{
		startTest();
	}
	~TrafficDirectionManagerTest()
	{}

	void startTest();

	bool handleUdpClientPacket( const std::string& packet);
	bool handleTcpClientPacket( const std::string& packet);
	bool handleTcpServerPacket( const std::string& packet);

};

bool TrafficDirectionManagerTest::handleUdpClientPacket( const std::string& packet)
{
//	std::cout << "handle UdpClient packet: " << packet << std::endl;
	return true;
}

bool TrafficDirectionManagerTest::handleTcpClientPacket( const std::string& packet)
{
//	std::cout << "handle TcpClient packet: " << packet << std::endl;
	return true;
}

bool TrafficDirectionManagerTest::handleTcpServerPacket( const std::string& packet)
{
//	std::cout << "handle TcpServer packet: " << packet << std::endl;
	return true;
}

void TrafficDirectionManagerTest::startTest()
{
	network::UdpClient udpClient;
	udpClient.init( "127.0.0.1", 3032, 0);
	udpClient.setHandlerPacket( std::bind( &TrafficDirectionManagerTest::handleUdpClientPacket, this, std::placeholders::_1));

//	network::UdpClient udpClient;
//	udpClient.init("127.0.0.1", 3030, 3031);
//	udpClient.setHandlerPacket( boost::bind( &TrafficDirectionManagerTest::handleUdpClientPacket, this, _1));
//	network::TcpClient tcpClient;
//	tcpClient.init( "127.0.0.1", 4040);
//	tcpClient.setHandlerPacket( boost::bind( &TrafficDirectionManagerTest::handleTcpClientPacket, this, _1));
//	network::TcpServer tcpServer;
//	tcpServer.init( 5050);
//	tcpServer.setHandlerPacket( boost::bind( &TrafficDirectionManagerTest::handleTcpServerPacket, this, _1));


	TrafficDirectionManager manager;
	ConnectionPtr source1 = ConnectionPtr( new Connection(
		configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3032, true));

	TrafficDirectionPtr direction1 = TrafficDirectionPtr( new TrafficDirection( source1));

	ConnectionPtr dst = ConnectionPtr( new Connection(
		configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3010));

	ConnectionPtr dst1 = ConnectionPtr( new Connection(
		configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3011));

	ConnectionPtr dst2 = ConnectionPtr( new Connection(
			configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME, "127.0.0.1", 3012));

	direction1->addDistination( dst);
	direction1->addDistination( dst1);
	direction1->addDistination( dst2);
	manager.addTrafficDirection( direction1);

	network::TcpServer server;
	int n = 0;
	while(true)
	{
		udpClient.sendPacket( "udpClient packet " + boost::lexical_cast<std::string>(n));
//		tcpClient.sendPacket( "tcpClient packet " + boost::lexical_cast<std::string>(n));
//		tcpServer.sendPacket( "tcpServer packet " + boost::lexical_cast<std::string>(n));
		n++;
		sleep(1);

		if (n == 10)
		{
			server.init( 3011);
			server.setHandlerPacket( std::bind( &TrafficDirectionManagerTest::handleTcpServerPacket, this, std::placeholders::_1));

		}
	}
}

} /* namespace model */

#endif /* TRAFFICDIRECTIONMANAGERTEST_H_ */
