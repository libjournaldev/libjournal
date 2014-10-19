#ifndef SEARCHACCOUNTDIALOG_H
#define SEARCHACCOUNTDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class SearchAccountDialog;
}

class SearchAccountDialog : public QDialog
{
    Q_OBJECT

public:
    SearchAccountDialog(QWidget *parent, QSqlDatabase &db);
    ~SearchAccountDialog();

private:
    Ui::SearchAccountDialog *ui;
    QSqlQueryModel model;
    QSqlDatabase activeDB;
    void initModel();
};

#endif // SEARCHACCOUNTDIALOG_H
