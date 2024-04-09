#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtWidgets>
#include "GameDomain/FishingRun.hpp"


class GameView : public QGraphicsView {

public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

    void refreshMove(FishingRun* fishingRun);
    QGraphicsEllipseItem* fish = nullptr;

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void ResizeGrid(QResizeEvent* event);
    QGraphicsScene *scene;
    QVector<QGraphicsRectItem*> cells;
    int cellSize;
    int numCols = 20;
    int numRows = 20;
};