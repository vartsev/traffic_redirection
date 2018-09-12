#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "view/iview.h"
#include <QObject>
#include <QMainWindow>
#include <QPushButton>

namespace view
{

class MainWindow : public QMainWindow, public IView
{
	Q_OBJECT

public:
	explicit MainWindow( QWidget *parent = 0);
	~MainWindow();

private slots:
	 void handleClickButton();

private:
	QPushButton* button_;
};

} /* namespace userinterface */

#endif /* MAINWINDOW_H_ */
