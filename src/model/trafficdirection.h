#ifndef TRAFFICDIRECTION_H_
#define TRAFFICDIRECTION_H_

#include "connection.h"

namespace model
{

class TrafficDirection
{
public:
	TrafficDirection( const Connection& source);
	~TrafficDirection();

	const Connection& getSource() const;
	const ConnectionList& getDistinationSet() const;

	void addDistination( const Connection& distination);
	void deleteDistination( const Connection& distination);

	bool operator==( const TrafficDirection& right) const;

private:
	bool handlePacket( const std::string& packet);

private:
	Connection source_;
	ConnectionList distinationList_;
};

typedef std::list<TrafficDirection> TrafficDirectionList;

} /* namespace model */

#endif /* TRAFFICDIRECTION_H_ */