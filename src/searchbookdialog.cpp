#include "searchbookdialog.h"
#include "ui_searchbookdialog.h"

searchbookdialog::searchbookdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchbookdialog)
{
    ui->setupUi(this);
}

searchbookdialog::~searchbookdialog()
{
    delete ui;
}
