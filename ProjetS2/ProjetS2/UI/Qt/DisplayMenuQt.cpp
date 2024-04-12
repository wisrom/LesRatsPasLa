#include "DisplayMenuQt.h"


DisplayMenuQt::DisplayMenuQt(int* intValue, FishingRun* sFishingRun, IInput* input_, InputGame actions_, QWidget* parent) :
    difficulty(intValue), fishingRun(sFishingRun), QMainWindow(parent), actions(actions_), input(input_)
{
    widget = new QWidget;
    widget->installEventFilter(this);
    writeMenu();
    startSound();

    connect(&timerMenu, &QTimer::timeout, this, &DisplayMenuQt::handleTimerMenu);
    timerMenu.start(50);
    //if (&timerMenu == NULL) {
        //&timerMenu = new QTimer(this);
        //connect(&timerMenu, &QTimer::timeout, this, &DisplayMenuQt::handleTimerMenu);
    //}
    //timerMenu->start(30);

}


void DisplayMenuQt::startSound() {
    //QMediaPlayer* _mediaPlayer = new QMediaPlayer;
    //QAudioOutput* _audioOutput = new QAudioOutput;

    //_mediaPlayer->setAudioOutput(_audioOutput);
    ////QString athasd("calmfishingSound.mp3");
    //_mediaPlayer->setSource(QUrl("qrc:/Sounds/calmfishingSound.mp3"));
    //
    //_audioOutput->setVolume(100);
    //_mediaPlayer->setLoops(QMediaPlayer::Infinite);
    //_mediaPlayer->play();
}
void DisplayMenuQt::startSecondSound() {

}

void DisplayMenuQt::exitMenu() {
    widget->parentWidget()->window()->close();
}

void DisplayMenuQt::setLabels() {

    difficultyLabel = new QLabel(QString("Difficulty : " + QString::number(*difficulty)));

    DataFile data;
    std::vector<int> Scores = data.getScores();
    Scores.push_back(0);
    std::sort(Scores.begin(), Scores.end(), std::greater<int>());
    int highestScore = Scores[0];
    highestScoreLabel = new QLabel(QString("Highest score : " + QString::number(highestScore)));

    highestScoreLabel->setAlignment(Qt::AlignCenter);
    highestScoreLabel->setMaximumHeight(75);

    difficultyLabel->setAlignment(Qt::AlignCenter);
    difficultyLabel->setMaximumHeight(75);

}

void DisplayMenuQt::handleTimerMenu() {
    if (!input->getMenuInput().btn4) { selectActual(); }
    if (!input->getMenuInput().btn3) {//exitMenu();
        changeLabelValue(difficultyLabel, QString::number(input->getMenuInput().btn3));
    }
    
    else if(input->getMenuInput().movement.x == 0 && input->getMenuInput().movement.y == -1){
        toPrevious();
    }
    else if (input->getMenuInput().movement.x == 0 && input->getMenuInput().movement.y == 1){
        toNext();
    }
    else if (input->getMenuInput().movement.x == -1 && input->getMenuInput().movement.y == 0){
        toPrevious();
    }
    else if (input->getMenuInput().movement.x == 1 && input->getMenuInput().movement.y == 0){
        toNext();
    }
}

bool DisplayMenuQt::eventFilter(QObject* obj, QEvent* event) {
    if (obj == widget && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();
        if (key == Qt::Key_W) {
            toPrevious();
            //handleIncrease();
        }
        else if (key == Qt::Key_A) {
            toPrevious();
            //handleDecrease();
        }
        else if (key == Qt::Key_S) {
            toNext();
            //handleDecrease();
        }
        else if (key == Qt::Key_D) {
            toNext();
            //handleDecrease();
        }
        else if (key == Qt::Key_H) {
            selectActual();
        }
        return true; 
    }
    return QObject::eventFilter(obj, event);
}

