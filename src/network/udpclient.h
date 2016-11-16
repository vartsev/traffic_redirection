#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>

namespace network
{

class UdpClient
{
	typedef boost::shared_ptr <boost::asio::ip::udp::socket> SocketPtr;
	typedef boost::function< bool( const std::string&)> CallBack;

	typedef boost::array< char, 2048> BufferForRead;
	typedef boost::shared_ptr< BufferForRead> BufferForReadPtr;

public:
	UdpClient();
	~UdpClient();

	bool init( const std::string& ipAddress, uint16_t portForWrite, uint16_t portForRead, uint16_t time);
	void sendPacket( const std::string& packet);
	void setHandlerUdpPacket( CallBack handleUdpPacket);

private:
	void connect();
	void handleReceive( BufferForReadPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred);

private:
	bool isInit_;
	std::string ip_;
	uint16_t portForWrite_;
	uint16_t portForRead_;
	uint16_t time_;
	boost::asio::io_service service_;
	SocketPtr socketPtr_;
	CallBack handlePacket_;
	BufferForReadPtr bufferForReadPtr_;
	boost::asio::ip::udp::endpoint partnerEndpoint_;
	boost::thread ioServiceThread_;
};

typedef boost::shared_ptr< network::UdpClient> UdpClientPtr;

} /* namespace network */

#endif /* UDPCLIENT_H_ */
