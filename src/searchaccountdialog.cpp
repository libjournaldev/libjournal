#include "searchaccountdialog.h"
#include "ui_searchaccountdialog.h"
#include <QDebug>

SearchAccountDialog::SearchAccountDialog(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    ui(new Ui::SearchAccountDialog)
{
    ui->setupUi(this);
    connect(ui->search,SIGNAL(textChanged(QString)),this,SLOT(search_textChanged(QString)));
    activeDB = db;
    model.setQuery("select * from reader", *activeDB);
    ui->tableView->setModel(&model);
}

SearchAccountDialog::~SearchAccountDialog()
{
    delete ui;
}


void SearchAccountDialog::search_textChanged(const QString &text)
{
    QSqlQuery q(*activeDB);
    if(!ui->search->text().isEmpty()){
        q.prepare("SELECT * FROM reader WHERE name LIKE ?");
        q.addBindValue(tr("%1\%").arg(text));
        q.exec();
    }
    else q.exec("select * from reader");
    model.setQuery(q);
}
