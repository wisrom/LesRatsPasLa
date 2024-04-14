#pragma once

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <qpainter.h>

#define MIN_REEL_SPEED_GAUGE_RPM 0
#define MAX_REEL_SPEED_GAUGE_RPM 150.0f

class ReelGauge : public QProgressBar 
{
public:
  ReelGauge(QWidget *parent = nullptr);
  void updateValues(int reelSpeedMin_rpm, int reelSpeedMax_rpm, int reelSpeed_rpm);
private:
  int reelSpeedMin_rpm;
  int reelSpeedMax_rpm;
  int reelSpeed_rpm;
  QPainter* painter;
  void gauge();


  void paintEvent(QPaintEvent* event) override;
};