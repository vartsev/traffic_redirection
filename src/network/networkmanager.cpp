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

	Connection source( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3000);
	TrafficDirection direction( 1, source);

	Connection dst( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3010);
	Connection dst1( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3011);
	Connection dst2( configuration::ConfigurationManager::TCP_SERVER_PARAMETER_NAME, "127.0.0.1", 3012);
	direction.addDistination( dst);
	direction.addDistination( dst1);
	direction.addDistination( dst2);

	Connection source1( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3001);
	TrafficDirection direction1( 2, source1);

	Connection dst3( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3020);
	Connection dst4( configuration::ConfigurationManager::TCP_CLIENT_PARAMETER_NAME, "127.0.0.1", 3021);
	Connection dst5( configuration::ConfigurationManager::UDP_PARAMETER_NAME, "127.0.0.1", 3022);
	direction1.addDistination( dst3);
	direction1.addDistination( dst4);
	direction1.addDistination( dst5);

	configurationManager_.updateTrafficDirection( trafficDirectionList_);

	trafficDirectionList_.remove( direction);
	trafficDirectionList_.push_back( direction1);
	trafficDirectionList_.push_back( direction);

	configurationManager_.updateTrafficDirection( trafficDirectionList_);

	return true;
}

} /* namespace network */
