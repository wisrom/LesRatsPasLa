#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtWidgets>


class GameView : public QGraphicsView {

public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

protected:
    void resizeEvent(QResizeEvent* event) override;


private:
    void ResizeGrid(QResizeEvent* event);
    QGraphicsScene *scene;
    QVector<QGraphicsRectItem*> cells;
};