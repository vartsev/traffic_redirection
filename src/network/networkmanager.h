#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include "configuration/configurationmanager.h"
#include "tcpclient.h"
#include "udpclient.h"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace network
{

typedef boost::shared_ptr< network::TcpClient> TcpClientPtr;
typedef std::vector<TcpClientPtr> TcpClientVector;

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	bool init();

	bool receiveUdpPacket( const std::string& packet);
	bool receiveTcpPacket( const std::string& packet);
	void sendUdpPacket( const std::string& packet);
	void sendTcpPacket( const std::string& packet);

private:
	configuration::ConfigurationManager configurationManager_;
	UdpClient udpClient_;
	TcpClientVector tcpClientVector_;
};

} /* namespace network */

#endif /* NETWORKMANAGER_H_ */
