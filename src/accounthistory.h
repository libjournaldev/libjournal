#ifndef ACCOUNTHISTORY_H
#define ACCOUNTHISTORY_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class AccountHistory;
}

class AccountHistorySqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    AccountHistorySqlModel(QObject *parent = 0);

    QVariant data(const QModelIndex &item) const;
    QVariant data(const QModelIndex &item, int role) const;
};

class AccountHistory : public QDialog
{
    Q_OBJECT

public:
    AccountHistory(QWidget *parent = 0);
    AccountHistory(int reader, QWidget *parent = 0);
    ~AccountHistory();
public slots:
    void showFullHistory();
    void showDebtors();

private slots:
    void search_textChanged(const QString &text);
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void markAs(int code);
    void on_markAsReturned_triggered();
    void on_markAsGiven_triggered();
    void on_markAsGivenToRoom_triggered();

private:
    Ui::AccountHistory *ui;
    AccountHistorySqlModel model;
    QSqlDatabase activeDB;
};

#endif // ACCOUNTHISTORY_H
