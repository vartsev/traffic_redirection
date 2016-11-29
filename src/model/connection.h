#ifndef CONNECTION_H_
#define CONNECTION_H_

#include<string>
#include<stdint.h>
#include <list>

#include "network/udpclient.h"
#include "network/tcpclient.h"
#include "network/tcpserver.h"

namespace model
{

class Connection
{
public:
	Connection( const std::string& protocol, const std::string& ip, uint16_t port);
	~Connection();

	void sendPacket( const std::string& packet);
	void setHandlerPacket( const network::CallBack& handlePacket);

	const std::string& getPtotocol() const;
	const std::string& getIp() const;
	const uint16_t getPort() const;

	bool operator==( const Connection& right) const;

private:
	std::string protocol_;
	std::string ip_;
	uint16_t port_;

	network::UdpClientPtr udpClientPtr_;
	network::TcpClientPtr tcpClientPtr_;
	network::TcpServerPtr tcpServerPtr_;

	network::CallBack handlePacket_;
};

typedef std::list< Connection> ConnectionList;

} /* namespace model */

#endif /* CONNECTION_H_ */
