#ifndef NETWORKPROVIDER_H_
#define NETWORKPROVIDER_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

namespace network
{

static boost::asio::io_service SERVICE;

typedef boost::function< void ( const std::string)> HandlePacketCallBack;
typedef boost::array< char, 2048> BufferForRead;
typedef boost::shared_ptr< BufferForRead> BufferForReadPtr;

} /* namespace network */

#endif /* NETWORKPROVIDER_H_ */
