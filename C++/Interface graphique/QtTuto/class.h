#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QtWidgets>
#include <QtGui>

#include "cannonfield.h"
#include "lcdwidget.h"

class GameBoard : public QWidget
{
	Q_OBJECT
	
	protected:
		QLCDNumber *hits;
		QLCDNumber *shots_left;
		Cannonfield *cannonfield;
		LCDWidget *angle;
		LCDWidget *force;
	
	public:
   	GameBoard(QWidget *parent=0);
   
   protected slots:
   	void fire();
   	void hit();
   	void missed();
   	void newGame();
   
   protected:
   	void keyPressEvent(QKeyEvent *event);
};

#endif // GAMEBOARD_H
