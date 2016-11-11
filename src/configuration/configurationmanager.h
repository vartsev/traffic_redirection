#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/json_parser.hpp>

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
    static ConfigurationManager& getInstance()
    {
        static ConfigurationManager  instance;
        return instance;
    }

	boost::property_tree::ptree readFromFile();
	void writeToFile( const boost::property_tree::ptree& root);

	bool isLoggingToFile();
	bool isLoggingToConsole();

private:
	ConfigurationManager();
	~ConfigurationManager();

	std::string getConfigPath();

private:
	bool logToFile_;
	bool logToConsole_;
};

} /* namespace configuration */

#endif /* CONFIGURATIONMANAGER_H_ */
