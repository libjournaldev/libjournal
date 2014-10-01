#include "libcontroller.h"
#include "ui_libcontroller.h"

LibController::LibController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LibController)
{
    ui->setupUi(this);
}

LibController::~LibController()
{
    delete ui;
}
