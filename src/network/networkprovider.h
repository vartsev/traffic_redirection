#ifndef NETWORKPROVIDER_H_
#define NETWORKPROVIDER_H_

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace network
{

static boost::asio::io_service SERVICE;

typedef std::function< void ( const std::string)> HandlePacketCallBack;
typedef std::array< char, 2048> BufferForRead;
typedef std::shared_ptr< BufferForRead> BufferForReadPtr;

} /* namespace network */

#endif /* NETWORKPROVIDER_H_ */
