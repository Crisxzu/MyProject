#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "test.h"

using	namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QPushButton hello("Hello world!");
	hello.resize(200, 200);

	QObject::connect(&hello, SIGNAL(clicked()), &app, SLOT(quit()));
	hello.show();
	return app.exec();
}
