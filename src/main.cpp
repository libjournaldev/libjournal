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
    mainWin.setFixedSize(lib.size());
    mainWin.show();

    return a.exec();
}
