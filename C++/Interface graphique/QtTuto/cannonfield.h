#ifndef DEF_CANNONFIELD
#define DEF_CANNONFIELD

#include <QtWidgets>
#include <QtGui>


class Cannonfield : public QWidget
{
	Q_OBJECT
	
	protected:
		int current_angle;
		int current_force;
		int timer_count;
		QTimer *auto_shoot_timer;
		float shoot_angle;
		float shoot_force;		
		QPoint target;
		bool f_game_is_ended;
		bool f_victory;
		bool f_defeat;		
					
	public:
		Cannonfield(QWidget *parent=0);
		
		//Fonctions membres	
		int angle() const
		{
			return current_angle;
		}
		
		int force() const
		{
			return current_force;
		}
		
		bool isGameOver() const
		{
			return f_game_is_ended;
		}
		
		bool isShooting() const;
			
	public slots:
		void setAngle(int angle);
		void setForce(int force);
		void moveShot();
		void shoot();
		void newTarget();
		void setGameOver();
		void restartGame();
		void setVictory();
		void setDefeat();
		
	signals:
		void angleChanged(int newAngle);
		void forceChanged(int newForce);
		void hit();
		void missed();
		void canShoot(bool can);
		
	protected:
		void paintEvent(QPaintEvent *event);
		
	private:
		QRect cannonRect() const;
		QRect shotRect() const;
		QRect targetRect() const;
		void paintShot(QPainter &painter);
		void paintCannon(QPainter &painter);
		void paintTarget(QPainter &painter);	
};

#endif /*CANNONFIELD*/

