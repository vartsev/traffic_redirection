#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include "configuration/configurationmanager.h"
#include "trafficdirection.h"

#include <boost/shared_ptr.hpp>
#include <vector>


namespace network
{

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	bool init();

private:
	configuration::ConfigurationManager configurationManager_;

	TrafficDirectionSet trafficDirectionSet_;
};

} /* namespace network */

#endif /* NETWORKMANAGER_H_ */
