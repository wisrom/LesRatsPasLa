#include "UI/qt/DisplayGame.h"
#include <QtWidgets\\QApplication>
#include <QFile>
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DisplayGame w;
    //QFile file("C:\\Users\\kgo20\\Desktop\\t\\styles.css");
    QFile file(":/styles.css");

    file.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    w.show();
    return a.exec();

}
