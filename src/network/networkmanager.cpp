#include "networkmanager.h"
#include "configuration/configurationmanager.h"

#include <iostream>
#include <stdint.h>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

namespace network
{

NetworkManager::NetworkManager()
{
	init();
}

NetworkManager::~NetworkManager()
{}

bool NetworkManager::init()
{
	std::cout << "interval: " << configurationManager_.getReconnectionInterval() << std::endl;
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

	Connection source3( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.2", 3001);
	TrafficDirection direction3( source3);

	Connection dst6( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3030);
	Connection dst7( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3031);
	Connection dst8( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3032);
	direction3.addDistination( dst3);
	direction3.addDistination( dst4);
	direction3.addDistination( dst5);

	configurationManager_.updateTrafficDirection( trafficDirectionSet_);

	trafficDirectionSet_.erase( direction1);
	trafficDirectionSet_.insert( direction2);
	trafficDirectionSet_.insert( direction2);
	trafficDirectionSet_.insert( direction2);
	trafficDirectionSet_.insert( direction3);
	trafficDirectionSet_.insert( direction1);

	configurationManager_.updateTrafficDirection( trafficDirectionSet_);

	return true;
}

} /* namespace network */
