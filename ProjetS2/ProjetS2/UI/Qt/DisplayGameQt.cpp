#include "UI/Qt/DisplayGameQt.h"
#include "UI/Qt/DisplayMenuQt.h"

#include "GameView.h"
#include <conio.h>

#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>

DisplayGameQt::DisplayGameQt(IInput* sInput, InputGame sActions, FishingRun* sFishingRun, QWidget* parent)
	: QMainWindow(parent), fishingRun(sFishingRun), input(sInput), actions(sActions)
{
	QWidget* mainmainWidget = new QWidget(this);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	stackedWidget = new QStackedWidget;
		
	QWidget* menuPage = createMenuPage(); // Widget du menu
	QWidget* gamePage = createGamePage(); // Widget du jeu


	// Ajout de widget principale dans le stack
	stackedWidget->addWidget(menuPage);
	stackedWidget->addWidget(gamePage);
	mainmainWidget->setLayout(layout);
	layout->addWidget(stackedWidget);
	setCentralWidget(mainmainWidget);
}

void DisplayGameQt::startGame() 
{
	if (timer == NULL) {
		timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &DisplayGameQt::handleTimer);
	}
	timer->start(30);
	gameView->refreshFishscatch(catchingFishLayout);
	//fishingRun->getCurrentSession()->setDifficulty(*difficulty);
	fishingRun->getCurrentSession()->startTimer();
	stackedWidget->setCurrentIndex(1);
}

void DisplayGameQt::backToMenu() 
{
	fishingRun->resetSession();
	gameView->refreshFishDisplay();
	timer->stop();
	displayMenu->timerMenu.start(20);
	stackedWidget->setCurrentIndex(0);
}

QWidget* DisplayGameQt::createMenuPage() 
{
	displayMenu = new DisplayMenuQt(new int(1), fishingRun, input, actions, this);
	connect(displayMenu, &DisplayMenuQt::startClicked, this, &DisplayGameQt::startGame);

	return displayMenu->widget;
}

QWidget* DisplayGameQt::createGamePage() {
	
	this->setWindowState(Qt::WindowFullScreen);

	// Grille principale
	QWidget* mainWidget = new QWidget(this); // Widget du jeu
	QGridLayout* mainLayout = new QGridLayout();
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);
	mainWidget->setObjectName("mainWidget");

	// Grille secondaire
	QWidget* scoreWidget = new QWidget(this);
	QGridLayout* scoreLayout = new QGridLayout();
	lblScore = new QLabel("Score : SCORE_VALUE");
	lblScore->setObjectName("lblScore");
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
	catchingFishLayout = new QGridLayout();
	catchingFishWidget->setLayout(catchingFishLayout);
	catchingFishWidget->setObjectName("catchingfishwidget");
	capturedFishWidget = new QStringList();

	QWidget* timerWidget = new QWidget(this);
	QGridLayout* timerLayout = new QGridLayout();
	lblTimer = new QLabel("Time : TIMER_VALUE");
	//QLabel lblTimer = QLabel("Score : ");
	timerWidget->setLayout(timerLayout);
	timerWidget->setObjectName("timerWidget");

	// Ajout des widget et layout secondaire au principale
	mainLayout->addWidget(scoreWidget, 0, 3, 1, 1);
	mainLayout->addWidget(gameWidget, 0, 0, 7, 3);
	mainLayout->addWidget(gaugeWidget, 7, 0, 1, 3);
	mainLayout->addWidget(catchingFishWidget, 1, 3, 6, 1);
	mainLayout->addWidget(timerWidget, 7, 3, 1, 1);

	mainLayout->addLayout(scoreLayout, 0, 0, 1, 3);
	mainLayout->addLayout(gameLayout, 1, 0, 6, 3);
	mainLayout->addLayout(gaugeLayout, 7, 0, 1, 3);
	mainLayout->addLayout(catchingFishLayout, 0, 3, 7, 1);
	mainLayout->addLayout(timerLayout, 7, 3, 1, 1);

	//Game
	gameView = new GameView(fishingRun, gameWidget);
	gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	gameView->setObjectName("gameView");
	// Ajouter le GameView au layout principal
	gameLayout->setContentsMargins(1, 1, 0, 0);
	gameLayout->addWidget(gameView);
	gameWidget->setLayout(gameLayout);

	// Ajouter le score widget au layout
	scoreLayout->addWidget(lblScore);
	scoreLayout->setAlignment(Qt::AlignCenter);

	// Ajouter les poissons captures au layout
	//catchingFishLayout->addWidget(capturedFishWidget);

	// Ajouter le timer widget au layout
	timerLayout->addWidget(lblTimer);
	timerLayout->setAlignment(Qt::AlignCenter);

	// Ajouter la gauge de reel speed
	gaugeLayout->addWidget(bghReelGauge);

	//Resize Label
	gameView->resizeLbl(lblScore);
	gameView->resizeLbl(lblTimer);

	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(QPixmap(":/Img/nemo.jpg").scaled(this->size())));
	mainWidget->setAutoFillBackground(true);
	mainWidget->setPalette(palette);

	return mainWidget;
}

void DisplayGameQt::keyPressEvent(QKeyEvent* event)
{
	int key = event->key();
	Movement m;
	m.x = 0;
	m.y = 0;
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
	case Qt::Key_N:
		this->showNormal(); // Restaurer en mode fenêtré
		break;
	case Qt::Key_M:
		this->setWindowState(Qt::WindowFullScreen); // Full Screen
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

void DisplayGameQt::handleTimer() {
	gameView->refreshMove(fishingRun);
	gameView->removeFishToGet();
	gameView->changeImageFish();
	

	Fish fishEmpty = Fish();
	if (fishingRun->getCurrentSession()->getNearFish().getId() != fishEmpty.getId()) {

		bghReelGauge->updateValues(
			fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().speed_rpm - fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().margin,
			fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().margin + fishingRun->getCurrentSession()->getNearFish().getCurrentCaptureStep().speed_rpm,
			actions.reelSpeed_rpm);
	}
	else
	{
		bghReelGauge->updateValues(0, MAX_REEL_SPEED_GAUGE_RPM, 0);
	}

	lblScore->setText("Score: " + QString::number(fishingRun->getCurrentSession()->getScore()));
	lblTimer->setText(QString::number(fishingRun->getCurrentSession()->getRemainingTime_s()));

	if (fishingRun->getIsFinished())
	{
		backToMenu();
		// TODO réinitialiser
	}

	gameView->refreshFishDisplay();
	if (fishingRun->getCurrentSession()->processInput(actions)) 
	{
		gameView->refreshFishscatch(catchingFishLayout);
	}

	actions = input->getGameInput(fishingRun->getCurrentSession()->getScore());
	if (quit)
	{
		quit = false;
		backToMenu();
		// TODO réinitialiser
	}
}

void DisplayGameQt::updateCapturedFish(std::vector<Fish> capturedFish, QGridLayout* layout)
{
	capturedFishWidget->clear();

	for (Fish fish : capturedFish)
	{
		*capturedFishWidget << QString::fromStdString(fish.getName()) << QString::number(fish.getScore());
	}

	int row = 0;
	int column = 0;
	for (const QString& text : *capturedFishWidget)
	{
		QLabel* label = new QLabel(text);
		layout->addWidget(label, row, column);
		column = (column + 1) % 2;
		if (column == 0)
		{
			++row;
		}
	}
}