#include "configurationkeeper.h"

#include <boost/filesystem/operations.hpp>
#include <fstream>

namespace configuration
{

const std::string ConfigurationKeeper::CONFIG_PATH = "/traffic_redirection/";
const std::string ConfigurationKeeper::CONFIG_NAME = "config.txt";

const std::string ConfigurationKeeper::LOG_TO_FILE_PARAMETER_NAME = "LoggingToFile";
const std::string ConfigurationKeeper::LOG_TO_CONSOLE_PARAMETER_NAME = "LoggingToConsole";
const std::string ConfigurationKeeper::RECONNECT_INTERVAL_PARAMETER_NAME = "ReconnectionInterval(millisecond)";

const std::string ConfigurationKeeper::DIRECTIONS_PARAMETER_NAME = "Directions";
const std::string ConfigurationKeeper::SRC_PARAMETER_NAME = "Source";
const std::string ConfigurationKeeper::DST_PARAMETER_NAME = "Destinations";

const std::string ConfigurationKeeper::PROTOCOL_PARAMETER_NAME = "Protocol";
const std::string ConfigurationKeeper::IP_PARAMETER_NAME = "Ip";
const std::string ConfigurationKeeper::PORT_PARAMETER_NAME = "Port";

const std::string ConfigurationKeeper::UDP_PARAMETER_NAME = "udp";
const std::string ConfigurationKeeper::TCP_CLIENT_PARAMETER_NAME = "tcp_client";
const std::string ConfigurationKeeper::TCP_SERVER_PARAMETER_NAME = "tcp_server";

const std::string ConfigurationKeeper::DEFAULT_IP = "127.0.0.1";
const std::string ConfigurationKeeper::DEFAULT_PORT = "44000";
const std::string ConfigurationKeeper::DEFAULT_INTERVAL = "100";
const std::string ConfigurationKeeper::DEFAULT_LOGGING = "0";

ConfigurationKeeper::ConfigurationKeeper():
		logToFile_( false),
		logToConsole_( true),
		reconnectionInterval_( 100),
		configPath_( getConfigPath())
{
	readFromFile( configPath_);
}

ConfigurationKeeper::~ConfigurationKeeper()
{
}

const boost::property_tree::ptree& ConfigurationKeeper::readFromFile( const std::string& configPath)
{
	std::ifstream configFile( configPath.c_str(), std::ifstream::in);

	boost::property_tree::ptree array;
	boost::property_tree::ptree arr;
	boost::property_tree::ptree part;
	boost::property_tree::ptree prt;

	try
	{
		boost::property_tree::json_parser::read_json( configFile, configurationTree_);

		logToFile_ = configurationTree_.get_child( LOG_TO_FILE_PARAMETER_NAME).get_value<std::string>() != "0";
		logToConsole_ = configurationTree_.get_child( LOG_TO_CONSOLE_PARAMETER_NAME).get_value<std::string>() != "0";
		reconnectionInterval_ = configurationTree_.get_child( RECONNECT_INTERVAL_PARAMETER_NAME).get_value<uint16_t>();
		configurationTree_.get_child( DIRECTIONS_PARAMETER_NAME);
	}

	catch( std::exception& e)
	{
		std::cout << e.what() << std::endl;
		configurationTree_.clear();

		configurationTree_.add_child( LOG_TO_FILE_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_LOGGING));
		configurationTree_.add_child( LOG_TO_CONSOLE_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_LOGGING));
		configurationTree_.add_child( RECONNECT_INTERVAL_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_INTERVAL));

		array.clear();
		part.clear();
		prt.clear();
		prt.add_child( PROTOCOL_PARAMETER_NAME, boost::property_tree::ptree( UDP_PARAMETER_NAME));
		prt.add_child( IP_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_IP));
		prt.add_child( PORT_PARAMETER_NAME, boost::property_tree::ptree( DEFAULT_PORT));
		part.add_child( SRC_PARAMETER_NAME, prt);

		arr.clear();
		arr.push_back( std::make_pair("", prt));
		part.add_child( DST_PARAMETER_NAME, arr);

		array.push_back( std::make_pair("", part));

		configurationTree_.add_child( DIRECTIONS_PARAMETER_NAME, array);

		writeToFile( configurationTree_);
	}

	return configurationTree_;
}

void ConfigurationKeeper::saveConfiguration( const boost::property_tree::ptree& configurationTree)
{
	if( writeToFile( configurationTree))
		configurationTree_ = configurationTree;
}

bool ConfigurationKeeper::writeToFile( const boost::property_tree::ptree& configurationTree)
{
	try
	{
		std::ofstream configFile;
		configFile.open( configPath_.c_str(), std::ofstream::trunc | std::ofstream::out);
		boost::property_tree::json_parser::write_json( configFile, configurationTree);
		configFile.close();
	}
	catch ( std::exception&)
	{
		return false;
	}

	return true;
}

boost::property_tree::ptree& ConfigurationKeeper::getConfigurationTree()
{
	return configurationTree_;
}

bool ConfigurationKeeper::isLoggingToFile()
{
	return logToFile_;
}

bool ConfigurationKeeper::isLoggingToConsole()
{
	return logToConsole_;
}

uint16_t ConfigurationKeeper::getReconnectionInterval()
{
	return reconnectionInterval_;
}

std::string ConfigurationKeeper::getConfigPath()
{
	std::string path( std::getenv( "HOME"));
	path += CONFIG_PATH;
	if( !boost::filesystem::exists( path))
		boost::filesystem::create_directories( path);
	return path + CONFIG_NAME;
}

} /* namespace configuration */
