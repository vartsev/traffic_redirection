#ifndef CONNECTIONDATA_H_
#define CONNECTIONDATA_H_

#include<string>
#include<stdint.h>

namespace network
{

class ConnectionData
{
public:
	ConnectionData( const std::string& protocol, const std::string& ip, uint16_t port);
	~ConnectionData();

	const std::string& getPtotocol() const;
	const std::string& getIp() const;
	const uint16_t getPort() const;

	bool operator==(const ConnectionData& right);

private:
	std::string protocol_;
	std::string ip_;
	uint16_t port_;
};

} /* namespace network */

#endif /* CONNECTIONDATA_H_ */
