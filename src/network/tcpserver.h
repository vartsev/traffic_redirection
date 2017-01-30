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

private:
	void expectConnection();

	void startReading();
	void handleReading( BufferForReadPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);
	void handleWriting( const boost::system::error_code& error);

private:
	boost::asio::io_service& service_;
	bool isInit_;
	bool isStop_;
	HandlePacketCallBack handlePacket_;

	BufferForReadPtr bufferForReadPtr_;
	SocketPtr socketPtr_;
	boost::asio::ip::tcp::endpoint endpoint_;
	AcceptorPtr acceptorPtr_;
	boost::thread ioServiceThread_;
};

typedef boost::shared_ptr< network::TcpServer> TcpServerPtr;

} /* namespace network */

#endif /* TCPSERVER_H_ */
