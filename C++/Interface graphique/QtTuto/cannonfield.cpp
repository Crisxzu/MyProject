#include <QtWidgets>
#include <QtGui>
#include <cmath>
#include "cannonfield.h"

Cannonfield::Cannonfield(QWidget *parent)
:	QWidget(parent),
	current_angle(45),
	current_force(0),
	timer_count(0),
	auto_shoot_timer(NULL),
	shoot_angle(0),
	shoot_force(0),
	f_game_is_ended(false),
	f_victory(false),
	f_defeat(false)
{
	auto_shoot_timer= new QTimer(this);
	connect(auto_shoot_timer, SIGNAL(timeout()), this, SLOT(moveShot()));
	
	setPalette(QPalette(QColor("#debc19")));
	setAutoFillBackground(true);
	newTarget();
}

void Cannonfield::shoot()
{
	if (isShooting())
		return;
	
	timer_count=0;
	shoot_angle=current_angle;
	shoot_force=current_force;
	auto_shoot_timer->start(5);
	emit canShoot(false);
}

void Cannonfield::newTarget()
{
	target=QPoint(QRandomGenerator::global()->bounded(200, 390), QRandomGenerator::global()->bounded(35, 290));
	update();
}

void Cannonfield::setGameOver()
{
	if (f_game_is_ended)
		return;
		
	if (isShooting())
		auto_shoot_timer->stop();
	
	f_game_is_ended=true;
	update();
}

void Cannonfield::setVictory()
{
	f_victory=true;
}

void Cannonfield::setDefeat()
{
	f_defeat=true;
}

void Cannonfield::restartGame()
{
	if (isShooting())
		auto_shoot_timer->stop();
	
	f_game_is_ended=false;
	f_victory=false;
	f_defeat=false;
	update();
	emit canShoot(true);
}

void Cannonfield::setAngle(int angle)
{
	if (angle<5)
		angle=5;
	
	if (angle>70)
		angle=70;
	
	if (current_angle==angle)
		return;
	
	current_angle=angle;
	update(cannonRect());
	emit angleChanged(current_angle);
}

void Cannonfield::setForce(int force)
{
	if (force < 0)
		force=0;
	
	if (current_force==force)
		return;
	
	current_force=force;
	emit forceChanged(current_force);
}

void Cannonfield::moveShot()
{
	QRegion region= shotRect();
	timer_count++;
	
	QRect shotR= shotRect();
	
	if (shotR.intersects(targetRect()))
	{
		auto_shoot_timer->stop();
		emit hit();
	}
	
	else if (shotR.x() > width() or shotR.y() > height())
	{
		auto_shoot_timer->stop();
		emit missed();	
	}
	
	else
		region=region.united(shotR);
	
	update(region);
}

void Cannonfield::paintEvent(QPaintEvent * /* event */)
{
	QPainter painter(this);
	
	if (f_game_is_ended)
	{
		painter.setPen(Qt::black);
		painter.setFont(QFont("Courier", 48, QFont::Bold));
		painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
		
		if (f_victory)
		{
			painter.setPen(Qt::black);
			painter.setFont(QFont("Courier", 40, QFont::Bold));
			painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignBottom , "VICTORY");
		}
		
		else if (f_defeat)
		{
			painter.setPen(Qt::black);
			painter.setFont(QFont("Courier", 40, QFont::Bold));
			painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignBottom , "DEFEAT");
		}
	}
	
	paintCannon(painter);
	
	if (isShooting())
		paintShot(painter);
	
	if (!f_game_is_ended)
		paintTarget(painter);	
}

void Cannonfield::paintCannon(QPainter& painter)
{
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::blue);
	
	painter.save();
	painter.translate(0, rect().height());
	painter.drawPie(QRect(-35, -35, 70, 70), 0, 90 * 16);
	painter.rotate(-current_angle);
	painter.drawRect(QRect(30, -5, 20, 10));
	painter.restore();	
}

void Cannonfield::paintShot(QPainter& painter)
{
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::black);
	painter.drawRect(shotRect());
}

void Cannonfield::paintTarget(QPainter &painter)
{
	painter.setPen(Qt::black);
	painter.setBrush(Qt::red);
	painter.drawRect(targetRect());
}

QRect Cannonfield::cannonRect() const
{
	QRect result(0, 0, 50, 50);
	result.moveBottomLeft(rect().bottomLeft());
	return result;
}

QRect Cannonfield::shotRect() const
{
	const double gravity = 4;

	double time = timer_count / 20.0;
	double velocity = shoot_force;
	double radians = shoot_angle * 3.14159265 / 180;

	double velx = velocity * cos(radians);
	double vely = velocity * sin(radians);
	double x0 = cos(radians);
	double y0 = sin(radians);
	double x = x0 + velx * time;
	double y = y0 + vely * time - 0.5 * gravity * time * time;

	QRect result(0, 0, 6, 6);
	result.moveCenter(QPoint(qRound(x), height() - 1 - qRound(y)));
	return result;
}

QRect Cannonfield::targetRect() const
{
	QRect result(0, 0, 20, 10);
	result.moveCenter(QPoint(target.x(), height() -1 - target.y()));
	return result;
}

bool Cannonfield::isShooting() const
{
	return auto_shoot_timer->isActive();
}
