#include "orderbookdialog.h"
#include "ui_orderbookdialog.h"
#include <QSqlRecord>

orderBookDialog::orderBookDialog(QSqlRecord *rec , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderBookDialog)
{
    ui->setupUi(this);
    activeDB = QSqlDatabase::database("libj");
    /*Заполняем таблицу с инвентарными номерами*/
    model.setQuery(tr("SELECT bookID FROM bookCatalogueTable WHERE bookUDKCode = '%1'").arg(rec->value("bookUDKCode").toString()),activeDB);

    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();

    ui->tableView->setModel(&model);
    ui->tableView->setColumnWidth(0,120);

    /*Заканчиваем заполнять таблицу с инвентарными номерами*/

    ui->labelBookName->setText(rec->value(1).toString());
    ui->labelAuthorNames->setText(rec->value(2).toString());
    ui->labelCategory->setText(rec->value(3).toString());
    ui->labelUDKCode->setText(rec->value(0).toString());
}

orderBookDialog::~orderBookDialog()
{
    delete ui;
}
