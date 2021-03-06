#include "library.h"
#include <QtCore>
#include <QtWidgets>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWin;
    mainWin.setWindowTitle(QObject::tr("LibJournal"));
    mainWin.setWindowIcon(QIcon(":/images/main.png"));
    Library lib(&mainWin);
    mainWin.setCentralWidget(&lib);
    mainWin.setFixedWidth(lib.width());
    mainWin.setFixedHeight(lib.height()+15);
    QObject::connect(&lib, SIGNAL(statusMessage(QString)),
                     mainWin.statusBar(), SLOT(showMessage(QString)));
    mainWin.show();
    QMetaObject::invokeMethod(&lib, "init", Qt::QueuedConnection);
    return a.exec();
}
