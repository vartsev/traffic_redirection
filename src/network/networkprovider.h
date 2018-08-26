#ifndef NETWORKPROVIDER_H_
#define NETWORKPROVIDER_H_

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace network
{

static boost::asio::io_service SERVICE;

typedef std::function< bool ( const std::string&)> HandlePacketCallBack;
typedef std::function< bool ( bool, const std::string&)> HandleSendingCallBack;
typedef std::array< char, 2048> Buffer;
typedef std::shared_ptr< Buffer> BufferPtr;

} /* namespace network */

#endif /* NETWORKPROVIDER_H_ */
