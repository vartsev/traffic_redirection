#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace configuration
{

class ConfigurationManager
{
public:
	static const std::string CONFIG_NAME;

	static const std::string DIRECTIONS_PARAMETER_NAME;
	static const std::string PROTOCOL_PARAMETER_NAME;
	static const std::string SRC_PARAMETER_NAME;
	static const std::string DST_PARAMETER_NAME;

	static const std::string UDP_PARAMETER_NAME;
	static const std::string TCP_PARAMETER_NAME;

	static const std::string PARTNER_IP_PARAMETER_NAME;
	static const std::string PORT_FOR_WRITE_PARAMETER_NAME;
	static const std::string PORT_FOR_READ_PARAMETER_NAME;

	static const std::string DEFAULT_PARTNER_IP;
	static const std::string DEFAULT_PORT_FOR_WRITE;
	static const std::string DEFAULT_PORT_FOR_READ;

	static const std::string UDP_TO_TCP;
	static const std::string TCP_TO_UDP;

	static const std::string RECONNECT_TIME_PARAMETER_NAME;
	static const std::string LOG_TO_CONSOLE_PARAMETER_NAME;

public:
    static ConfigurationManager& getInstance()
    {
        static ConfigurationManager  instance;
        return instance;
    }

	boost::property_tree::ptree readFromFile();
	void writeToFile( const boost::property_tree::ptree& root);

	bool isLogging();
	bool isUdpToTcp();
	bool isTcpToUdp();

private:
	ConfigurationManager();
	~ConfigurationManager();

private:
	bool logState_;
	bool udpToTcp_;
	bool tcpToUdp_;
};

} /* namespace configuration */

#endif /* CONFIGURATIONMANAGER_H_ */
