#include <iostream>
#include <string>
#include <QApplication>
#include <QPushButton>
#include "test.h"

using	namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton hello("Hello world!");

    hello.show();
    return app.exec();
}
