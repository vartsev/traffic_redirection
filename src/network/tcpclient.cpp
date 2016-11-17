#include "tcpclient.h"
#include "configuration/configurationmanager.h"

#include <boost/date_time.hpp>
#include <boost/lexical_cast.hpp>

namespace network
{

TcpClient::TcpClient() : isInit_( false), isConnected_( false), ip_(""), port_( 34000), time_( 500)
{
	bufferForReadPtr_ = BufferForReadPtr( new BufferForRead);
}

TcpClient::~TcpClient()
{
	isConnected_ = false;

	if ( socketPtr_.get())
		socketPtr_->close();

	service_.stop();
	ioServiceThread_.detach();
	ioServiceThread_.interrupt();
	ioServiceThread_.join();
}

bool TcpClient::init( const std::string& ipAddress, uint16_t port, uint16_t time)
{
		ip_ = ipAddress;
		port_ = port;
		time_ = time;

		connect();

		isInit_ = true;
		return true;
}

void TcpClient::connect()
{
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

	boost::system::error_code error;
	socketPtr_->connect( partnerEndpoint_, error);

	if( error.value() != 0)
	{
//		if( configuration::ConfigurationManager::getInstance().isLoggingToConsole())
//			std::cout <<  boost::posix_time::microsec_clock::local_time() <<" no connection! error: " << error.value() << std::endl;
		isConnected_ = false;
		usleep( time_ * 1000);
		connect();
		return;
	}

	startReading();

	isConnected_ = true;
}

void TcpClient::startReading()
{
	if( !socketPtr_.get() || !socketPtr_->is_open())
		return;

	socketPtr_->async_read_some( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &TcpClient::handleReading, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	ioServiceThread_ = boost::thread( boost::bind( &boost::asio::io_service::run, &service_));
}

void TcpClient::handleReading( BufferForReadPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred)
{
	if( error.value() != 0)
	{
		isConnected_ = false;
		connect();
		return;
	}

	std::string packet;
	std::copy( bufferPtr->begin(), bufferPtr->begin()+bytes_transferred, std::back_inserter( packet));

	handlePacket_( packet);

	if( !socketPtr_.get() || !socketPtr_->is_open())
	{
		isConnected_ = false;
		connect();
		return;
	}

	socketPtr_->async_read_some( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &TcpClient::handleReading, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpClient::sendPacket( const std::string& packet)
{
	if( !isInit_)
		return;

	if( !isConnected_ || !socketPtr_.get() || !socketPtr_->is_open())
	{
		isConnected_ = false;
		return;
	}

	try
	{
//		if( configuration::ConfigurationManager::getInstance().isLoggingToConsole())
//			std::cout << boost::posix_time::microsec_clock::local_time() << " sendTcpPacket addr: " << ip_ << " size: " << packet.size() << std::endl;

		boost::asio::async_write( *socketPtr_, boost::asio::buffer( packet),
			boost::bind( &TcpClient::handleWriting, this, boost::asio::placeholders::error));
	}
	catch( const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TcpClient::setHandlerPacket( const CallBack& handleTcpPacket)
{
	handlePacket_ = handleTcpPacket;
}

void TcpClient::handleWriting( const boost::system::error_code& error)
{
	if( error.value() != 0)
	{
		std::cout << "handleWriting error: " << error.value() << std::endl;
		isConnected_ = false;
		return;
	}
}

} /* namespace network */
