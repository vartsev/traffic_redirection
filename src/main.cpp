#include "network/networkmanager.h"
#include "configuration/configurationmanager.h"

int main( int argc, char* argv[])
{
	configuration::ConfigurationManager configurationManager;

	std::cout << "interval: " << configurationManager.getReconnectionInterval() << std::endl;
	configurationManager.saveLoggingToFileState( true);
	configurationManager.saveLoggingToConsoleState( true);
	configurationManager.saveReconnectionInterval( 500);

//	network::NetworkManager networkManager;

	while(true)
	{
		sleep( 10);
	}
	return true;
}
