#include "libcontroller.h"
#include <QApplication>
/*Добавил новую строку в комментарий лолвася*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibController w;
    w.show();

    return a.exec();
}
