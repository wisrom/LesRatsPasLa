#pragma once

#include <QtWidgets/QMainWindow>
#include "UI/Qt/ReelGauge.hpp"

class DisplayGameQt : public QMainWindow
{
    Q_OBJECT

public:
    DisplayGameQt(QWidget *parent = nullptr);
    ~DisplayGameQt();

private slots:
    void boutonClicked();
};