void DisplayMenuQt::writeMenu() {
    setWindowTitle("Menu");

    mainlayout = new QVBoxLayout(widget);

    buttonsLayout = new QVBoxLayout;
    startLayout = new QHBoxLayout;
    scoreLayout = new QHBoxLayout;
    optionsLayout = new QHBoxLayout;
    difficultyShowLayout = new QVBoxLayout;
    difficultyControlLayout = new QHBoxLayout;
    exitLayout = new QHBoxLayout;
    labelWidget = new QWidget;

    setLabels();

    QFont font1("Arial", 22, QFont::Bold);
    QFont font2("Arial", 18, QFont::Bold);
    QFont font3("Arial", 16, QFont::Bold);

    difficultyLabel->setFont(font1);
    highestScoreLabel->setFont(font1);

    startButton = new QPushButton("Start");
    optionButton = new QPushButton("Options");
    scoreButton = new QPushButton("Scores");
    increaseButton = new QPushButton("Increase");
    decreaseButton = new QPushButton("Decrease");
    exitButton = new QPushButton("Exit");


    startButton->setFont(font2);
    optionButton->setFont(font2);
    scoreButton->setFont(font2);
    increaseButton->setFont(font3);
    decreaseButton->setFont(font3);
    exitButton->setFont(font2);

    int space = 600;
    startLayout->addSpacing(space);
    startLayout->addWidget(startButton);
    startLayout->addSpacing(space);

    optionsLayout->addSpacing(space);
    optionsLayout->addWidget(optionButton);
    optionsLayout->addSpacing(space);

    scoreLayout->addSpacing(space);
    scoreLayout->addWidget(scoreButton);
    scoreLayout->addSpacing(space);

    difficultyShowLayout->addWidget(difficultyLabel);
    difficultyShowLayout->addWidget(highestScoreLabel);

    labelWidget->setLayout(difficultyShowLayout);
    labelWidget->setMaximumHeight(150);
    labelWidget->setStyleSheet("background:transparent;");

    difficultyControlLayout->addSpacing(space);
    difficultyControlLayout->addWidget(increaseButton);
    difficultyControlLayout->addSpacing(10);
    difficultyControlLayout->addWidget(decreaseButton);
    difficultyControlLayout->addSpacing(space);

    exitLayout->addSpacing(space);
    exitLayout->addWidget(exitButton);
    exitLayout->addSpacing(space);

    buttonsLayout->addSpacing(10);


    buttonsLayout->addLayout(startLayout);
    buttonsLayout->addLayout(optionsLayout);
    buttonsLayout->addLayout(scoreLayout);

    buttonsLayout->addWidget(labelWidget);
    //buttonsLayout->addLayout(difficultyShowLayout);

    buttonsLayout->addLayout(difficultyControlLayout);
    buttonsLayout->addLayout(exitLayout);

    buttonsLayout->addSpacing(10);
    mainlayout->addLayout(buttonsLayout);


    //adjustButtonPositions();

    connect(startButton, &QPushButton::clicked, [this]() {timerMenu.stop();emit startClicked(); });

    //connect(optionButton, &QPushButton::clicked, this, &DisplayMenuQt::getOptions);
    connect(scoreButton, &QPushButton::clicked, this, &DisplayMenuQt::getScoresPage);
    connect(increaseButton, &QPushButton::clicked, this, &DisplayMenuQt::handleIncrease);
    connect(decreaseButton, &QPushButton::clicked, this, &DisplayMenuQt::handleDecrease);
    connect(exitButton, &QPushButton::clicked, this, &DisplayMenuQt::exitMenu);

    //QPushButton* NextButton = new QPushButton();
    //connect(NextButton, &QPushButton::clicked, this, &DisplayMenuQt::toNext);
    //NextButton->setShortcut(Qt::Key::Key_W);
    //NextButton->setShortcut(Qt::Key::Key_A);

    //QShortcut* shortcutW = new QShortcut(QKeySequence(Qt::Key_W), this);
    //connect(shortcutW, &QShortcut::activated, this, &DisplayMenuQt::toNext);

    optionButton->setShortcut(Qt::Key::Key_O);
    scoreButton->setShortcut(Qt::Key::Key_P);
    exitButton->setShortcut(Qt::Key::Key_C);
    

    std::vector<QPushButton*> buttons = { startButton, optionButton, scoreButton, increaseButton, decreaseButton, exitButton };
    buttonsList = buttons;
    setButtonsStyle(buttons);
    setBackground();

    widget->setLayout(mainlayout);
    QPixmap cursorImage(":/Img/mouseImg.png");
    QCursor cursor(cursorImage);

    widget->setCursor(cursor);
    currentSelected = new int(0);
    buttonsList[*currentSelected]->setFocus();
    
}

