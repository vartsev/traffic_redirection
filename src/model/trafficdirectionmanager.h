#ifndef TRAFFICDIRECTIONMANAGER_H_
#define TRAFFICDIRECTIONMANAGER_H_

#include "configuration/configurationmanager.h"
#include "trafficdirection.h"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace model
{

class TrafficDirectionManager
{
public:
	TrafficDirectionManager();
	~TrafficDirectionManager();

	bool init();

	bool addTrafficDirection( const TrafficDirection& trafficDirection);
	bool deleteTrafficDirection( const TrafficDirection& trafficDirection);

private:
	configuration::ConfigurationManager configurationManager_;

	TrafficDirectionList trafficDirectionList_;
};

} /* namespace model */

#endif /* TRAFFICDIRECTIONMANAGER_H_ */
