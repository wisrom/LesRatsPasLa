#pragma once

#include <QtWidgets/QMainWindow>
#include <Input/IInput.hpp>
#include "GameDomain/FishingRun.hpp"
#include "GameView.h"
#include <QTimer>
#include "UI/Qt/ReelGauge.hpp"

class DisplayGameQt : public QMainWindow
{
    Q_OBJECT

public:
    DisplayGameQt(IInput* input, InputGame actions, FishingRun fishingRun, QWidget* parent = nullptr);
    ~DisplayGameQt();
    GameView* gameView;
    void refreshMove();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void handleTimer();

private:
    FishingRun fishingRun;
    IInput* input;
    InputGame actions;
    QTimer* timer;
    QTableWidget* capturedFishWidget;

    void updateCapturedFishWidget(std::vector<Fish> capturedFish);
};
