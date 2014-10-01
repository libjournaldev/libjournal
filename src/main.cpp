#include "libcontroller.h"
#include <QApplication>
/*1*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibController w;
    w.show();

    return a.exec();
}
