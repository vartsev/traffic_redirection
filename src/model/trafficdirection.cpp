#include "trafficdirection.h"

#include <boost/bind.hpp>

namespace model
{

TrafficDirection::TrafficDirection( const ConnectionPtr source) : source_( source)
{}

TrafficDirection::~TrafficDirection()
{}

const ConnectionPtr TrafficDirection::getSource() const
{
	return source_;
}

const ConnectionList& TrafficDirection::getDistinationList() const
{
	return distinationList_;
}

void TrafficDirection::addDistination( const ConnectionPtr distination)
{
	bool isSame = false;
	for( auto& dist : distinationList_)
	{
		if( distination == dist)
			isSame = true;
	}

	if( !isSame)
	{
		distinationList_.push_back( distination);
	}
}

void TrafficDirection::deleteDistination( const ConnectionPtr distination)
{
	for( auto& dist : distinationList_)
	{
		if( distination == dist)
		{
			distinationList_.remove( dist);
			return;
		}
	}

}

bool TrafficDirection::handlePacket( const std::string& packet)
{
	for( auto& distination : distinationList_)
	{
		distination->sendPacket( packet);
	}

	return true;
}

bool TrafficDirection::operator==( const TrafficDirection& right) const
{
	bool result = ( source_ == right.getSource());

	if( !result)
		return false;

	for( auto& distination : distinationList_)
	{
		bool isSame = false;
		for( auto& it : right.getDistinationList())
		{
			if(	distination == it)
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

void TrafficDirection::activate( const SendingResult& callback)
{
	source_->activate();
	source_->setHandlerPacket( std::bind( &TrafficDirection::handlePacket, this, std::placeholders::_1));
	for( auto& distination : distinationList_)
	{
		distination->activate();
		distination->setSendingResult( callback);
	}
}

bool TrafficDirection::deactivate()
{
	bool result = true;
	source_->deactivate();
	for( auto& distination : distinationList_)
	{
		result = result && distination->deactivate();
	}

	return result;
}

} /* namespace model */
