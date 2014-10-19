#include "searchaccountdialog.h"
#include "ui_searchaccountdialog.h"

SearchAccountDialog::SearchAccountDialog(QWidget *parent, QSqlDatabase &db) :
    QDialog(parent),
    ui(new Ui::SearchAccountDialog)
{
    ui->setupUi(this);
    activeDB = db;
    model.setQuery("select * from reader",activeDB);
    ui->tableView->setModel(&model);

}


SearchAccountDialog::~SearchAccountDialog()
{
    delete ui;
}

