#ifndef TRAFFICDIRECTIONMANAGERTEST_H_
#define TRAFFICDIRECTIONMANAGERTEST_H_

#include "network/udpclient.h"
#include "network/tcpclient.h"
#include "network/tcpserver.h"

#include <boost/lexical_cast.hpp>

namespace network
{

class TrafficDirectionManagerTest
{
public:
	TrafficDirectionManagerTest()
	{
		startTest();
	}

	void startTest();
	void testList();
	bool handleUdpClientPacket( const std::string& packet);
	bool handleTcpClientPacket( const std::string& packet);
	bool handleTcpServerPacket( const std::string& packet);

	~TrafficDirectionManagerTest()
	{}
};

bool TrafficDirectionManagerTest::handleUdpClientPacket( const std::string& packet)
{
	std::cout << "handle UdpClient packet: " << packet << std::endl;
	return true;
}

bool TrafficDirectionManagerTest::handleTcpClientPacket( const std::string& packet)
{
	std::cout << "handle TcpClient packet: " << packet << std::endl;
	return true;
}

bool TrafficDirectionManagerTest::handleTcpServerPacket( const std::string& packet)
{
	std::cout << "handle TcpServer packet: " << packet << std::endl;
	return true;
}

void TrafficDirectionManagerTest::startTest()
{
	std::cout << "Start test" << std::endl;
	network::UdpClient udpClient;
	udpClient.init("127.0.0.1", 3030, 3031);
	udpClient.setHandlerPacket( boost::bind( &TrafficDirectionManagerTest::handleUdpClientPacket, this, _1));
	network::TcpClient tcpClient;
	tcpClient.init( "127.0.0.1", 4040);
	tcpClient.setHandlerPacket( boost::bind( &TrafficDirectionManagerTest::handleTcpClientPacket, this, _1));
	network::TcpServer tcpServer;
	tcpServer.init( 5050);
	tcpServer.setHandlerPacket( boost::bind( &TrafficDirectionManagerTest::handleTcpServerPacket, this, _1));
	int n = 0;
	while(true)
	{
		udpClient.sendPacket( "udpClient packet " + boost::lexical_cast<std::string>(n));
		tcpClient.sendPacket( "tcpClient packet " + boost::lexical_cast<std::string>(n));
		tcpServer.sendPacket( "tcpServer packet " + boost::lexical_cast<std::string>(n));
		n++;
		sleep(1);
	}
}

void TrafficDirectionManagerTest::testList()
{
	sleep(5);
}

} /* namespace network */

#endif /* TRAFFICDIRECTIONMANAGERTEST_H_ */
