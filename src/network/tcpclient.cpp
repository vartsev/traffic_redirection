#include "tcpclient.h"
#include "configuration/configurationmanager.h"

#include <boost/date_time.hpp>
#include <boost/lexical_cast.hpp>

namespace network
{

TcpClient::TcpClient():
		service_( SERVICE),
		ip_(""),
		port_( 34000),
		isStop_( false),
		time_( 500)
{
	bufferForReadPtr_ = BufferPtr( new Buffer);
}

TcpClient::~TcpClient()
{
	isStop_ = true;
	if ( socketPtr_.get())
		socketPtr_->close();

	service_.stop();

	ioServiceThread_.interrupt();
	ioServiceThread_.detach();
}

bool TcpClient::init( const std::string& ipAddress, uint16_t port, uint16_t time)
{
	ip_ = ipAddress;
	port_ = port;
	time_= time;

	expectConnection();

	return true;
}

void TcpClient::expectConnection()
{
	if( isStop_)
		return;

	if ( socketPtr_.get())
		socketPtr_->close();
	service_.reset();
	ioServiceThread_.detach();
	ioServiceThread_.interrupt();
	ioServiceThread_.join();

	partnerEndpoint_ = boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string( ip_), port_);
	socketPtr_ = SocketPtr( new boost::asio::ip::tcp::socket( service_));
	socketPtr_->open( boost::asio::ip::tcp::v4());
	boost::asio::ip::tcp::no_delay option( true);
	socketPtr_->set_option( option);

	socketPtr_->async_connect( partnerEndpoint_, boost::bind( &TcpClient::startReading, this, boost::asio::placeholders::error));
	ioServiceThread_ = boost::thread( boost::bind( &boost::asio::io_service::run, &service_));
}

void TcpClient::startReading( const boost::system::error_code& error)
{
	if( error.value() != 0 || !socketPtr_.get() || !socketPtr_->is_open())
	{
		usleep( time_*1000);
		expectConnection();
		return;
	}

	socketPtr_->async_read_some( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &TcpClient::handleReading, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpClient::handleReading( BufferPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred)
{
	if( error.value() != 0)
	{
		expectConnection();
		return;
	}

	std::string packet;
	std::copy( bufferPtr->begin(), bufferPtr->begin()+bytes_transferred, std::back_inserter( packet));

	if( handlePacket_)
		handlePacket_( packet);

	if( !socketPtr_.get() || !socketPtr_->is_open())
	{
		expectConnection();
		return;
	}

	socketPtr_->async_read_some( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &TcpClient::handleReading, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpClient::sendPacket( const std::string& packet)
{
	if( !socketPtr_.get() || !socketPtr_->is_open())
	{
		handleWriting_( false, packet);
		return;
	}

	try
	{
		boost::asio::async_write( *socketPtr_, boost::asio::buffer( packet),
			boost::bind( &TcpClient::handleWriting, this, packet, boost::asio::placeholders::error));
	}
	catch( const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TcpClient::setHandlerPacket( const HandlePacketCallBack& handleTcpPacket)
{
	handlePacket_ = handleTcpPacket;
}

void TcpClient::setHandlerSending( const HandleSendingCallBack& handleWriting)
{
	handleWriting_ = handleWriting;
}

void TcpClient::handleWriting( std::string packet, const boost::system::error_code& error)
{
	if( !handleWriting_)
		return;

	if( error.value() == 0)
	{
		handleWriting_( true, packet);
	}
	else
		handleWriting_( false, packet);
}

} /* namespace network */
