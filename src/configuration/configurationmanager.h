#ifndef CONFIGURATIONKEEPER_H_
#define CONFIGURATIONKEEPER_H_

#include "network/trafficdirection.h"

#include <boost/thread.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdint.h>
#include <vector>

namespace configuration
{

class ConfigurationManager
{

public:
	static const std::string CONFIG_PATH;
	static const std::string CONFIG_NAME;

	static const std::string LOG_TO_FILE_PARAMETER_NAME;
	static const std::string LOG_TO_CONSOLE_PARAMETER_NAME;
	static const std::string RECONNECT_INTERVAL_PARAMETER_NAME;

	static const std::string DIRECTIONS_PARAMETER_NAME;
	static const std::string SRC_PARAMETER_NAME;
	static const std::string DST_PARAMETER_NAME;

	static const std::string PROTOCOL_PARAMETER_NAME;
	static const std::string IP_PARAMETER_NAME;
	static const std::string PORT_PARAMETER_NAME;

	static const std::string UDP_PARAMETER_NAME;
	static const std::string TCP_CLIENT_PARAMETER_NAME;
	static const std::string TCP_SERVER_PARAMETER_NAME;

	static const std::string DEFAULT_IP;
	static const std::string DEFAULT_PORT;
	static const std::string DEFAULT_INTERVAL;
	static const std::string DEFAULT_LOGGING;

public:
	ConfigurationManager();
	~ConfigurationManager();

	boost::property_tree::ptree& getConfigurationTree();
	void saveConfiguration( const boost::property_tree::ptree& configurationTree);

	static bool isLoggingToFile();
	void saveLoggingToFileState( bool state);

	static bool isLoggingToConsole();
	void saveLoggingToConsoleState( bool state);

	static uint16_t getReconnectionInterval();
	void saveReconnectionInterval( uint16_t inerval);

	void updateTrafficDirection( const network::TrafficDirectionList& trafficDirectionList);

private:
	const boost::property_tree::ptree& readFromFile( const std::string& configPath);
	bool writeToFile( const boost::property_tree::ptree& configurationTree);
	std::string getConfigPath();

private:
	static bool logToFile_;
	static bool logToConsole_;
	static uint16_t reconnectionInterval_;
	std::string configPath_;

	boost::property_tree::ptree configurationTree_;
	boost::mutex mutex_;
};

} /* namespace configuration */

#endif /* CONFIGURATIONKEEPER_H_ */
