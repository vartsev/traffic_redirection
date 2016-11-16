#ifndef TRAFFICDIRECTION_H_
#define TRAFFICDIRECTION_H_

#include "connection.h"
#include <list>

namespace network
{

typedef std::list< Connection> ConnectionList;

class TrafficDirection
{
public:
	TrafficDirection( uint16_t id, const Connection& source);
	~TrafficDirection();

	uint16_t getId() const;

	const Connection& getSource() const;
	const ConnectionList& getDistinationList() const;

	void addDistination( const Connection& distination);
	void deleteDistination( const Connection& distination);

	bool operator==( const TrafficDirection& right);

private:
	uint16_t id_;
	Connection source_;
	ConnectionList distinationList_;
};

typedef std::list<TrafficDirection> TrafficDirectionList;

} /* namespace configuration */

#endif /* TRAFFICDIRECTION_H_ */
