#include "mainwindow.h"

#include<iostream>
#include <QFileDialog>
#define ru QString::fromUtf8

namespace view
{

MainWindow::MainWindow( QWidget *parent)
{
	this->setWindowTitle( ru("Перенаправление трафика"));
	button_ = new QPushButton( ru("Кнопка"), this);
	button_->setGeometry( QRect( QPoint( 10, 10),
							QSize( 200, 50)));

	this->setMinimumSize( 800, 600);
 	this->showMaximized();

 	connect( button_, SIGNAL( released()), this, SLOT( handleClickButton()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleClickButton()
{

	QString map = QFileDialog::getOpenFileName( this, tr( "Map"), "/");

	std::cout << "handleClickButton " << map.toStdString() << std::endl;

}

} /* namespace userinterface */
