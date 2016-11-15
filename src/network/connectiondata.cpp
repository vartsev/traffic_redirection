#include "connectiondata.h"

namespace network
{

ConnectionData::ConnectionData( const std::string& protocol, const std::string& ip, uint16_t port):
			protocol_( protocol),
			ip_( ip),
			port_( port)
{}

ConnectionData::~ConnectionData()
{}

const std::string& ConnectionData::getPtotocol() const
{
	return protocol_;
}

const std::string& ConnectionData::getIp() const
{
	return ip_;
}

const uint16_t ConnectionData::getPort() const
{
	return port_;
}

bool ConnectionData::operator==( const ConnectionData& right)
{
	if( protocol_ == right.getPtotocol() && ip_ == right.getIp() && port_== right.getPort())
		return true;

	return false;
}

} /* namespace network */
