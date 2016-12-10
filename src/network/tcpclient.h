#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "networkprovider.h"

namespace network
{

class TcpClient
{
	typedef boost::shared_ptr <boost::asio::ip::tcp::socket> SocketPtr;

public:
	TcpClient();
	~TcpClient();

	bool init( const std::string& ipAddress, uint16_t port, uint16_t time = 500);
	void sendPacket( const std::string& packet);
	void setHandlerPacket( const HandlePacketCallBack& handleTcpPacket);

private:
	void connect();
	void startReading();
	void handleReading( BufferForReadPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);
	void handleWriting( const boost::system::error_code& error);

private:
	boost::asio::io_service& service_;
	std::string ip_;
	uint16_t port_;
	uint16_t time_;
	HandlePacketCallBack handlePacket_;
	BufferForReadPtr bufferForReadPtr_;

	SocketPtr socketPtr_;
	boost::asio::ip::tcp::endpoint partnerEndpoint_;
	boost::thread ioServiceThread_;
	boost::thread connectThread_;
};

typedef boost::shared_ptr< network::TcpClient> TcpClientPtr;

} /* namespace network */

#endif /* TCPCLIENT_H_ */
