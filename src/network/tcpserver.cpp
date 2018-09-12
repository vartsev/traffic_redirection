#include "tcpserver.h"

#include <boost/lexical_cast.hpp>

namespace network
{

TcpServer::TcpServer():
		service_( SERVICE),
		isInit_( false),
		isStop_( false)
{
	bufferForReadPtr_ = BufferPtr( new Buffer);
}

TcpServer::~TcpServer()
{
	isInit_ = false;
	isStop_ = true;

	if( acceptorPtr_.get())
		acceptorPtr_->close();

	if( socketPtr_.get())
		socketPtr_->close();

	service_.stop();
	ioServiceThread_.interrupt();
	ioServiceThread_.detach();
}

void TcpServer::setHandlerPacket( const HandlePacketCallBack& handlePacket)
{
	handlePacket_ = handlePacket;
}

void TcpServer::setHandlerSending( const HandleSendingCallBack& handleWriting)
{
	handleWriting_ = handleWriting;
}

bool TcpServer::init( uint16_t port)
{
	try
	{
		endpoint_ = boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port);
		expectConnection();

		isInit_ = true;

		return true;
	}
	catch( boost::system::system_error& error)
	{
		std::cout << error.what() << std::endl;
		return false;
	}
}

void TcpServer::expectConnection()
{
	if( isStop_)
		return;

	try
	{
		if( acceptorPtr_.get())
			acceptorPtr_->close();

		if( socketPtr_.get())
			socketPtr_->close();

		acceptorPtr_ = AcceptorPtr( new boost::asio::ip::tcp::acceptor( service_, endpoint_));
		socketPtr_ = SocketPtr( new boost::asio::ip::tcp::socket( service_));
		acceptorPtr_->listen();

		acceptorPtr_->async_accept( *socketPtr_, boost::bind( &TcpServer::startReading, this, boost::asio::placeholders::error));
		ioServiceThread_ = boost::thread( boost::bind( &boost::asio::io_service::run, &service_));
	}
	catch( std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TcpServer::startReading( const boost::system::error_code& error)
{
	if( error.value() != 0 || !socketPtr_.get() || !socketPtr_->is_open())
		return;

	socketPtr_->async_read_some( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &TcpServer::handleReading, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpServer::handleReading( BufferPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred)
{
	if( !socketPtr_.get() || !socketPtr_->is_open() || error.value() != 0)
	{
		expectConnection();
		return;
	}

	std::string packet;
	std::copy( bufferPtr->begin(), bufferPtr->begin()+bytes_transferred, std::back_inserter( packet));

	if( handlePacket_)
		handlePacket_( packet);

	socketPtr_->async_read_some( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &TcpServer::handleReading, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpServer::sendPacket( const std::string& packet)
{
	if( !isInit_ || !socketPtr_ || !socketPtr_->is_open())
	{
		if( !handleWriting_)
			return;

		handleWriting_( false, packet);
		return;
	}

	try
	{
		boost::asio::async_write( *socketPtr_, boost::asio::buffer( packet),
			boost::bind( &TcpServer::handleWriting, this, packet, boost::asio::placeholders::error));
	}
	catch( const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TcpServer::handleWriting( std::string packet, const boost::system::error_code& error)
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

} /* namespace application */
