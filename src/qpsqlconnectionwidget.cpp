#include "qpsqlconnectionwidget.h"
#include "ui_qpsqlconnectionwidget.h"

QPSQLConnectionWidget::QPSQLConnectionWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPSQLConnectionWidget)
{
    ui->setupUi(this);
}

QPSQLConnectionWidget::~QPSQLConnectionWidget()
{
    delete ui;
}
