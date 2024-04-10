#include "UI/Qt/DisplayGameQt.h"
#include "GameView.h"
#include <conio.h>

#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>

DisplayGameQt::DisplayGameQt(IInput* sInput, InputGame sActions, FishingRun* sFishingRun, QWidget* parent)
	: QMainWindow(parent), fishingRun(sFishingRun), input(sInput), actions(sActions)
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &DisplayGameQt::handleTimer);
	timer->start(30);

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
	lblScore = new QLabel("Score : SCORE_VALUE");
	scoreWidget->setLayout(scoreLayout);
	scoreWidget->setObjectName("scoreWidget");

	QWidget* gameWidget = new QWidget(this);
	QGridLayout* gameLayout = new QGridLayout(gameWidget);
	//gameWidget->setLayout(gameLayout);
	gameWidget->setObjectName("gameWidget");
	QWidget* gaugeWidget = new QWidget(this);
	QGridLayout* gaugeLayout = new QGridLayout();
	QWidget* lblReelSpeed = new QLabel("Reel Speed");
	bghReelGauge = new ReelGauge(gaugeWidget);
	bghReelGauge->setObjectName("gaugeBar");
	gaugeWidget->setLayout(gaugeLayout);
	gaugeWidget->setObjectName("gaugeWidget");

	QWidget* catchingFishWidget = new QWidget(this);
	QGridLayout* catchingFishLayout = new QGridLayout();
	catchingFishWidget->setLayout(catchingFishLayout);
	catchingFishWidget->setObjectName("catchingfishwidget");

	capturedFishWidget = new QTableWidget();
	capturedFishWidget->setColumnCount(2);
	capturedFishWidget->setHorizontalHeaderLabels({ "Name", "Score" });

	QWidget* timerWidget = new QWidget(this);
	QGridLayout* timerLayout = new QGridLayout();
	lblTimer = new QLabel("Time : TIMER_VALUE");
	//QLabel lblTimer = QLabel("Score : ");
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
	gameView = new GameView(fishingRun, gameWidget);

	// Ajouter le GameView au layout principal
	gameLayout->setContentsMargins(5, 5, 5, 5);
	gameLayout->addWidget(gameView);
	gameWidget->setLayout(gameLayout);

	// Ajouter le score widget au layout
	scoreLayout->addWidget(lblScore);
	scoreLayout->setAlignment(Qt::AlignCenter);

	// Ajouter les poissons captures au layout
	//catchingFishLayout->addWidget(capturedFishWidget);

	// Ajouter le timer widget au layout
	timerLayout->addWidget(lblTimer);
	timerLayout->setAlignment(Qt::AlignRight);

	// Ajouter la gauge de reel speed
	gaugeLayout->addWidget(bghReelGauge);
}

void DisplayGameQt::keyPressEvent(QKeyEvent* event)
{
	int key = event->key();
	Movement m;
	// WASD
	switch (key) {
	case Qt::Key_W:
		// Déplacement vers le haut
		m.x = 0;
		m.y = -1;
		break;
	case Qt::Key_A:
		// Déplacement vers la gauche
		m.x = -1;
		m.y = 0;
		break;
	case Qt::Key_S:
		// Déplacement vers le bas
		m.x = 0;
		m.y = 1;
		break;
	case Qt::Key_D:
		// Déplacement vers la droite
		m.x = 1;
		m.y = 0;
		break;
	case Qt::Key_Escape:
		quit = true;
		break;
	default:
		// Ne rien faire pour les autres touches
		return;
	}

	// Appliquer le mouvement
	fishingRun->getCurrentSession()->player.move(m);
}

DisplayGameQt::~DisplayGameQt()
{}

//void DisplayGameQt::refreshMove()
//{
//	gameView->refreshMove(fishingRun);
//}

void DisplayGameQt::handleTimer() {
	gameView->refreshMove(fishingRun);
	gameView->removeFishToGet();

	Fish fishEmpty = Fish();
	if (fishingRun->getCurrentSession()->getNearFish().getId() != fishEmpty.getId()) {
		bghReelGauge->updateValues(
			fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().speed_rpm - fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().margin,
			fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().margin + fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().speed_rpm,
			actions.reelSpeed_rpm);
	}

	lblScore->setText("Score: " + QString::number(fishingRun->getCurrentSession()->getScore()));
	lblTimer->setText(QString::number(fishingRun->getCurrentSession()->getRemainingTime_s()));

	if (fishingRun->getIsFinished())
	{
		// TODO retourner au menu
	}

	fishingRun->getCurrentSession()->processInput(actions);

	actions = input->getGameInput();
	if (quit)
	{
		quit = false;
		//TODO retour au menu
	}
}