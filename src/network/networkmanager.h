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

	bool addTrafficDirection( const TrafficDirection& trafficDirection);
	bool deleteTrafficDirection( const TrafficDirection& trafficDirection);

private:
	configuration::ConfigurationManager configurationManager_;

	TrafficDirectionList trafficDirectionList_;
};

} /* namespace network */

#endif /* NETWORKMANAGER_H_ */
