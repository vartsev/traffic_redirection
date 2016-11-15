#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include "configurationkeeper.h"

namespace configuration
{

class ConfigurationManager
{
public:
	ConfigurationManager();
	~ConfigurationManager();

	bool getLoggingToFileState();
	void saveLoggingToFileState( bool state);

	bool getLoggingToConsoleState();
	void saveLoggingToConsoleState( bool state);

	uint16_t getReconnectionInterval();
	void saveReconnectionInterval( uint16_t inerval);

private:
	ConfigurationKeeper configurationKeeper_;
};

} /* namespace configuration */

#endif /* CONFIGURATIONMANAGER_H_ */
