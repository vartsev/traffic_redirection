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

	bool initByConfig();

	bool addTrafficDirection( const TrafficDirectionPtr trafficDirection);
	bool deleteTrafficDirection( const TrafficDirectionPtr trafficDirection);
	const TrafficDirectionList& getTrafficDirectionList() const;

private:
	bool handleSending( const Connection&, bool, const std::string&);

private:
	configuration::ConfigurationManager configurationManager_;

	TrafficDirectionList trafficDirectionList_;
};

} /* namespace model */

#endif /* TRAFFICDIRECTIONMANAGER_H_ */
