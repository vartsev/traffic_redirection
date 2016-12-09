#ifndef TRAFFICDIRECTION_H_
#define TRAFFICDIRECTION_H_

#include "connection.h"

namespace model
{

class TrafficDirection
{
public:
	TrafficDirection( const ConnectionPtr source);
	~TrafficDirection();

	const ConnectionPtr getSource() const;
	const ConnectionList& getDistinationSet() const;

	void addDistination( const ConnectionPtr distination);
	void deleteDistination( const ConnectionPtr distination);

	bool operator==( const TrafficDirection& right) const;

private:
	bool handlePacket( const std::string& packet);

private:
	ConnectionPtr source_;
	ConnectionList distinationList_;
	std::list< int> testList_;
};
//typedef std::unique_ptr<TrafficDirection>
typedef std::shared_ptr<TrafficDirection> TrafficDirectionPtr;
typedef std::list<TrafficDirectionPtr> TrafficDirectionList;

} /* namespace model */

#endif /* TRAFFICDIRECTION_H_ */
