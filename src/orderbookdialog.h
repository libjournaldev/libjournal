#ifndef ORDERBOOKDIALOG_H
#define ORDERBOOKDIALOG_H

#include <QDialog>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQueryModel>
namespace Ui {
class orderBookDialog;
}

class orderBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit orderBookDialog(QSqlRecord *rec , QWidget *parent);
    ~orderBookDialog();

private:
    Ui::orderBookDialog *ui;
    QSqlDatabase activeDB;
    QSqlQueryModel model;
};

#endif // ORDERBOOKDIALOG_H
