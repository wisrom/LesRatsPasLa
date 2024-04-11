#include "DisplayMenuQt.h"

DisplayMenuQt::DisplayMenuQt(int* sdifficulty, FishingRun* sFishingRun, QWidget* parent) : QMainWindow(parent), fishingRun(sFishingRun), difficulty(sdifficulty){
   writeMenu();
}

//DisplayMenuQt::DisplayMenuQt(int* intValue, FishingRun* sFishingRun, QWidget* parent) : difficulty(intValue), QMainWindow(parent), fishingRun(sFishingRun) {
//    writeMenu();    
//}

//DisplayMenuQt::DisplayMenuQt(int argc_, char** argv_, int* intValue) : DisplayMenuQt(intValue){
//    argc = argc_;
//    argv = argv_;
//}DisplayMenuQt::DisplayMenuQt(int argc_, char** argv_, int* intValue) : DisplayMenuQt(intValue){
//    argc = argc_;
//    argv = argv_;
//}
//DisplayMenuQt::DisplayMenuQt(QWidget* parent) : argc(argc_), argv(argv_) ,QMainWindow(parent) {


void DisplayMenuQt::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event); // Call base class implementation

    // Call the function to adjust button positions
    adjustButtonPositions();
}

void DisplayMenuQt::adjustButtonPositions() {
    // Calculate x position for centering buttons
    
    int windowWidth = this->geometry().width();
    int windowHeight = this->geometry().height();
    
    int buttonsWidth = windowWidth / 3;
    int buttonsHeight = (windowHeight/2) / 5;

    int xPos = int((windowWidth - buttonsWidth) / 2);
    int yPos = int(int((windowHeight - (buttonsHeight)) / 6));

    startButton->setGeometry(xPos, yPos, buttonsWidth, buttonsHeight);
    optionButton->setGeometry(xPos, yPos*2, buttonsWidth, buttonsHeight);
    scoreButton->setGeometry(xPos, yPos*3, buttonsWidth, buttonsHeight);
    
    difficultyLabel->setGeometry(xPos, yPos * 4, buttonsWidth, buttonsHeight);
    increaseButton->setGeometry(xPos, yPos*5, buttonsWidth/2, buttonsHeight);
    decreaseButton->setGeometry(xPos+ buttonsWidth/2, yPos*5, buttonsWidth/2, buttonsHeight);
}

