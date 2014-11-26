#ifndef SEARCHACCOUNTWIDGET_H
#define SEARCHACCOUNTWIDGET_H

#include <QtWidgets>
#include <QtSql>
#include "libjsqlmodel.h"

namespace Ui {
class SearchAccountWidget;
}

class SearchAccountWidget : public QWidget
{
    Q_OBJECT

public:
    SearchAccountWidget(QWidget *parent = 0);
    ~SearchAccountWidget();

public slots:
    void on_editRowAction_triggered();

private slots:
    void search_textChanged(const QString &text);
    void on_tableView_customContextMenuRequested(const QPoint &pos);
    void on_pushButton_clicked();

private:
    Ui::SearchAccountWidget *ui;
    QSqlQueryModel model;
    QSqlDatabase activeDB;
    void initModel();

};

#endif // SEARCHACCOUNTWIDGET_H
