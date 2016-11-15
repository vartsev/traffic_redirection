#include "trafficdirection.h"

namespace network
{

TrafficDirection::TrafficDirection( const ConnectionData& source) : source_( source)
{}

TrafficDirection::~TrafficDirection()
{}

const ConnectionData& TrafficDirection::getSource() const
{
	return source_;
}

const ConnectionDataList& TrafficDirection::getDistinationList() const
{
	return distinationList_;
}

void TrafficDirection::addDistination( const ConnectionData& distination)
{
	distinationList_.push_back( distination);
}

void TrafficDirection::deleteDistination( const ConnectionData& distination)
{
	distinationList_.remove( distination);
}

} /* namespace network */
