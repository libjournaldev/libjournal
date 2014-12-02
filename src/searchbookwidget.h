#ifndef SEARCHBOOKWIDGET_H
#define SEARCHBOOKWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include <QButtonGroup>

namespace Ui {
class SearchBookWidget;
}

class SearchBookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBookWidget(QWidget *parent = 0);
    ~SearchBookWidget();

public slots:
    void on_editRowAction_triggered();

private slots:
    void search_textChanged(const QString &text);
    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_addNewBookButton_clicked();

private:
    Ui::SearchBookWidget *ui;
    QSqlQueryModel model;
    QSqlDatabase activeDB;
    void initModel();
};

#endif // SEARCHBOOKWIDGET_H
