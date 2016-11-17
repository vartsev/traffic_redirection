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

const ConnectionList& TrafficDirection::getDistinationSet() const
{
	return distinationList_;
}

void TrafficDirection::addDistination( const Connection& distination)
{
	bool isSame = false;
	for( ConnectionList::iterator it = distinationList_.begin();
			it!= distinationList_.end(); ++it)
	{
		if( distination == *it)
			isSame = true;
	}

	if( !isSame)
		distinationList_.push_back( distination);
}

void TrafficDirection::deleteDistination( const Connection& distination)
{
	distinationList_.remove( distination);
}

bool TrafficDirection::operator==( const TrafficDirection& right) const
{
	bool result = ( source_ == right.getSource());

	if( !result)
		return false;

	for( ConnectionList::const_iterator itTraffic = distinationList_.begin()
			; itTraffic != distinationList_.end(); ++itTraffic)
	{
		bool isSame = false;
		for( ConnectionList::const_iterator it = right.getDistinationSet().begin();
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

} /* namespace network */
