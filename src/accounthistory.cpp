#include "accounthistory.h"
#include "ui_accounthistory.h"
#include <QSqlDatabase>
#include <QDate>
#include <QDebug>

AccountHistory::AccountHistory(int reader, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountHistory)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/takenBooks.png"));

    QSqlDatabase db = QSqlDatabase::database("libj");
    AccountHistorySqlModel *model = new AccountHistorySqlModel(ui->tableView);

    model->setQuery(tr("SELECT requesttable.bookID, bookName, status, endDate "
                       "FROM requestTable, bookCatalogueTable, bookInfoTable "
                       "WHERE (bookCatalogueTable.bookID = requestTable.bookID) "
                       "AND (bookInfoTable.bookUDKCode = bookCatalogueTable.bookUDKCode)"
                       "AND requestTable.readerID = %1").arg(reader), db);
    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(0,55);
    ui->tableView->setColumnWidth(1,345);
    ui->tableView->setColumnWidth(2,73);
    ui->tableView->setColumnWidth(3,93);
    model->setHeaderData(0, Qt::Horizontal, tr("Инв. №"));
    model->setHeaderData(1, Qt::Horizontal, tr("Название книги"));
    model->setHeaderData(2, Qt::Horizontal, tr("Состояние"));
    model->setHeaderData(3, Qt::Horizontal, tr("Срок возврата"));

    const QColor hlClr = QColor(128,128,128,50);
    const QColor txtClr = Qt::black;
    QPalette p = ui->tableView->palette();
    p.setColor(QPalette::Highlight, hlClr);
    p.setColor(QPalette::HighlightedText, txtClr);
    ui->tableView->setPalette(p);
}

AccountHistory::~AccountHistory()
{
    delete ui;
}

AccountHistorySqlModel::AccountHistorySqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

QVariant AccountHistorySqlModel::data(const QModelIndex &index, int role) const
{
    QModelIndex dateIndex = QSqlQueryModel::index(index.row(), 3);
    QModelIndex statusIndex = QSqlQueryModel::index(index.row(), 2);
    QDate endDate = QSqlQueryModel::data(dateIndex).toDate();
    QString status = QSqlQueryModel::data(statusIndex).toString();
    bool owed = (QDate::currentDate() > endDate);
    bool onHands = (status == "на руках");
    if (role == Qt::BackgroundRole){
        if(owed && onHands) return QBrush(QColor(255, 133, 96));
        else if(!owed && onHands) return QBrush(QColor(100, 172, 255));
        return QBrush(QColor(Qt::white));
    }
    if (role == Qt::TextColorRole){
        if(!onHands) return QVariant::fromValue(QColor(Qt::black));
        return QVariant::fromValue(QColor(Qt::white));
    }
    return QSqlQueryModel::data(index, role);
}
