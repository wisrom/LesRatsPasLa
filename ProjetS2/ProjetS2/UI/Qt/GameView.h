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
protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QString playerImgPath = ":/Img/hamecon.png";
    QString waterImgPath = ":/Img/eau.png";
    QString fishImgPath = ":/Img/poisson";

    void scaleImg(QPixmap imagePath, QGraphicsPixmapItem* pixmapItem);
    void ResizeGrid(QResizeEvent* event);
    QGraphicsScene *scene;
    FishingRun* fishingRun;
    QVector<QGraphicsPixmapItem*> cells;
    QVector<QGraphicsPixmapItem*> fishsToGet;
    QVector <QLabel*> lbls;

    int cellSize;
    int numCols = 29;
    int numRows = 19;
};