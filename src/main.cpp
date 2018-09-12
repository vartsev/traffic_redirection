#include <QtCore>
#include <QtGui>

#include "view/mainwindow.h"
#include "model/trafficdirectionmanager.h"
#include "presenter/presenter.h"

#include <iostream>

int main( int argc, char* argv[])
{
	QApplication app(argc, argv);
	view::MainWindow mainWindow;

	presenter::Presenter presenter( mainWindow);
	return app.exec();
}
