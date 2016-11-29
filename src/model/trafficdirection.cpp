#include "trafficdirection.h"

#include <boost/bind.hpp>

namespace model
{

TrafficDirection::TrafficDirection( const Connection& source) : source_( source)
{
	source_.setHandlerPacket( boost::bind( &TrafficDirection::handlePacket, this, _1));
}

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
	for( ConnectionList::const_iterator it = distinationList_.begin();
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

bool TrafficDirection::handlePacket( const std::string& packet)
{
	for( ConnectionList::iterator itDistination = distinationList_.begin()
				; itDistination!= distinationList_.end(); ++itDistination)
	{
		itDistination->sendPacket( packet);
	}

	return true;
}

bool TrafficDirection::operator==( const TrafficDirection& right) const
{
	bool result = ( source_ == right.getSource());

	if( !result)
		return false;

	for( ConnectionList::const_iterator itDistination = distinationList_.begin()
			; itDistination != distinationList_.end(); ++itDistination)
	{
		bool isSame = false;
		for( ConnectionList::const_iterator it = right.getDistinationSet().begin();
				it != right.getDistinationSet().end(); ++it)
		{
			if(	*itDistination == *it)
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

} /* namespace model */
