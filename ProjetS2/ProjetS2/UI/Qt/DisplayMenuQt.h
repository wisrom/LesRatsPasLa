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
#include <QScreen>
//#include "GameWindowQt.h"
#include "GameDomain/FishingRun.hpp"
//for try
#include <QtWidgets>

#include <QFile>

#include "Input/InputConsole.hpp"
#include "Input/InputArduino.hpp"
#include "Output/OutputArduino.hpp"

#include "Communication/ComSerialJSON.hpp"

//#include <QMediaPlayer>
//#include <QAudioOutput>
#include <QUrl>

class DisplayMenuQt : public QMainWindow {
	Q_OBJECT
public:
	DisplayMenuQt(int* difficulty, FishingRun* sFishingRun, IInput* input_, InputGame actions_, QWidget* parent = nullptr);
	DisplayMenuQt(int* difficulty, FishingRun* sFishingRun, int width, int height, QWidget* parent = nullptr);
	QWidget* widget;
	QPushButton* startButton;
	FishingRun* fishingRun;
	int* difficulty;

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	std::vector<QPushButton*> buttonsList;
	//QPushButton* currentSelectedButton;
	int* currentSelected;
	IInput* input;
	InputGame actions;

	QPushButton* optionButton;
	QPushButton* scoreButton;
	QPushButton* increaseButton;
	QPushButton* decreaseButton;
	QPushButton* exitButton;
	QLabel* highestScoreLabel;
	QLabel* difficultyLabel;
	int WidWidth = 0;
	int WidHeight = 0;
	QVBoxLayout* mainlayout;

	QHBoxLayout* startLayout;
	QVBoxLayout* buttonsLayout;
	QHBoxLayout* scoreLayout;
	QHBoxLayout* optionsLayout;
	QVBoxLayout* difficultyShowLayout;

	QHBoxLayout* difficultyControlLayout;
	QHBoxLayout* exitLayout;
	QWidget* labelWidget;
	void writeMenu();
	void setBackground();
	void setButtonsStyle(std::vector<QPushButton*> buttons);



private slots:
	void changeLabelValue(QLabel* label, QString value);
	void selectActual();
	void toNext();
	void toPrevious();
	void setMousePos();

	void getOptions();
	void getScoresPage();
	void handleIncrease();
	void handleDecrease();
	void exitMenu();

	void setLabels();
	void startSound();
	void startSecondSound();

signals:
	void startClicked();
};


//IOutput* output = new OutputArduino(&com);
