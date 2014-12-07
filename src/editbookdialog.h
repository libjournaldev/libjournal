#ifndef EDITBOOKDIALOG_H
#define EDITBOOKDIALOG_H

#include <QDialog>
#include <QCompleter>
#include <QStringList>
#include <vector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

using namespace std;
namespace Ui {
class editbookdialog;
}

class editbookdialog : public QDialog
{
    Q_OBJECT

public:
    editbookdialog(QSqlRecord *rec , QWidget *parent = 0);
    editbookdialog(QWidget *parent = 0);
    ~editbookdialog();


private slots:

    void initTableInfo(int);

    void on_surnameLineEdit_editingFinished();

    void on_nameLineEdit_editingFinished();

    void on_linkBack_linkActivated(const QString &link);

    void on_linkForward_linkActivated(const QString &link);

    void on_linkAppendAuthor_linkActivated(const QString &link);

    void on_bookNameLineEdit_editingFinished();

    void on_bookNameLineEdit_textChanged(const QString &arg1);

private:
    Ui::editbookdialog *ui;
    QSqlDatabase activeDB;
    int currentAuthorBook;
    QSqlQuery *query;
    QCompleter *completerAuthorName;
    QCompleter *completerAuthorSurname;
    QCompleter *completerBookName;
    QCompleter *bookCategory;
    QCompleter *bookUDKCode;
    QStringList authorNameList;
    QStringList authorSurnameList;
    QStringList bookNameList;
    QStringList bookCategoryList;
    QStringList bookUDKCodeList;
    vector < vector <QString> > authorNames;

};

#endif // EDITBOOKDIALOG_H
