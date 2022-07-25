#ifndef DEF_LCDWIDGET
#define DEF_LCDWIDGET

#include <QtWidgets>
#include <QtGui>

class LCDWidget : public QWidget
{	
	Q_OBJECT
	
	public:		
		//Fonctions membres	
		LCDWidget(QWidget *parent=0);
		LCDWidget(const QString& text, QWidget *parent=0);
		
		int value() const;
		QString text() const; 
		
	public slots:
		void setValue(int value);
		void setRange(int minValue, int maxValue);
		void setText(const QString& text);
		
	signals:
		void valueChanged(int newValue);
	
	private:
		void init();
		
	private:
		QSlider *slider;
		QLabel *label;
};

#endif /*LCDWIDGET*/

