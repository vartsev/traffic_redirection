#ifndef PRESENTER_H_
#define PRESENTER_H_

#include "view/iview.h"
#include "model/trafficdirectionmanager.h"

namespace presenter
{

class Presenter
{
public:
	Presenter( view::IView& view);
	~Presenter();

private:
	bool handleSending( const model::Connection&, bool, const std::string&);

private:
	view::IView& view_;
	model::TrafficDirectionManager manager_;
};

} /* namespace presenter */

#endif /* PRESENTER_H_ */
