#include <QtGui/QApplication>
#include "mainwindowimpl.h"
#include <QDebug>
//
int main(int argc, char * argv[])
{
	QApplication a( argc, argv );
	MainWindowImpl win;
	win.showMaximized();
	
	return a.exec();
}
