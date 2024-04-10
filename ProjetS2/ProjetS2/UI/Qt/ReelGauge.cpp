#include "ReelGauge.hpp"

ReelGauge::ReelGauge(QWidget* parent) : QProgressBar(parent)
{
	setRange(0, MAX_REEL_SPEED_GAUGE_RPM);
	updateValues(0, 0, 0);
}

void ReelGauge::updateValues(int reelSpeedMin_rpm, int reelSpeedMax_rpm, int reelSpeed_rpm)
{
	this->reelSpeedMin_rpm = reelSpeedMin_rpm;
	this->reelSpeedMax_rpm = reelSpeedMax_rpm;
	this->reelSpeed_rpm = reelSpeed_rpm;
	gauge();
	update();
}

void ReelGauge::gauge()
{
	painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing);

	// Color variation
	QLinearGradient gradient(0, 0, width(), 0);
	gradient.setColorAt(0, QColor(0, 255, 0));
	gradient.setColorAt(1, QColor(255, 0, 0));

	// Fill progress bar with gradient
	int reelSpeedPosition = (reelSpeed_rpm / MAX_REEL_SPEED_GAUGE_RPM) * this->width();
	painter->fillRect(0, 0, reelSpeedPosition, height(), gradient);

	// Draw additional vertical bars
	painter->setPen(Qt::black);
	int reelSpeedMinPosition = (reelSpeedMin_rpm / MAX_REEL_SPEED_GAUGE_RPM) * this->width();
	int reelSpeedMaxPosition = (reelSpeedMax_rpm / MAX_REEL_SPEED_GAUGE_RPM) * this->width();
	painter->drawLine(reelSpeedMinPosition, 0, reelSpeedMinPosition, height());
	painter->drawLine(reelSpeedMaxPosition, 0, reelSpeedMaxPosition, height());
}

void ReelGauge::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	gauge();
}