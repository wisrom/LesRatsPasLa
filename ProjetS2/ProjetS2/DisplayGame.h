#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qpushbutton.h>



class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();

private slots:
    void boutonClicked();
};
