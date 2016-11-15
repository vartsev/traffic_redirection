#ifndef TRAFFICDIRECTION_H_
#define TRAFFICDIRECTION_H_

#include "connectiondata.h"
#include <list>

namespace network
{

typedef std::list< ConnectionData> ConnectionDataList;

class TrafficDirection
{
public:
	TrafficDirection( const ConnectionData& source);
	~TrafficDirection();

	const ConnectionData& getSource() const;
	const ConnectionDataList& getDistinationList() const;

	void addDistination( const ConnectionData& distination);
	void deleteDistination( const ConnectionData& distination);

private:
	ConnectionData source_;
	ConnectionDataList distinationList_;
};

typedef std::list<TrafficDirection> TrafficDirectionList;

} /* namespace configuration */

#endif /* TRAFFICDIRECTION_H_ */
