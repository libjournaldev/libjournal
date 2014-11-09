#include "searchaccountdialog.h"
#include "ui_searchaccountdialog.h"
#include <QDebug>

SearchAccountDialog::SearchAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchAccountDialog)
{
    ui->setupUi(this);
    QTimer::singleShot(0, ui->search, SLOT(setFocus()));
    connect(ui->search,SIGNAL(textChanged(QString)),this,SLOT(search_textChanged(QString)));
    activeDB = QSqlDatabase::database("libj");
    model.setQuery("select reader_id, name, surname from reader", activeDB);
    model.setHeaderData(0, Qt::Horizontal, tr("ID"));
    model.setHeaderData(1, Qt::Horizontal, tr("Имя"));
    model.setHeaderData(2, Qt::Horizontal, tr("Фамилия"));
    ui->tableView->setModel(&model);  
    comboBoxMap["имени"] = "name";
    comboBoxMap["фамилии"] = "surname";
    QMapIterator<QString, QString> i(comboBoxMap);
    while(i.hasNext()){
        i.next();
        ui->comboBox->addItem(i.key());
    }
}

SearchAccountDialog::~SearchAccountDialog()
{
    delete ui;
}


void SearchAccountDialog::search_textChanged(const QString &text)
{
    QSqlQuery q(activeDB);
    if(!ui->search->text().isEmpty()){
        q.prepare(tr("SELECT reader_id, name, surname FROM reader WHERE %1 LIKE ?")
                  .arg(comboBoxMap[ui->comboBox->currentText()]));
        q.addBindValue(tr("%1\%").arg(text));
        q.exec();
    }
    else q.exec("select reader_id, name, surname from reader");
    model.setQuery(q);
}
