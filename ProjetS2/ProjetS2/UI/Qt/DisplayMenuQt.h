#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QtWidgets>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
//#include "GameWindowQt.h"
#include "GameDomain/FishingRun.hpp"
//for try
#include <QtWidgets>

#include <QFile>

#include "Input/InputConsole.hpp"
#include "Input/InputArduino.hpp"
#include "Output/OutputArduino.hpp"

#include "Communication/ComSerialJSON.hpp"



class DisplayMenuQt : public QMainWindow {
	Q_OBJECT
public:
	DisplayMenuQt(int* difficulty, FishingRun* sFishingRun, QWidget* parent = nullptr);
	//DisplayMenuQt(int argc_, char** argv_, int* intValue);
	QWidget* widget;
	QPushButton* startButton;
	FishingRun* fishingRun;
	int* difficulty;

protected:
	void resizeEvent(QResizeEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

private:
	QPushButton* optionButton;
	QPushButton* scoreButton;
	QPushButton* increaseButton;
	QPushButton* decreaseButton;
	QLabel* difficultyLabel;
	QVBoxLayout* layout;
	void writeMenu();
	void adjustButtonPositions();

private slots:
	void changeLabelValue(QLabel* label, QString value);
	void selectActual();
	void getOptions();
	void getScores();
	void handleIncrease();
	void handleDecrease();

signals:
	void startClicked();
};

//protected:
//    void keyPressEvent(QKeyEvent* event) override;
//    //void resizeEvent(QResizeEvent* event) override;
//
//private slots:
//    void handleStart();
//    void getOptions();
//    void getScores();
//    void handleIncrease();
//    void handleDecrease();

//    void changeLabelValue(QLabel* label, QString value);
//    void selectActual();
//    
//    void openGame();
//    void openGameWindow();
//    void drawGameWindow();
//    void writeMenu();
//private:
//   
//
//    int buttonsWidth = 150;
//    int buttonsHeight = 50;
//    

  /*  int argc = 1;
	char** argv = nullptr;*/

	//IOutput* output = new OutputArduino(&com);
