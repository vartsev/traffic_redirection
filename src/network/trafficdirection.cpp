#include "trafficdirection.h"

namespace network
{

TrafficDirection::TrafficDirection( const Connection& source) : source_( source)
{}

TrafficDirection::~TrafficDirection()
{}

const Connection& TrafficDirection::getSource() const
{
	return source_;
}

const ConnectionSet& TrafficDirection::getDistinationSet() const
{
	return distinationSet_;
}

void TrafficDirection::addDistination( const Connection& distination)
{
	distinationSet_.insert( distination);
}

void TrafficDirection::deleteDistination( const Connection& distination)
{
	distinationSet_.erase( distination);
}

bool TrafficDirection::operator==( const TrafficDirection& right) const
{
	bool result = ( source_ == right.getSource());

	if( !result)
		return false;

	for( ConnectionSet::const_iterator itTraffic = distinationSet_.begin()
			; itTraffic != distinationSet_.end(); ++itTraffic)
	{
		bool isSame = false;
		for( ConnectionSet::const_iterator it = right.getDistinationSet().begin();
				it != right.getDistinationSet().end(); ++it)
		{
			if(	*itTraffic == *it)
			{
				isSame = true;
				break;
			}
		}

		result = result && isSame;

		if( !result)
			return false;
	}

	return result;
}

bool TrafficDirection::operator<( const TrafficDirection& right) const
{
	if( source_.getPort() <= right.getSource().getPort() && !(*this == right))
		return true;

	return false;

//	return source_ < right.getSource();
}

} /* namespace network */
