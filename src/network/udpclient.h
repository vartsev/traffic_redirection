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
	void setHandlerSending( const HandleSendingCallBack& handleSending);

private:
	void connect();
	void handleReceive( BufferPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);
	void handleSending( std::string packet, const boost::system::error_code& error);

private:
	boost::asio::io_service& service_;
	std::string ip_;
	uint16_t portForWrite_;
	uint16_t portForRead_;
	uint16_t time_;
	bool isStop_;
	SocketPtr socketPtr_;
	HandlePacketCallBack handlePacket_;
	HandleSendingCallBack handleSending_;
	BufferPtr bufferForReadPtr_;
	boost::asio::ip::udp::endpoint partnerEndpoint_;
	boost::thread ioServiceThread_;
};

typedef std::shared_ptr< network::UdpClient> UdpClientPtr;

} /* namespace network */

#endif /* UDPCLIENT_H_ */
