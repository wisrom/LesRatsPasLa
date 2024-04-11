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
    void resizeLbl(QLabel* lbl);
    void changeImageFish();
    void changeImageBubble();
protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QString playerImgPath = ":/Img/boat.png";
    QString waterImgPath = ":/Img/water.jpg";
    QString bubbleImgPath = ":/Img/bulles.png";
    QString fishImgPath = ":/Img/poisson.png";

    bool isReady = false;
    QGraphicsPixmapItem* fishPopItem;
    QVector<QGraphicsPixmapItem*> fishsToGet;
    void scaleImg(QPixmap imagePath, QGraphicsPixmapItem* pixmapItem);
    void ResizeGrid(QResizeEvent* event);
    QGraphicsScene *scene;
    FishingRun* fishingRun;
    QVector<QGraphicsPixmapItem*> cells;
    QVector <QLabel*> lbls;

    int cellSize;
    int numCols = 29;
    int numRows = 19;
};