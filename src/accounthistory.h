#ifndef ACCOUNTHISTORY_H
#define ACCOUNTHISTORY_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class AccountHistory;
}

enum BookStatus
{
    bookReturned,
    bookOnHands,
    expired
};

class AccountHistory : public QDialog
{
    Q_OBJECT

public:
    explicit AccountHistory(int reader, QWidget *parent = 0);
    ~AccountHistory();

private:
    Ui::AccountHistory *ui;
};

class AccountHistorySqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    AccountHistorySqlModel(QObject *parent = 0);

    QVariant data(const QModelIndex &item, int role) const;
};

#endif // ACCOUNTHISTORY_H
