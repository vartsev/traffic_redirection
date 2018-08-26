#include <QtCore>
#include <QtGui>

#include "view/mainwindow.h"
#include "model/trafficdirectionmanager.h"
#include "presenter/presenter.h"
#include "configuration/configurationmanager.h"

#include <iostream>

int main( int argc, char* argv[])
{
	model::TrafficDirectionManager manager;

	QApplication app(argc, argv);
	view::MainWindow mainWindow;
	return app.exec();
}
