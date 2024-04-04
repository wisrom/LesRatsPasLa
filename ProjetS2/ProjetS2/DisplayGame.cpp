#include "DisplayGame.h"




QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

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
    QGridLayout* gameLayout = new QGridLayout();
    gameWidget->setLayout(gameLayout);
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


    // Connecter le signal clicked() du bouton à la fonction boutonClicked()
    //connect(button1, &QPushButton::clicked, this, &QtWidgetsApplication1::boutonClicked);

}

// Implémenter la fonction boutonClicked()
void QtWidgetsApplication1::boutonClicked()
{
    qDebug() << "Bouton cliqué !";
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}
