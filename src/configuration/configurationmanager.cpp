#include "configurationmanager.h"

#include <boost/lexical_cast.hpp>
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
const std::string ConfigurationManager::ID_PARAMETER_NAME = "Id";
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

ConfigurationManager::ConfigurationManager():
		logToFile_( false),
		logToConsole_( true),
		reconnectionInterval_( 100),
		configPath_( getConfigPath())
{
	readFromFile( configPath_);
}

ConfigurationManager::~ConfigurationManager()
{
}

const boost::property_tree::ptree& ConfigurationManager::readFromFile( const std::string& configPath)
{
	std::ifstream configFile;
	{
		boost::lock_guard<boost::mutex> lock( mutex_);
		configFile.open( configPath.c_str(), std::ifstream::in);
	}

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

		boost::property_tree::ptree part;
		configurationTree_.add_child( DIRECTIONS_PARAMETER_NAME, part);

		writeToFile( configurationTree_);
	}

	return configurationTree_;
}

void ConfigurationManager::saveConfiguration( const boost::property_tree::ptree& configurationTree)
{
	if( writeToFile( configurationTree))
		configurationTree_ = configurationTree;
}

bool ConfigurationManager::writeToFile( const boost::property_tree::ptree& configurationTree)
{
	boost::lock_guard<boost::mutex> lock( mutex_);

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

boost::property_tree::ptree& ConfigurationManager::getConfigurationTree()
{
	return configurationTree_;
}

bool ConfigurationManager::isLoggingToFile()
{
	return logToFile_;
}

bool ConfigurationManager::isLoggingToConsole()
{
	return logToConsole_;
}

void ConfigurationManager::saveLoggingToFileState( bool state)
{
	configurationTree_.get_child( configuration::ConfigurationManager::LOG_TO_FILE_PARAMETER_NAME).
					put_value<std::string>( boost::lexical_cast<std::string>( state));

	writeToFile( configurationTree_);
}

void ConfigurationManager::saveLoggingToConsoleState( bool state)
{
	configurationTree_.get_child( configuration::ConfigurationManager::LOG_TO_CONSOLE_PARAMETER_NAME).
					put_value<std::string>( boost::lexical_cast<std::string>( state));

	writeToFile( configurationTree_);
}

uint16_t ConfigurationManager::getReconnectionInterval()
{
	return reconnectionInterval_;
}

void ConfigurationManager::saveReconnectionInterval( uint16_t inerval)
{
	configurationTree_.get_child( configuration::ConfigurationManager::RECONNECT_INTERVAL_PARAMETER_NAME).
					put_value<std::string>( boost::lexical_cast<std::string>( inerval));

	writeToFile( configurationTree_);
}

void ConfigurationManager::updateTrafficDirection( const network::TrafficDirectionList& trafficDirectionList)
{
	boost::property_tree::ptree array;
	boost::property_tree::ptree arr;
	boost::property_tree::ptree part;
	boost::property_tree::ptree prt;

	for( network::TrafficDirectionList::const_iterator itTraffic = trafficDirectionList.begin();
			itTraffic != trafficDirectionList.end(); ++itTraffic)
	{
		prt.clear();
		prt.add_child( PROTOCOL_PARAMETER_NAME, boost::property_tree::ptree( itTraffic->getSource().getPtotocol()));
		prt.add_child( IP_PARAMETER_NAME, boost::property_tree::ptree( itTraffic->getSource().getIp()));
		prt.add_child( PORT_PARAMETER_NAME, boost::property_tree::ptree( boost::lexical_cast<std::string>( itTraffic->getSource().getPort())));

		part.clear();
		part.add_child( ID_PARAMETER_NAME, boost::property_tree::ptree( boost::lexical_cast<std::string>( itTraffic->getId())));
		part.add_child( SRC_PARAMETER_NAME, prt);

		arr.clear();
		{
			for( network::ConnectionList::const_iterator itDistination = itTraffic->getDistinationList().begin();
					itDistination != itTraffic->getDistinationList().end(); ++itDistination)
			{
				prt.clear();

				prt.add_child( PROTOCOL_PARAMETER_NAME, boost::property_tree::ptree( itDistination->getPtotocol()));
				prt.add_child( IP_PARAMETER_NAME, boost::property_tree::ptree( itDistination->getIp()));
				prt.add_child( PORT_PARAMETER_NAME, boost::property_tree::ptree( boost::lexical_cast<std::string>( itDistination->getPort())));

				arr.push_back( std::make_pair( "", prt));
			}
		}

		part.add_child( DST_PARAMETER_NAME, arr);

		array.push_back( std::make_pair("", part));

	}

	configurationTree_.put_child( DIRECTIONS_PARAMETER_NAME, array);
	writeToFile( configurationTree_);
}

std::string ConfigurationManager::getConfigPath()
{
	std::string path( std::getenv( "HOME"));
	path += CONFIG_PATH;
	if( !boost::filesystem::exists( path))
		boost::filesystem::create_directories( path);
	return path + CONFIG_NAME;
}

} /* namespace configuration */
