#pragma once

#include <QtWidgets/QMainWindow>

class DisplayGameQt : public QMainWindow
{
    Q_OBJECT

public:
    DisplayGameQt(QWidget *parent = nullptr);
    ~DisplayGameQt();

private slots:
    void boutonClicked();
};
