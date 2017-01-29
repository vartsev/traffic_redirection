#include <QtCore>
#include <QtGui>

#include "userinterface/mainwindow.h"
#include "model/trafficdirectionmanager.h"
#include "configuration/configurationmanager.h"

int main( int argc, char* argv[])
{
	model::TrafficDirectionManager manager;

	QApplication app(argc, argv);
	userinterface::MainWindow mainWindow;
	return app.exec();
}
