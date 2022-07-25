#include <QtWidgets>
#include <QtGui>
#include <iostream>
#include "class.h"
#include "lcdwidget.h"
#include "cannonfield.h"


using namespace std;

GameBoard::GameBoard(QWidget *parent)
:	QWidget(parent),
	hits(NULL),
	shots_left(NULL),
	cannonfield(NULL),
	angle(NULL),
	force(NULL)
{	
	setMinimumSize(500, 400);
	QPushButton *quit=new QPushButton("Quit");
	quit->setFont(QFont("Times", -1, QFont::Bold));
	
	QPushButton *shoot=new QPushButton("Shoot");
	shoot->setFont(QFont("Times", -1, QFont::Bold));
	
	QPushButton *restart=new QPushButton("New Game");
	restart->setFont(QFont("Times", -1, QFont::Bold));
	
	connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(restart, SIGNAL(clicked()), this, SLOT(newGame()));

	angle=new LCDWidget("RANGE");
	angle->setRange(5, 70);
	
	force=new LCDWidget("FORCE");
	force->setRange(10, 70);
	
	hits=new QLCDNumber(2);
	hits->setSegmentStyle(QLCDNumber::Filled);
	
	shots_left=new QLCDNumber(2);
	shots_left->setSegmentStyle(QLCDNumber::Filled);
	
	QLabel *hits_label=new QLabel("HITS");
	QLabel *shots_left_label=new QLabel("SHOTS LEFT");
	
	cannonfield= new Cannonfield;
	
	connect(angle, SIGNAL(valueChanged(int)), cannonfield, SLOT(setAngle(int)));
	connect(cannonfield, SIGNAL(angleChanged(int)), angle, SLOT(setValue(int)));
	
	connect(force, SIGNAL(valueChanged(int)), cannonfield, SLOT(setForce(int)));
	connect(cannonfield, SIGNAL(forceChanged(int)), force, SLOT(setValue(int)));

	connect(cannonfield, SIGNAL(hit()), this, SLOT(hit()));
	connect(cannonfield, SIGNAL(missed()), this, SLOT(missed()));
	
	connect(shoot, SIGNAL(clicked()), this, SLOT(fire()));
	connect(cannonfield, SIGNAL(canShoot(bool)), shoot, SLOT(setEnabled(bool)));
	
	QHBoxLayout * hbox=new QHBoxLayout;
	hbox->addWidget(shoot);
	hbox->addWidget(hits);
	hbox->addWidget(hits_label);
	hbox->addWidget(shots_left);
	hbox->addWidget(shots_left_label);
	hbox->addStretch(1);
	hbox->addWidget(restart);
	
	
	QVBoxLayout *left_layout=new QVBoxLayout;
	left_layout->addWidget(angle);
	left_layout->addWidget(force);
		
	QGridLayout *grid_layout=new QGridLayout;
	grid_layout->addWidget(quit, 0, 0);
	grid_layout->addLayout(left_layout, 1, 0);
	grid_layout->addLayout(hbox, 0, 1);
	grid_layout->addWidget(cannonfield, 1,1, 2, 1);
	grid_layout->setColumnStretch(1, 10);
	
	angle->setValue(60);
	
	force->setValue(25);
	
	setLayout(grid_layout);
	
	setFocusPolicy(Qt::StrongFocus);
	setFocus();
	
	newGame();	
}

void GameBoard::keyPressEvent(QKeyEvent *event)
{
	switch(event->modifiers())
	{
		case Qt::ControlModifier:
			switch(event->key())
			{
				case Qt::Key_N:
					newGame();
					break;
			}
			break;
		
		case Qt::NoModifier:
			switch(event->key())
			{
				case Qt::Key_Up:
					force->setValue(force->value()+1);
					break;
				
				case Qt::Key_Down:
					force->setValue(force->value()-1);
					break;
				
				case Qt::Key_Left:
					angle->setValue(angle->value()-1);
					break;
				
				case Qt::Key_Right:
					angle->setValue(angle->value()+1);
					break;
					
				case Qt::Key_Return:
					fire();
					break;
			}
			break;		
	}
}

void GameBoard::fire()
{
	if (cannonfield->isGameOver() or cannonfield->isShooting())
		return;
	
	shots_left->display(shots_left->intValue()-1);
	cannonfield->shoot();
}

void GameBoard::hit()
{
	hits->display(hits->intValue()+1);
	
	if (shots_left->intValue()==0)
	{
		if (hits->intValue()==15)
		{
			cannonfield->setVictory();
		}
		else
		{
			cannonfield->setDefeat();
		}
		
		cannonfield->setGameOver();	
	}
	
	else
		cannonfield->newTarget();
		emit cannonfield->canShoot(true);
}

void GameBoard::missed()
{
	if (shots_left->intValue()==0)
	{
		cannonfield->setDefeat();
		cannonfield->setGameOver();	
	}
	
	else
		emit cannonfield->canShoot(true);
}

void GameBoard::newGame()
{
	shots_left->display(15);
	hits->display(0);
	cannonfield->restartGame();
	cannonfield->newTarget();
}
