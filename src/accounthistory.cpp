#include "accounthistory.h"
#include "ui_accounthistory.h"
#include <QSqlDatabase>
#include <QDate>
#include <QtSql>
#include <QMenu>
#include <QDebug>

AccountHistory::AccountHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountHistory)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/takenBooks.png"));
    setWindowTitle("История заявок");
    setMinimumWidth(662);
    setMinimumHeight(378);
    connect(ui->showFullButton, SIGNAL(clicked()), this, SLOT(showFullHistory()));
    connect(ui->showDebtors, SIGNAL(clicked()), this, SLOT(showDebtors()));
    activeDB = QSqlDatabase::database("libj");
    model.setQuery("SELECT readerID, requesttable.bookID, bookName, status, endDate "
                   "FROM requestTable, bookCatalogueTable, bookInfoTable "
                   "WHERE bookCatalogueTable.bookID = requestTable.bookID "
                   "GROUP BY bookID", activeDB);
    ui->tableView->setModel(&model);

    ui->tableView->setColumnWidth(0,55);
    ui->tableView->setColumnWidth(1,55);
    ui->tableView->setColumnWidth(2,345);
    ui->tableView->setColumnWidth(3,73);
    ui->tableView->setColumnWidth(4,93);
    model.setHeaderData(0, Qt::Horizontal, tr("ID чит."));
    model.setHeaderData(1, Qt::Horizontal, tr("Инв. №"));
    model.setHeaderData(2, Qt::Horizontal, tr("Название книги"));
    model.setHeaderData(3, Qt::Horizontal, tr("Состояние"));
    model.setHeaderData(4, Qt::Horizontal, tr("Срок возврата"));
}

void AccountHistory::showFullHistory()
{
    model.setQuery("SELECT readerID, requesttable.bookID, bookName, status, endDate "
                   "FROM requestTable, bookCatalogueTable, bookInfoTable "
                   "WHERE bookCatalogueTable.bookID = requestTable.bookID "
                   "GROUP BY bookID", activeDB);
    model.query().exec();
}

void AccountHistory::showDebtors()
{
    model.setQuery("SELECT readerID, requesttable.bookID, bookName, status, endDate "
                   "FROM requestTable, bookCatalogueTable, bookInfoTable "
                   "WHERE bookCatalogueTable.bookID = requestTable.bookID "
                   "AND CURDATE() > endDate "
                   "GROUP BY bookID", activeDB);
    model.query().exec();
}

AccountHistory::AccountHistory(int reader, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountHistory)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/takenBooks.png"));
    setWindowTitle(tr("История пользователя (ID %1)").arg(reader));
    ui->searchGroupBox->hide();

    activeDB = QSqlDatabase::database("libj");

    model.setQuery(tr("SELECT requesttable.bookID, bookName, status, endDate "
                       "FROM requestTable, bookCatalogueTable, bookInfoTable "
                       "WHERE (bookCatalogueTable.bookID = requestTable.bookID) "
                       "AND (bookInfoTable.bookUDKCode = bookCatalogueTable.bookUDKCode)"
                       "AND requestTable.readerID = %1").arg(reader), activeDB);
    ui->tableView->setModel(&model);

    ui->tableView->setColumnWidth(0,55);
    ui->tableView->setColumnWidth(1,345);
    ui->tableView->setColumnWidth(2,73);
    ui->tableView->setColumnWidth(3,93);
    model.setHeaderData(0, Qt::Horizontal, tr("Инв. №"));
    model.setHeaderData(1, Qt::Horizontal, tr("Название книги"));
    model.setHeaderData(2, Qt::Horizontal, tr("Состояние"));
    model.setHeaderData(3, Qt::Horizontal, tr("Срок возврата"));

}

