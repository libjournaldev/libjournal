#include "deletebookdialog.h"
#include "ui_deletebookdialog.h"

deleteBookDialog::deleteBookDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deleteBookDialog)
{
    ui->setupUi(this);
}

deleteBookDialog::~deleteBookDialog()
{
    delete ui;
}
