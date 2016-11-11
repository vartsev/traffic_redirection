#include "configurationmanager.h"

#include <boost/filesystem/operations.hpp>
#include <fstream>

namespace configuration
{

const std::string ConfigurationManager::CONFIG_PATH = "/traffic_redirection/";
const std::string ConfigurationManager::CONFIG_NAME = "config.txt";

const std::string ConfigurationManager::LOG_TO_FILE_PARAMETER_NAME = "LoggingToFile";
const std::string ConfigurationManager::LOG_TO_CONSOLE_PARAMETER_NAME = "LoggingToConsole";
const std::string ConfigurationManager::RECONNECT_INTERVAL_PARAMETER_NAME = "ReconnectionInterval(millisecond)";

const std::string ConfigurationManager::DIRECTIONS_PARAMETER_NAME = "Directions";
const std::string ConfigurationManager::SRC_PARAMETER_NAME = "Source";
const std::string ConfigurationManager::DST_PARAMETER_NAME = "Destinations";

const std::string ConfigurationManager::PROTOCOL_PARAMETER_NAME = "Protocol";
const std::string ConfigurationManager::IP_PARAMETER_NAME = "Ip";
const std::string ConfigurationManager::PORT_PARAMETER_NAME = "Port";

const std::string ConfigurationManager::UDP_PARAMETER_NAME = "udp";
const std::string ConfigurationManager::TCP_CLIENT_PARAMETER_NAME = "tcp_client";
const std::string ConfigurationManager::TCP_SERVER_PARAMETER_NAME = "tcp_server";

const std::string ConfigurationManager::DEFAULT_IP = "127.0.0.1";
const std::string ConfigurationManager::DEFAULT_PORT = "44000";
const std::string ConfigurationManager::DEFAULT_INTERVAL = "100";
const std::string ConfigurationManager::DEFAULT_LOGGING = "0";

ConfigurationManager::ConfigurationManager(): logToFile_( false), logToConsole_( true)
{
}

ConfigurationManager::~ConfigurationManager()
{
}

boost::property_tree::ptree ConfigurationManager::readFromFile()
{
	std::string path = getConfigPath() + CONFIG_NAME;
	std::ifstream configFile( path.c_str(), std::ifstream::in);

	boost::property_tree::ptree root;
	boost::property_tree::ptree array;
	boost::property_tree::ptree part;

	try
	{
		boost::property_tree::json_parser::read_json( configFile, root);

		logToFile_ = root.get_child( LOG_TO_FILE_PARAMETER_NAME).get_value<std::string>() != "0";
		logToConsole_ = root.get_child( LOG_TO_CONSOLE_PARAMETER_NAME).get_value<std::string>() != "0";
		root.get_child( RECONNECT_INTERVAL_PARAMETER_NAME);
		root.get_child( DIRECTIONS_PARAMETER_NAME);
	}

	catch( std::exception& e)
	{
		std::cout << e.what() << std::endl;
		root.clear();

		root.add_child( LOG_TO_FILE_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_LOGGING));
		root.add_child( LOG_TO_CONSOLE_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_LOGGING));
		root.add_child( RECONNECT_INTERVAL_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_INTERVAL));

		array.clear();
		part.clear();
		part.add_child( SRC_PARAMETER_NAME, boost::property_tree::ptree( "192.168.0.99"));
		part.add_child( DST_PARAMETER_NAME, boost::property_tree::ptree( "34000"));
		array.push_back( std::make_pair("", part));
		part.clear();
		part.add_child( SRC_PARAMETER_NAME, boost::property_tree::ptree( "192.168.0.100"));
		part.add_child( DST_PARAMETER_NAME, boost::property_tree::ptree( "34000"));
		array.push_back( std::make_pair("", part));
		root.add_child( DIRECTIONS_PARAMETER_NAME, array);

		writeToFile( root);
	}

	return root;
}

void ConfigurationManager::writeToFile( const boost::property_tree::ptree& root)
{
	std::ofstream configFile;
	std::string path = getConfigPath() + CONFIG_NAME;
	configFile.open( path.c_str(), std::ofstream::trunc | std::ofstream::out);
	boost::property_tree::json_parser::write_json( configFile, root);
	configFile.close();
}

bool ConfigurationManager::isLoggingToFile()
{
	return logToFile_;
}

bool ConfigurationManager::isLoggingToConsole()
{
	return logToConsole_;
}

std::string ConfigurationManager::getConfigPath()
{
	std::string path( std::getenv( "HOME"));
	path += CONFIG_PATH;
	if( !boost::filesystem::exists( path))
		boost::filesystem::create_directories( path);
	return path;
}

} /* namespace configuration */