void DisplayMenuQt::setMousePos() {

    (*currentSelected)++;
    //int y = *currentSelected * 50 + 25;
    //if(currentSelected)
    //changeLabelValue(difficultyLabel, QString("value : " + QString::number(*currentSelected)));
    //QCursor::setPos(globalButtonCenter);
    //QPoint cursorPos;   


    //QCursor::setPos(100, 100);

    //widgetAtMouse->setCursor()
    //widgetAtMouse->grabMouse();
    //QCursor.setPosition(widgetAtMouse->getPosi);
    //QPushButton* clickedButton = qobject_cast<QPushButton*>(widgetAtMouse);
}

void DisplayMenuQt::toNext() {
    if (*currentSelected < 5) { (*currentSelected)++; }
    else { *currentSelected = 0; }
    buttonsList[*currentSelected]->setFocus();
    //changeLabelValue(difficultyLabel, QString("Difficulty set to " + QString::number(*currentSelected)));
}
void DisplayMenuQt::toPrevious() {
    if (*currentSelected > 0) { (*currentSelected)--; }
    else { *currentSelected = 5; }
    buttonsList[*currentSelected]->setFocus();
    //changeLabelValue(difficultyLabel, QString("Difficulty set to " + QString::number(*currentSelected)));
}


void DisplayMenuQt::keyPressEvent(QKeyEvent* event) {
    /*
    * Arrows : move from choice to choice
    * O : open option Dialog
    * P : open scores Dialog
    * 1-2-3-4 : set difficulty to # and start directly
    * Enter : start
    * Space : press the button selected
    * C : close the window without lunching the game
    */

    switch (event->key()) {
        //Movements
    case Qt::Key_Up:
        toNext();
        break;
    case Qt::Key_Down:
        toPrevious();
        break;
    case Qt::Key_Left:
        toNext();
        break;
    case Qt::Key_Right:
        toPrevious();
        break;

    case Qt::Key_W:
        toPrevious(); break;
    case Qt::Key_A:
        toPrevious(); break;
    case Qt::Key_D:
        toNext(); break;
    case Qt::Key_S:
        toNext(); break;

        //Quick access
    case Qt::Key_C:
        *difficulty = -1;
        exitMenu();
        break;
    case Qt::Key_O:
        getOptions(); break;
    case Qt::Key_P:
        getScoresPage(); break;

    case Qt::Key_1:
        *difficulty = 1;
        startClicked();
        break;
    case Qt::Key_2:
        *difficulty = 2;
        startClicked(); break;
    case Qt::Key_3:
        *difficulty = 3;
        startClicked(); break;
    case Qt::Key_4:
        *difficulty = 4;
        startClicked(); break;

        //Normal press
    case Qt::Key_Space:
        selectActual(); break;
    case Qt::Key_Enter:
        startClicked(); break;


    default:
        //break;
        QWidget::keyPressEvent(event);
    }
}

void DisplayMenuQt::selectActual() {
    //QPoint mousePos = QCursor::pos();
    //QWidget* widgetAtMouse = childAt(mousePos);
    //QPushButton* clickedButton = qobject_cast<QPushButton*>(widgetAtMouse);
    buttonsList[*currentSelected]->click();
}


