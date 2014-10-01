#include "libcontroller.h"
#include "ui_libcontroller.h"

LibController::LibController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LibController)
{
    ui->setupUi(this);
    // git push me and then just touch me satisfaction
}

LibController::~LibController()
{
    delete ui;
}