void AccountHistory::on_search_textChanged(const QString &text)
{
    QSqlQuery q(activeDB);
    if(!text.isEmpty()){
        q.prepare(tr("SELECT readerID, requesttable.bookID, bookName, status, endDate "
                     "FROM requestTable, bookCatalogueTable, bookInfoTable "
                     "WHERE (bookCatalogueTable.bookID = requestTable.bookID) "
                     "AND requestTable.bookID LIKE ?"
                     "GROUP BY bookID"));
        q.addBindValue(tr("%1\%").arg(text));
        q.exec();
    }
    else q.exec("SELECT readerID, requesttable.bookID, bookName, status, endDate "
                "FROM requestTable, bookCatalogueTable, bookInfoTable "
                "WHERE bookCatalogueTable.bookID = requestTable.bookID "
                "GROUP BY bookID");

    model.setQuery(q);
}

void AccountHistory::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QList<QAction*> actions;
    actions << ui->markAsReturned << ui->markAsGiven << ui->markAsGivenToRoom;
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    bool ok = selectionModel->hasSelection();
    int row = selectionModel->currentIndex().row();
    int statusCol = model.record(row).indexOf("status");
    QModelIndex statusIdx = model.index(row, statusCol);
    int statusCode = model.data(statusIdx).toInt();
    QMenu contextMenu(this);
    contextMenu.addActions(actions);
    for(int act=0; act<actions.size(); ++act){
        if(statusCode != act) actions[act]->setEnabled(ok);
        else actions[act]->setDisabled(true);
    }
    contextMenu.exec(QCursor::pos());
}

void AccountHistory::markAs(int code)
{
    QSqlQuery q(activeDB);
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    int row = selectionModel->currentIndex().row();
    int bookCol = model.record(row).indexOf("bookID");
    QModelIndex bookIdx = model.index(row, bookCol);
    int bookID = model.data(bookIdx).toInt();
    q.exec(tr("UPDATE requestTable SET status = %1 WHERE bookID = %2").arg(code).arg(bookID));
    model.query().exec();
}

void AccountHistory::on_markAsReturned_triggered()
{
    markAs(0);
}

void AccountHistory::on_markAsGiven_triggered()
{
    markAs(1);
}

void AccountHistory::on_markAsGivenToRoom_triggered()
{
    markAs(2);
}

AccountHistory::~AccountHistory()
{
    delete ui;
}

AccountHistorySqlModel::AccountHistorySqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

QVariant AccountHistorySqlModel::data(const QModelIndex &index) const
{
    return QSqlQueryModel::data(index);
}

QVariant AccountHistorySqlModel::data(const QModelIndex &index, int role) const
{
    if((role == Qt::BackgroundRole) || (role == Qt::TextColorRole) || (role == Qt::DisplayRole)){
        int dateCol = QSqlQueryModel::record(index.row()).indexOf("endDate");
        int statusCol = QSqlQueryModel::record(index.row()).indexOf("status");
        QModelIndex dateIndex = QSqlQueryModel::index(index.row(), dateCol);
        QModelIndex statusIndex = QSqlQueryModel::index(index.row(), statusCol);
        QDate endDate = QSqlQueryModel::data(dateIndex).toDate();
        int status = QSqlQueryModel::data(statusIndex).toInt();
        bool owed = (QDate::currentDate() > endDate);
        bool onHands = (status == 1); // если на руках
        if (role == Qt::BackgroundRole){
            if(owed && onHands) return QBrush(QColor(255, 133, 96, 190));
            else if(!owed && onHands) return QBrush(QColor(100, 172, 255, 190));
            return QBrush(QColor(Qt::white));
        }
        if (role == Qt::TextColorRole){
            if(!onHands) return QVariant::fromValue(QColor(Qt::black));
            return QVariant::fromValue(QColor(Qt::white));
        }
        if((role == Qt::DisplayRole) && index.column() == statusCol){
            switch(status){
                case 0: return QString("вернули");
                case 1: return QString("на руках");
                case 2: return QString("в зале");
            }
        }
    }
    return QSqlQueryModel::data(index, role);
}
