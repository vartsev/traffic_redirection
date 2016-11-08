#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "tcpclient.h"
#include "udpclient.h"

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
	UdpClient udpClient_;
	TcpClientVector tcpClientVector_;
};

} /* namespace network */

#endif /* NETWORKMANAGER_H_ */
