#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

namespace network
{


class TcpClient
{
	typedef boost::function< void ( const std::string)> CallBack;
	typedef boost::array< char, 2048> BufferForRead;
	typedef boost::shared_ptr< BufferForRead> BufferForReadPtr;
	typedef boost::shared_ptr <boost::asio::ip::tcp::socket> SocketPtr;

public:
	TcpClient();
	~TcpClient();

	bool init( const std::string& ipAddress, uint16_t port, uint16_t time = 500);
	void sendPacket( const std::string& packet);
	void setHandlerPacket( const CallBack& handleTcpPacket);

private:
	void connect();
	void startReading();
	void handleReading( BufferForReadPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);
	void handleWriting( const boost::system::error_code& error);

private:
	bool isInit_;
	bool isConnected_;
	std::string ip_;
	uint16_t port_;
	uint16_t time_;
	CallBack handlePacket_;
	BufferForReadPtr bufferForReadPtr_;

	boost::asio::io_service service_;
	SocketPtr socketPtr_;
	boost::asio::ip::tcp::endpoint partnerEndpoint_;
	boost::thread ioServiceThread_;
};

typedef boost::shared_ptr< network::TcpClient> TcpClientPtr;

} /* namespace network */

#endif /* TCPCLIENT_H_ */
