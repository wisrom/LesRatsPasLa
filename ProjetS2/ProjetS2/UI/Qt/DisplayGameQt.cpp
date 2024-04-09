#include "UI/Qt/DisplayGameQt.h"
#include "GameView.h"
#include <conio.h>

#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>

DisplayGameQt::DisplayGameQt(IInput* sInput, InputGame sActions, FishingRun sFishingRun, QWidget* parent)
	: QMainWindow(parent), fishingRun(sFishingRun), input(sInput), actions(sActions)
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &DisplayGameQt::handleTimer);
	timer->start(100);

	resize(800, 600); // Taille initiale de la fenêtre

	// Grille principale
	QWidget* mainWidget = new QWidget(this);
	QGridLayout* mainLayout = new QGridLayout();
	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);
	mainWidget->setObjectName("mainWidget");

	// Grille secondaire
	QWidget* scoreWidget = new QWidget(this);
	QGridLayout* scoreLayout = new QGridLayout();
	scoreWidget->setLayout(scoreLayout);
	scoreWidget->setObjectName("scoreWidget");

	QWidget* gameWidget = new QWidget(this);
	QGridLayout* gameLayout = new QGridLayout(gameWidget);
	//gameWidget->setLayout(gameLayout);
	gameWidget->setObjectName("gameWidget");

	QWidget* gaugeWidget = new QWidget(this);
	QGridLayout* gaugeLayout = new QGridLayout();
	gaugeWidget->setLayout(gaugeLayout);
	gaugeWidget->setObjectName("gaugeWidget");

	QWidget* catchingFishWidget = new QWidget(this);
	QGridLayout* catchingFishLayout = new QGridLayout();
	catchingFishWidget->setLayout(catchingFishLayout);
	catchingFishWidget->setObjectName("catchingfishwidget");

	QWidget* timerWidget = new QWidget(this);
	QGridLayout* timerLayout = new QGridLayout();
	timerWidget->setLayout(timerLayout);
	timerWidget->setObjectName("timerWidget");

	// Ajout des widget et layout secondaire au principale
	mainLayout->addWidget(scoreWidget, 0, 0, 1, 3);
	mainLayout->addWidget(gameWidget, 1, 0, 6, 3);
	mainLayout->addWidget(gaugeWidget, 7, 0, 1, 3);
	mainLayout->addWidget(catchingFishWidget, 0, 3, 7, 1);
	mainLayout->addWidget(timerWidget, 7, 3, 1, 1);

	mainLayout->addLayout(scoreLayout, 0, 0, 1, 3);
	mainLayout->addLayout(gameLayout, 1, 0, 6, 3);
	mainLayout->addLayout(gaugeLayout, 7, 0, 1, 3);
	mainLayout->addLayout(catchingFishLayout, 0, 3, 7, 1);
	mainLayout->addLayout(timerLayout, 7, 3, 1, 1);

	//Game
	gameView = new GameView(gameWidget);

	// Ajouter le GameView au layout principal
	gameLayout->setContentsMargins(5, 5, 5, 5);
	gameLayout->addWidget(gameView);
	gameWidget->setLayout(gameLayout);
}

void DisplayGameQt::keyPressEvent(QKeyEvent* event)
{
	int e = event->key();
	Movement m;
	m.x = 1;
	m.y = 0;
	fishingRun.getCurrentSession()->player.move(m);
}

DisplayGameQt::~DisplayGameQt()
{}

void DisplayGameQt::refreshMove()
{
	gameView->refreshMove(&fishingRun);
}

void DisplayGameQt::handleTimer() {
	this->refreshMove();

	// TODO refresh le score
	// TODO refresh le timer

	//if (fishingRun.getIsFinished())
	//{
	//    // TODO retourner au menu
	//}

	//output->DisplayGameData(fishingRun.getCurrentSession()->getScore());
	//displayGame.displaySession(*fishingRun.getCurrentSession());
	//actions = input->getGameInput();

	//if (actions.quit)
	//{
	//    //TODO retour au menu
	//}

	// Check menu
	//fishingRun.getCurrentSession()->processInput(actions);
}