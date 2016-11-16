#include "trafficdirection.h"

namespace network
{

TrafficDirection::TrafficDirection( uint16_t id, const Connection& source) : id_( id), source_( source)
{}

TrafficDirection::~TrafficDirection()
{}

uint16_t TrafficDirection::getId() const
{
	return id_;
}

const Connection& TrafficDirection::getSource() const
{
	return source_;
}

const ConnectionList& TrafficDirection::getDistinationList() const
{
	return distinationList_;
}

void TrafficDirection::addDistination( const Connection& distination)
{
	distinationList_.push_back( distination);
}

void TrafficDirection::deleteDistination( const Connection& distination)
{
	distinationList_.remove( distination);
}

bool TrafficDirection::operator==( const TrafficDirection& right)
{
	return (id_ == right.getId()) ? true : false;
}

} /* namespace network */
