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
    void refreshFishDisplay();
    Position isDifferent;
    bool isReady = false;
    void refreshFishscatch(QGridLayout* layout);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QString playerImgPath = ":/Img/boat.png";
    QString waterImgPath = ":/Img/water.jpg";
    QString bubbleImgPath = ":/Img/bulles.png";
    QString fishImgPath = ":/Img/poisson.png";

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