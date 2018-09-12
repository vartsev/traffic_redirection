#include "presenter.h"

namespace presenter
{

Presenter::Presenter( view::IView& view):
		view_( view),
		manager_( std::bind( &Presenter::handleSending,
				this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
{
	manager_.initByConfig();
}

Presenter::~Presenter()
{

}

bool Presenter::handleSending( const model::Connection& connection,
						bool state, const std::string& packet)
{
	return true;
}

} /* namespace presenter */
