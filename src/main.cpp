#include "library.h"

#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWin;
    mainWin.setWindowTitle(QObject::tr("LibJournal"));
    Library lib(&mainWin);
    mainWin.setCentralWidget(&lib);
    mainWin.setFixedWidth(lib.width());
    mainWin.setFixedHeight(lib.height()+15);
    QObject::connect(&lib, SIGNAL(statusMessage(QString)),
                     mainWin.statusBar(), SLOT(showMessage(QString)));
    mainWin.show();
    /* загружать из настроек? */
    QMetaObject::invokeMethod(&lib, "init", Qt::QueuedConnection);
    return a.exec();
}
