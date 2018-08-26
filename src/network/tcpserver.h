#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "networkprovider.h"

namespace network
{

class TcpServer
{
	typedef boost::shared_ptr <boost::asio::ip::tcp::acceptor> AcceptorPtr;
	typedef boost::shared_ptr <boost::asio::ip::tcp::socket> SocketPtr;

public:
	TcpServer();
	~TcpServer();

	bool init( uint16_t port);
	void sendPacket( const std::string& packet);
	void setHandlerPacket( const HandlePacketCallBack& handlePacket);
	void setHandlerSending( const HandleSendingCallBack& handleWriting);

private:
	void expectConnection();

	void startReading();
	void handleReading( BufferPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);
	void handleWriting( std::string packet, const boost::system::error_code& error);

private:
	boost::asio::io_service& service_;
	bool isInit_;
	bool isStop_;
	HandlePacketCallBack handlePacket_;
	HandleSendingCallBack handleWriting_;

	BufferPtr bufferForReadPtr_;
	SocketPtr socketPtr_;
	boost::asio::ip::tcp::endpoint endpoint_;
	AcceptorPtr acceptorPtr_;
	boost::thread ioServiceThread_;
};

typedef std::shared_ptr< network::TcpServer> TcpServerPtr;

} /* namespace network */

#endif /* TCPSERVER_H_ */
