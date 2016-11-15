#ifndef CONFIGURATIONKEEPER_H_
#define CONFIGURATIONKEEPER_H_

#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdint.h>

namespace configuration
{

class ConfigurationKeeper
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
	ConfigurationKeeper();
	~ConfigurationKeeper();

	boost::property_tree::ptree& getConfigurationTree();
	void saveConfiguration( const boost::property_tree::ptree& configurationTree);

	bool isLoggingToFile();
	bool isLoggingToConsole();
	uint16_t getReconnectionInterval();

private:
	const boost::property_tree::ptree& readFromFile( const std::string& configPath);
	bool writeToFile( const boost::property_tree::ptree& configurationTree);
	std::string getConfigPath();

private:
	bool logToFile_;
	bool logToConsole_;
	uint16_t reconnectionInterval_;

	std::string configPath_;
	boost::property_tree::ptree configurationTree_;
};

} /* namespace configuration */

#endif /* CONFIGURATIONKEEPER_H_ */
