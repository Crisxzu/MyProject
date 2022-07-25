#include <QtWidgets>
#include <QtGui>
#include "class.h"



int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QEventLoop loop(app);
	GameBoard gameboard;
	
	gameboard.show();	
		
	loop.exec();
	return 0;
}
