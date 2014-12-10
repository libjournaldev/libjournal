#ifndef ORDERBOOKDIALOG_H
#define ORDERBOOKDIALOG_H

#include <QDialog>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "searchaccountwidget.h"
namespace Ui {
class orderBookDialog;
}

class orderBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit orderBookDialog(QSqlRecord *rec , QWidget *parent);
    ~orderBookDialog();

private slots:
    void on_orderBookDialog_accepted();

private:
    Ui::orderBookDialog *ui;
    QSqlDatabase activeDB;
    QSqlQueryModel model;
    QSqlQuery *query;
};

#endif // ORDERBOOKDIALOG_H
