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

	bool init( const std::string& ipAddress, uint16_t port, uint16_t time);
	void sendPacket( const std::string& packet);
	void setHandlerPacket( const HandlePacketCallBack& handleTcpPacket);
	void setHandlerSending( const HandleSendingCallBack& handleWriting);

private:
	void expectConnection();
	void startReading( const boost::system::error_code& error);
	void handleReading( BufferPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);
	void handleWriting( std::string packet, const boost::system::error_code& error);

private:
	boost::asio::io_service& service_;
	std::string ip_;
	uint16_t port_;
	bool isStop_;
	uint16_t time_;
	HandlePacketCallBack handlePacket_;
	HandleSendingCallBack handleWriting_;
	BufferPtr bufferForReadPtr_;

	SocketPtr socketPtr_;
	boost::asio::ip::tcp::endpoint partnerEndpoint_;
	boost::thread ioServiceThread_;
};

typedef std::shared_ptr< network::TcpClient> TcpClientPtr;

} /* namespace network */

#endif /* TCPCLIENT_H_ */
