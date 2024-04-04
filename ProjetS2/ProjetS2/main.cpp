#include "DisplayGame.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    QFile file("styles.css");
    file.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    w.show();
    return a.exec();

}
