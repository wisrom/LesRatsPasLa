#pragma once

#include <QtWidgets/QMainWindow>

class DisplayGame : public QMainWindow
{
    Q_OBJECT

public:
    DisplayGame(QWidget *parent = nullptr);
    ~DisplayGame();

private slots:
    void boutonClicked();
};
