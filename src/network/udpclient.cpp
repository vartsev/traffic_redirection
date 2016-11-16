#include "udpclient.h"
#include "configuration/configurationmanager.h"

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>

namespace network
{

UdpClient::UdpClient(): isInit_( false), ip_(""), portForWrite_( 44000), portForRead_( 44000), time_( 500)
{
	bufferForReadPtr_ = BufferForReadPtr( new BufferForRead);
}

UdpClient::~UdpClient()
{
	if ( socketPtr_.get())
		socketPtr_->close();

	service_.stop();
	ioServiceThread_.interrupt();
	ioServiceThread_.join();
}

bool UdpClient::init( const std::string& ipAddress, uint16_t portForWrite, uint16_t portForRead, uint16_t time)
{
	if ( socketPtr_.get())
		socketPtr_->close();
	service_.reset();

	try
	{
//		boost::property_tree::ptree root = configuration::ConfigurationManager::getInstance().readFromFile();

		ip_ = ipAddress;
		portForWrite_ = portForWrite;
		portForRead_ = portForRead;
		time_ = time;

		connect();

		isInit_ = true;
		return true;
	}
	catch( boost::system::system_error& error)
	{
		std::cout << error.what() << std::endl;
		return false;
	}
}

void UdpClient::connect()
{
	if ( socketPtr_.get())
		socketPtr_->close();
	service_.reset();

	partnerEndpoint_ = boost::asio::ip::udp::endpoint( boost::asio::ip::address::from_string( ip_), portForWrite_);
	boost::asio::ip::udp::endpoint endpoint( boost::asio::ip::udp::v4(), portForRead_);
	socketPtr_ = SocketPtr( new boost::asio::ip::udp::socket( service_, endpoint));

	if( !socketPtr_.get() || !socketPtr_->is_open())
	{
		usleep( time_ * 1000);
		ioServiceThread_.interrupt();
		ioServiceThread_.join();

		connect();
		return;
	}

	socketPtr_->async_receive( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &UdpClient::handleReceive, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	ioServiceThread_ = boost::thread( boost::bind( &boost::asio::io_service::run, &service_));

}

void UdpClient::handleReceive( BufferForReadPtr bufferPtr, const boost::system::error_code& error, size_t bytes_transferred)
{
	if( error.value() != 0)
	{
		connect();
		return;
	}

	std::string packet;
	std::copy( bufferPtr->begin(), bufferPtr->begin()+bytes_transferred, std::back_inserter( packet));

	handlePacket_( packet);

	if( !socketPtr_.get() || !socketPtr_->is_open())
	{
		init( ip_, portForWrite_, portForRead_, time_);
		return;
	}

	socketPtr_->async_receive( boost::asio::buffer( *bufferForReadPtr_),
		boost::bind( &UdpClient::handleReceive, this, bufferForReadPtr_, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UdpClient::sendPacket( const std::string& packet)
{
	if( !isInit_)
		return;

//	if( configuration::ConfigurationManager::getInstance().isLoggingToConsole())
//		std::cout << boost::posix_time::microsec_clock::local_time() << " sendUdpPacket addr: " << ip_ << " size: " << packet.size() << std::endl;

	socketPtr_->send_to( boost::asio::buffer( packet), partnerEndpoint_);
}

void UdpClient::setHandlerUdpPacket( CallBack handleUdpPacket)
{
	handlePacket_ = handleUdpPacket;
}

} /* namespace conversion */
