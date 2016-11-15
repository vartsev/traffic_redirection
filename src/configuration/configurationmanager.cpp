#include "configurationmanager.h"
#include <boost/lexical_cast.hpp>

namespace configuration
{

ConfigurationManager::ConfigurationManager()
{

}

ConfigurationManager::~ConfigurationManager()
{

}

bool ConfigurationManager::getLoggingToFileState()
{
	return configurationKeeper_.isLoggingToFile();
}

void ConfigurationManager::saveLoggingToFileState( bool state)
{
	boost::property_tree::ptree& configurationTree( configurationKeeper_.getConfigurationTree());
	configurationTree.get_child( configuration::ConfigurationKeeper::LOG_TO_FILE_PARAMETER_NAME).
					put_value<std::string>( boost::lexical_cast<std::string>( state));

	configurationKeeper_.saveConfiguration( configurationTree);
}

bool ConfigurationManager::getLoggingToConsoleState()
{
	return configurationKeeper_.isLoggingToConsole();
}

void ConfigurationManager::saveLoggingToConsoleState( bool state)
{
	boost::property_tree::ptree& configurationTree( configurationKeeper_.getConfigurationTree());
	configurationTree.get_child( configuration::ConfigurationKeeper::LOG_TO_CONSOLE_PARAMETER_NAME).
					put_value<std::string>( boost::lexical_cast<std::string>( state));

	configurationKeeper_.saveConfiguration( configurationTree);
}

uint16_t ConfigurationManager::getReconnectionInterval()
{
	return configurationKeeper_.getReconnectionInterval();
}

void ConfigurationManager::saveReconnectionInterval( uint16_t inerval)
{
	boost::property_tree::ptree& configurationTree( configurationKeeper_.getConfigurationTree());
	configurationTree.get_child( configuration::ConfigurationKeeper::RECONNECT_INTERVAL_PARAMETER_NAME).
					put_value<std::string>( boost::lexical_cast<std::string>( inerval));

	configurationKeeper_.saveConfiguration( configurationTree);
}

} /* namespace configuration */
