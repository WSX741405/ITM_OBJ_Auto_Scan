#include "UI/OBJMainWindow.h"
#include <QtWidgets/QApplication>

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}