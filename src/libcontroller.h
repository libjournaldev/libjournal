#ifndef LIBCONTROLLER_H
#define LIBCONTROLLER_H

#include <QMainWindow>

namespace Ui {
class LibController;
}

class LibController : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibController(QWidget *parent = 0);
    ~LibController();

private:
    Ui::LibController *ui;
};

#endif // LIBCONTROLLER_H
