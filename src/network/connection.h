#ifndef CONNECTION_H_
#define CONNECTION_H_

#include<string>
#include<stdint.h>

#include "udpclient.h"
#include "tcpclient.h"
#include "tcpserver.h"

namespace network
{

class Connection
{
public:
	Connection( const std::string& protocol, const std::string& ip, uint16_t port);
	~Connection();

	const std::string& getPtotocol() const;
	const std::string& getIp() const;
	const uint16_t getPort() const;

	bool operator==( const Connection& right) const;
	bool operator<( const Connection& right) const;

private:
	std::string protocol_;
	std::string ip_;
	uint16_t port_;

	UdpClientPtr udpClientPtr_;
	TcpClientPtr tcpClientPtr_;
	TcpServerPtr tcpServerPtr_;
};

} /* namespace network */

#endif /* CONNECTION_H_ */
