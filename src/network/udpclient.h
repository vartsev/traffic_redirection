#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#include "networkprovider.h"

namespace network
{

class UdpClient
{
	typedef boost::shared_ptr <boost::asio::ip::udp::socket> SocketPtr;

public:
	UdpClient();
	~UdpClient();

	bool init( const std::string& ipAddress, uint16_t portForWrite, uint16_t portForRead, uint16_t time = 500);
	void sendPacket( const std::string& packet);
	void setHandlerPacket( const HandlePacketCallBack& handleUdpPacket);

private:
	void connect();
	void handleReceive( BufferForReadPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);

private:
	boost::asio::io_service& service_;
	std::string ip_;
	uint16_t portForWrite_;
	uint16_t portForRead_;
	uint16_t time_;
	bool isStop_;
	SocketPtr socketPtr_;
	HandlePacketCallBack handlePacket_;
	BufferForReadPtr bufferForReadPtr_;
	boost::asio::ip::udp::endpoint partnerEndpoint_;
	boost::thread ioServiceThread_;
};

typedef boost::shared_ptr< network::UdpClient> UdpClientPtr;

} /* namespace network */

#endif /* UDPCLIENT_H_ */
