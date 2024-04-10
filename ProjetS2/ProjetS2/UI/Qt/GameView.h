#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtWidgets>
#include "GameDomain/FishingRun.hpp"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class GameView : public QGraphicsView {

public:
    GameView(FishingRun* fishingRun, QWidget *parent = nullptr);
    ~GameView();

    void refreshMove(FishingRun* fishingRun);
    QGraphicsPixmapItem* fish = nullptr;
    void removeFishToGet();


protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QString playerImgPath = "C:\\Users\\kgo20\\Desktop\\img\\hamecon0.png";
    QString waterImgPath = "C:\\Users\\kgo20\\Desktop\\img\\eau0.png";
    QString fishImgPath = "C:\\Users\\kgo20\\Desktop\\img\\poissonColor22.png";
    void scaleImg(QPixmap imagePath, QGraphicsPixmapItem* pixmapItem);
    void ResizeGrid(QResizeEvent* event);
    QGraphicsScene *scene;
    FishingRun* fishingRun;
    QVector<QGraphicsPixmapItem*> cells;
    QVector<QGraphicsPixmapItem*> fishsToGet;

    int cellSize;
    int numCols = 20;
    int numRows = 20;
};