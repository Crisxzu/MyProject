#include <QtWidgets>
#include <QtGui>
#include "lcdwidget.h"


LCDWidget::LCDWidget(QWidget *parent)
:	QWidget(parent),
	slider(NULL)
{
	init();
}

LCDWidget::LCDWidget(const QString& text, QWidget *parent)
:	QWidget(parent),
	slider(NULL)
{
	init();
	setText(text);	
}

int LCDWidget::value() const
{
	return slider->value();
}

QString LCDWidget::text() const
{
	return label->text();
}

void LCDWidget::setValue(int value)
{
	slider->setValue(value);
}

void LCDWidget::setRange(int minValue, int maxValue)
{
	if (minValue<0 or maxValue>99 or minValue>maxValue)
	{
		qWarning("LCDWidget::setRange(%d, %d)\n \tRange must be 0..99\n \tand minValue must not be greater than maxValue\n", minValue, maxValue);
		return;		
	}
	slider->setRange(minValue, maxValue);
}

void LCDWidget::setText(const QString& text)
{
	label->setText(text);
}

void LCDWidget::init()
{
	QLCDNumber *lcd= new QLCDNumber(5);
	lcd->setSegmentStyle(QLCDNumber::Flat);
	
	slider=new QSlider(Qt::Horizontal);
	slider->setRange(0, 99);
	slider->setValue(0);
	
	label=new QLabel;
	label->setAlignment(Qt::AlignCenter | Qt::AlignTop);
	label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	
	connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
	connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
	
	QVBoxLayout *layout=new QVBoxLayout;
	layout->addWidget(lcd);
	layout->addWidget(slider);
	layout->addWidget(label);
	setLayout(layout);
	setFocusProxy(slider);	
}
