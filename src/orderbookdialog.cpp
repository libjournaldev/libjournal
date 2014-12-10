#include "orderbookdialog.h"
#include "ui_orderbookdialog.h"
#include <QSqlRecord>
#include <QStringList>
#include <QDate>

orderBookDialog::orderBookDialog(QSqlRecord *rec , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderBookDialog)
{
    ui->setupUi(this);
    activeDB = QSqlDatabase::database("libj");
    /*Заполняем таблицу с инвентарными номерами*/
    model.setQuery(tr("SELECT bookID FROM bookCatalogueTable WHERE bookUDKCode = '%1' and bookID NOT IN "
                      "(SELECT bookID FROM requestTable WHERE status='На руках' OR status='Читальный зал')")
                   .arg(rec->value("bookUDKCode").toString()),activeDB);
    model.query().exec();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();

    ui->tableView->setModel(&model);
    ui->tableView->setColumnWidth(0,120);

    /*Заканчиваем заполнять таблицу с инвентарными номерами*/

    ui->labelBookName->setText(rec->value(1).toString());
    ui->labelAuthorNames->setText(rec->value(2).toString());
    ui->labelCategory->setText(rec->value(3).toString());
    ui->labelUDKCode->setText(rec->value(0).toString());

    /*Заполняем виды выдачи*/
    QStringList types;
    types<<"На руки";
    types<<"В читальный зал";
    ui->comboBoxTypes->addItems(types);
}

orderBookDialog::~orderBookDialog()
{
    delete ui;
}


void orderBookDialog::on_orderBookDialog_accepted()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    QModelIndex primaryKeyIndex = model.index(row, 0);
    int bookID = model.data(primaryKeyIndex).toInt();
    int type;
    QString date;
    if (ui->comboBoxTypes->currentText()=="На руки"){
        type = 2;
        date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    }else{
        type = 1;
        QDate tmpDate = QDate::currentDate();
        date = tmpDate.toString("yyyy-MM-dd");
        qDebug()<<date;
    }
    query = new QSqlQuery(tr("INSERT INTO requestTable (readerID,bookID,status,endDate) VALUES (%1,%2,%3,'%4')")
                          .arg(ui->lineEdit->text(),QString::number(bookID),QString::number(type),date),activeDB);

    delete query;
}