//to complete
void DisplayMenuQt::getScoresPage() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Scores logs");

    dialog->resize(300, 400);

    QLabel* Infos = new QLabel("\nList of the best scores\nGood Luck Beating them!\n", dialog);

    DataFile data;
    std::vector<int> scores = data.getScores();
    for (int i = 0; i < 7; i++) { scores.push_back(i * 3); }

    std::sort(scores.begin(), scores.end(), std::greater<int>());
    std::vector<int> vtop = { 0, 0, 0, 0, 0 };

    for (int i = 0; i < 5; i++) { vtop[i] = scores[i]; }

    QFont fontscore("Arial", 18, QFont::Bold);

    QLabel* top1 = new QLabel("Score to beat : " + QString::number(vtop[0]), dialog);
    QLabel* top2 = new QLabel("Second : " + QString::number(vtop[1]), dialog);
    QLabel* top3 = new QLabel("Third : " + QString::number(vtop[2]), dialog);
    QLabel* top4 = new QLabel("4th : " + QString::number(vtop[3]), dialog);
    QLabel* top5 = new QLabel("5th : " + QString::number(vtop[4]), dialog);
    Infos->setFont(fontscore);
    top1->setFont(fontscore); top2->setFont(fontscore); top3->setFont(fontscore); top4->setFont(fontscore); top5->setFont(fontscore);
    // Align the text to the left
    Infos->setAlignment(Qt::AlignCenter);
    top1->setAlignment(Qt::AlignCenter);
    top2->setAlignment(Qt::AlignCenter);
    top3->setAlignment(Qt::AlignCenter);
    top4->setAlignment(Qt::AlignCenter);
    top5->setAlignment(Qt::AlignCenter);

    //dialog-
    //QLabel* scores = new QLabel("Score to beat : \nSecond : \n Third : \n \n\n4:\n5:\n6:", dialog);
    //scores->setAlignment(Qt::AlignRight); // Align the text to the left


    QVBoxLayout* layout = new QVBoxLayout(dialog);

    layout->addWidget(Infos);
    layout->addWidget(top1);
    layout->addWidget(top2);
    layout->addWidget(top3);
    layout->addWidget(top4);
    layout->addWidget(top5);

    dialog->exec(); // Use exec() for modal dialog or show() for modeless dialog

    highestScoreLabel->setText(QString("Highest score : " + QString::number(vtop[0])));
}

void DisplayMenuQt::setBackground() {
    //mainlayout
    widget->setStyleSheet("background-image: url(:/Img/imageback.png);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-color: #000000;"
    );


    //this->cursor() = cursor;
}

void DisplayMenuQt::setButtonsStyle(std::vector<QPushButton*> buttons) {
    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i]->setStyleSheet("QPushButton {"
            //"background-color: #4CAF50;" // Green background color
            "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #00A0FF, stop: 1 #000FFF);"
            "color: white;"               // Text color
            "border-style: outset;"       // Border style
            "border-width: 2px;"           // Border width
            "border-radius: 10px;"         // Border radius
            "border-color: #000000;"      // Border color
            "padding: 6px;"                // Padding
            "}"
            "QPushButton:focus {"
                "background-color: #ADD8E6;"
                "border: 2px solid black;"
                "color: black;"               // Text color
            "}"
        );

    }

}
void DisplayMenuQt::getOptions() {
    qDebug() << "\nOptions button clicked!";

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Settings");
    dialog->resize(300, 400);


    QLabel* Infos = new QLabel("Set the difficulty (1 to 4)", dialog);

    QVBoxLayout* layoutDialog = new QVBoxLayout(dialog);

    QPushButton* increaseBut = new QPushButton("Increase", this);
    QPushButton* decreaseBut = new QPushButton("Decrease", this);

    increaseBut->setGeometry(100, 50, 100, 50);
    increaseBut->setGeometry(100, 150, 100, 50);

    connect(increaseBut, &QPushButton::clicked, this, &DisplayMenuQt::handleIncrease);
    connect(decreaseBut, &QPushButton::clicked, this, &DisplayMenuQt::handleDecrease);

    Infos->setAlignment(Qt::AlignCenter);

    layoutDialog->addWidget(increaseBut);
    layoutDialog->addWidget(decreaseBut);
    // Align the text to the left


    //QLabel* scores = new QLabel("Score to beat : \nSecond : \n Third : \n \n\n4:\n5:\n6:", dialog);
    //scores->setAlignment(Qt::AlignRight); // Align the text to the left

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(Infos);
    dialog->exec(); // Use exec() for modal dialog or show() for modeless dialog

}

void DisplayMenuQt::changeLabelValue(QLabel* label, QString value) {
    label->setText(value);
}
void DisplayMenuQt::handleIncrease() {
    if (*difficulty < 4) { (*difficulty)++; }
    else { *difficulty = 1; }
    changeLabelValue(difficultyLabel, QString("Difficulty set to " + QString::number(*difficulty)));
}
void DisplayMenuQt::handleDecrease() {
    if (*difficulty > 1) { (*difficulty)--; }
    else { *difficulty = 4; }
    changeLabelValue(difficultyLabel, QString("Difficulty set to " + QString::number(*difficulty)));
}

