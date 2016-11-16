#ifndef TRAFFICDIRECTION_H_
#define TRAFFICDIRECTION_H_

#include "connection.h"
#include <list>

namespace network
{

typedef std::set< Connection> ConnectionSet;

class TrafficDirection
{
public:
	TrafficDirection( const Connection& source);
	~TrafficDirection();

	const Connection& getSource() const;
	const ConnectionSet& getDistinationSet() const;

	void addDistination( const Connection& distination);
	void deleteDistination( const Connection& distination);

	bool operator==( const TrafficDirection& right) const;
	bool operator<( const TrafficDirection& right) const;

private:
	Connection source_;
	ConnectionSet distinationSet_;
};

typedef std::set<TrafficDirection> TrafficDirectionSet;

} /* namespace configuration */

#endif /* TRAFFICDIRECTION_H_ */
