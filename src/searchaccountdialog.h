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
    SearchAccountDialog(QWidget *parent);
    ~SearchAccountDialog();
private slots:
    void search_textChanged(const QString &text);

private:
    Ui::SearchAccountDialog *ui;
    QSqlQueryModel model;
    QSqlDatabase activeDB;
    QMap<QString, QString> comboBoxMap;
    void initModel();
};

#endif // SEARCHACCOUNTDIALOG_H
