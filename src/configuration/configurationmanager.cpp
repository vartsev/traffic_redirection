#include "configurationmanager.h"
#include <fstream>

namespace configuration
{

const std::string ConfigurationManager::CONFIG_NAME = "./config.txt";

const std::string ConfigurationManager::DIRECTIONS_PARAMETER_NAME = "Directions";
const std::string ConfigurationManager::PROTOCOL_PARAMETER_NAME = "Protocol";
const std::string ConfigurationManager::SRC_PARAMETER_NAME = "Source";
const std::string ConfigurationManager::DST_PARAMETER_NAME = "Distination";

const std::string ConfigurationManager::UDP_PARAMETER_NAME = "udp";
const std::string ConfigurationManager::TCP_PARAMETER_NAME = "tcp";

const std::string ConfigurationManager::PORT_FOR_WRITE_PARAMETER_NAME = "PortForWrite";
const std::string ConfigurationManager::PORT_FOR_READ_PARAMETER_NAME = "PortForRead";
const std::string ConfigurationManager::PARTNER_IP_PARAMETER_NAME = "RemoteIp";

const std::string ConfigurationManager::DEFAULT_PARTNER_IP = "127.0.0.1";
const std::string ConfigurationManager::DEFAULT_PORT_FOR_WRITE = "44000";
const std::string ConfigurationManager::DEFAULT_PORT_FOR_READ = "44000";

const std::string ConfigurationManager::UDP_TO_TCP = "udp_to_tcp";
const std::string ConfigurationManager::TCP_TO_UDP = "tcp_to_udp";

//const std::string ConfigurationManager::RECONNECT_TIME_PARAMETER_NAME = "ReconnectInterval(millisecond)";
//const std::string ConfigurationManager::LOG_TO_CONSOLE_PARAMETER_NAME = "LogToConsole";

ConfigurationManager::ConfigurationManager(): logState_( false), udpToTcp_( true), tcpToUdp_( false)
{
}

ConfigurationManager::~ConfigurationManager()
{
}

boost::property_tree::ptree ConfigurationManager::readFromFile()
{
//	std::string path = CONFIG_DIR;
//	path += CONFIG_NAME;
	std::ifstream configFile( CONFIG_NAME.c_str(), std::ifstream::in);
//
	boost::property_tree::ptree root;
	boost::property_tree::ptree array;
	boost::property_tree::ptree part;
//
	try
	{
		boost::property_tree::json_parser::read_json( configFile, root);
		root.get_child( DIRECTIONS_PARAMETER_NAME);
//
//		root.get_child( UDP_PARAMETER_NAME).get_child( PARTNER_IP_PARAMETER_NAME);
//		root.get_child( UDP_PARAMETER_NAME).get_child( PORT_FOR_WRITE_PARAMETER_NAME);
//		root.get_child( UDP_PARAMETER_NAME).get_child( PORT_FOR_READ_PARAMETER_NAME);
//
//		udpToTcp_ = root.get_child( TRAFFIC_DIRECTION_PARAMETER_NAME).get_child( UDP_TO_TCP).get_value<std::string>() != "0";
//		tcpToUdp_ = root.get_child( TRAFFIC_DIRECTION_PARAMETER_NAME).get_child( TCP_TO_UDP).get_value<std::string>() != "0";
//
//		root.get_child( RECONNECT_TIME_PARAMETER_NAME);
//		logState_ = root.get_child( LOG_TO_CONSOLE_PARAMETER_NAME).get_value<std::string>() != "0";
	}

	catch( std::exception& e)
	{
		std::cout << e.what() << std::endl;
		root.clear();
//
//		part.clear();
//		part.add_child( PARTNER_IP_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_PARTNER_IP));
//		part.add_child( PORT_FOR_WRITE_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_PORT_FOR_WRITE));
//		part.add_child( PORT_FOR_READ_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_PORT_FOR_READ));
//		root.push_back( std::make_pair( UDP_PARAMETER_NAME, part));
//
		array.clear();
		part.clear();
		part.add_child( PARTNER_IP_PARAMETER_NAME, boost::property_tree::ptree( "192.168.0.99"));
		part.add_child( "Port", boost::property_tree::ptree( "34000"));
		array.push_back( std::make_pair("", part));
		part.clear();
		part.add_child( PARTNER_IP_PARAMETER_NAME, boost::property_tree::ptree( "192.168.0.100"));
		part.add_child( "Port", boost::property_tree::ptree( "34000"));
		array.push_back( std::make_pair("", part));
		root.add_child( DIRECTIONS_PARAMETER_NAME, array);
//
//		part.clear();
//		part.add_child( UDP_TO_TCP, boost::property_tree::ptree( "1"));
//		part.add_child( TCP_TO_UDP, boost::property_tree::ptree( "0"));
//		root.push_back( std::make_pair( TRAFFIC_DIRECTION_PARAMETER_NAME, part));
//
//		root.add_child( RECONNECT_TIME_PARAMETER_NAME, boost::property_tree::ptree( "100"));
//		root.add_child( LOG_TO_CONSOLE_PARAMETER_NAME, boost::property_tree::ptree( "1"));
//		logState_ = true;
//
//		writeToFile( root);
	}

	return root;
}

void ConfigurationManager::writeToFile( const boost::property_tree::ptree& root)
{
	std::ofstream configFile;
//	std::string path = CONFIG_DIR;
//	path += CONFIG_NAME;
	configFile.open( CONFIG_NAME.c_str(), std::ofstream::trunc | std::ofstream::out);
	boost::property_tree::json_parser::write_json( configFile, root);
	configFile.close();
}

bool ConfigurationManager::isLogging()
{
	return logState_;
}

bool ConfigurationManager::isUdpToTcp()
{
	return udpToTcp_;
}

bool ConfigurationManager::isTcpToUdp()
{
	return tcpToUdp_;
}

} /* namespace configuration */
