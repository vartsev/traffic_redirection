#include "trafficdirectionmanager.h"
#include "configuration/configurationmanager.h"

#include <iostream>
#include <stdint.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

namespace network
{

TrafficDirectionManager::TrafficDirectionManager()
{
	init();
}

TrafficDirectionManager::~TrafficDirectionManager()
{}

bool TrafficDirectionManager::init()
{
	configurationManager_.saveLoggingToFileState( true);
	configurationManager_.saveLoggingToConsoleState( true);
	configurationManager_.saveReconnectionInterval( 400);

	Connection source1( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3002);
	TrafficDirection direction1( source1);

	Connection dst( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3010);
	Connection dst1( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3011);
	Connection dst2( configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME, "127.0.0.1", 3012);
	direction1.addDistination( dst);
	direction1.addDistination( dst1);
	direction1.addDistination( dst2);

	Connection source2( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3001);
	TrafficDirection direction2( source2);

	Connection dst3( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3020);
	Connection dst4( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3021);
	Connection dst5( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3022);
	direction2.addDistination( dst3);
	direction2.addDistination( dst4);
	direction2.addDistination( dst5);

	Connection source3( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3001);
	TrafficDirection direction3( source3);

	Connection dst6( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3030);
	Connection dst7( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3031);
	Connection dst8( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3032);
	direction3.addDistination( dst6);
	direction3.addDistination( dst7);
	direction3.addDistination( dst5);

	configurationManager_.updateTrafficDirection( trafficDirectionList_);

	deleteTrafficDirection( direction1);
	addTrafficDirection( direction2);
	addTrafficDirection( direction2);
	addTrafficDirection( direction2);
	addTrafficDirection( direction3);
	addTrafficDirection( direction1);

	deleteTrafficDirection( direction3);

	configurationManager_.updateTrafficDirection( trafficDirectionList_);

	return true;
}

bool TrafficDirectionManager::addTrafficDirection( const TrafficDirection& trafficDirection)
{
	bool isSame = false;
	for( TrafficDirectionList::iterator it = trafficDirectionList_.begin();
			it!= trafficDirectionList_.end(); ++it)
	{
		if( trafficDirection == *it)
			isSame = true;
	}

	if( !isSame)
		trafficDirectionList_.push_back( trafficDirection);
	else
		return false;

	return true;
}

bool TrafficDirectionManager::deleteTrafficDirection( const TrafficDirection& trafficDirection)
{
	trafficDirectionList_.remove( trafficDirection);

	return true;
}

} /* namespace network */
