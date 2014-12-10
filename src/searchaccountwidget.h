#ifndef SEARCHACCOUNTWIDGET_H
#define SEARCHACCOUNTWIDGET_H

#include <QtWidgets>
#include <QtSql>
#include <QSqlRecord>
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
    void on_openHistory_triggered();
    void addAccount();
    void refresh(QAbstractButton *radio = 0);

private slots:
    void search_textChanged(const QString &text);
    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::SearchAccountWidget *ui;
    QSqlQueryModel model;
    QSqlDatabase activeDB;

};

#endif // SEARCHACCOUNTWIDGET_H