void DisplayMenuQt::writeMenu(){
    widget = new QWidget;
    setWindowTitle("Menu");
    resize(800, 600);
    layout = new QVBoxLayout(widget);
    
    //difficultyLabel = new QLabel(QString("Difficulty set to " + QString::number(*difficulty)), this);
    difficultyLabel = new QLabel(QString("Difficulty set to " + QString::number(*difficulty)), this);
    layout->addWidget(difficultyLabel);

    QFont font1("Arial", 22, QFont::Bold);
    QFont font2("Arial", 18, QFont::Bold);
    QFont font3("Arial", 16, QFont::Bold);
    difficultyLabel->setFont(font1);

    startButton = new QPushButton("Start", this);
    optionButton = new QPushButton("Options", this);
    scoreButton = new QPushButton("Scores", this);
    increaseButton = new QPushButton("Increase", this);
    decreaseButton = new QPushButton("Decrease", this);
    /*
    startButton = new QPushButton("Start");
    optionButton = new QPushButton("Options");
    scoreButton = new QPushButton("Scores");
    increaseButton = new QPushButton("Increase");
    decreaseButton = new QPushButton("Decrease");
    */

    startButton->setFont(font2);
    optionButton->setFont(font2);
    scoreButton->setFont(font2);
    increaseButton->setFont(font3);
    decreaseButton->setFont(font3);

    layout->addWidget(startButton);
    layout->addWidget(optionButton);
    layout->addWidget(scoreButton);
    layout->addWidget(increaseButton);
    layout->addWidget(decreaseButton);

    adjustButtonPositions();

    connect(startButton, &QPushButton::clicked, [this]() {
        emit startClicked();
        });
    connect(optionButton, &QPushButton::clicked, this, &DisplayMenuQt::getOptions);
    connect(scoreButton, &QPushButton::clicked, this, &DisplayMenuQt::getScores);
    connect(increaseButton, &QPushButton::clicked, this, &DisplayMenuQt::handleIncrease);
    connect(decreaseButton, &QPushButton::clicked, this, &DisplayMenuQt::handleDecrease);

    connect(this, &DisplayMenuQt::resizeEvent, this, &DisplayMenuQt::adjustButtonPositions);
    
    setLayout(layout);
    
}
//
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
        move(0, y() - 10); break;
    case Qt::Key_Down:
        move(0, y() + 10); break;
    case Qt::Key_Left:
        move(x() - 10, 0); break;
    case Qt::Key_Right:
        move(x() + 10, 0); break;

    //Quick access
    case Qt::Key_C:
        *difficulty = -1;
        close(); break;
    case Qt::Key_O:
        getOptions(); break;
    case Qt::Key_P:
        getScores(); break;
    
    case Qt::Key_1:
        *difficulty = 1;
        startClicked(); break;
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
        break;
        //QWidget::keyPressEvent(event);
    }
}
//
void DisplayMenuQt::selectActual() {
    QPoint mousePos = QCursor::pos();
    QWidget* widgetAtMouse = childAt(mousePos);

    // Check if the widget at the mouse position is a QPushButton
    QPushButton* clickedButton = qobject_cast<QPushButton*>(widgetAtMouse);
    //if (clickedButton) {qDebug() << "Mouse is over the perimeter of button:" << clickedButton->text();}
    //else {qDebug() << "Mouse is not over the perimeter of any button.";}
    
}
//
////to complete
void DisplayMenuQt::getScores() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Scores logs");
    
    dialog->resize(300, 400);

    QLabel* Infos = new QLabel("\nList of the best scores\nGood Luck Beating them!\n", dialog);

    //get the top 5 scores!!!
    int vtop1 = 1000;
    int vtop2 = 800;
    int vtop3 = 700;
    int vtop4 = 600;
    int vtop5 = 500;
    
    QLabel* top1 = new QLabel("Score to beat : " + QString::number(vtop1), dialog);
    QLabel* top2 = new QLabel("Second : "+QString::number(vtop2), dialog);
    QLabel* top3 = new QLabel("Third : " + QString::number(vtop3), dialog);
    QLabel* top4 = new QLabel("4th : " + QString::number(vtop4), dialog);
    QLabel* top5 = new QLabel("5th : " + QString::number(vtop5), dialog);
    
    // Align the text to the left
    Infos->setAlignment(Qt::AlignCenter);
    top1->setAlignment(Qt::AlignLeft); 
    top2->setAlignment(Qt::AlignLeft);
    top3->setAlignment(Qt::AlignLeft);
    top4->setAlignment(Qt::AlignLeft);
    top5->setAlignment(Qt::AlignLeft);

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
//
void DisplayMenuQt::changeLabelValue(QLabel* label, QString value){
    label->setText(value);
}
//
//void DisplayMenuQt::drawGameWindow() {
//
//}
//
//void DisplayMenuQt::openGameWindow() {
//    InputGame actions = InputGame();
//    FishingRun fishingRun = FishingRun();
//    fishingRun.getCurrentSession()->difficulty = *difficulty;
//    
//   /* GameWindowQt gameWindow(actions, fishingRun);
//    gameWindow.show();
//    
//    Sleep(4000);
//    gameWindow.start();*/
//    
//}
// 
//    
//void DisplayMenuQt::openGame() {
//    this->hide();
//    openGameWindow();
//    //Sleep(1000);
//    this->show();
//}
//

//
//
void DisplayMenuQt::handleIncrease() {
    if (*difficulty<4) {(*difficulty)++;}
    else { *difficulty = 1; }
    qDebug() << "Value increased to" << *difficulty;
    changeLabelValue(difficultyLabel, QString("Difficulty set to " + QString::number(*difficulty)));

}

void DisplayMenuQt::handleDecrease() {
    if (*difficulty>1) {(*difficulty)--;}
    else { *difficulty = 4; }
    qDebug() << "Value decreased to" << *difficulty;
    changeLabelValue(difficultyLabel, QString("Difficulty set to " + QString::number(*difficulty)));
}

