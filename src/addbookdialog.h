#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QtSql>
#include <vector>
#include <string>
#include <Qstring>
#include <QCompleter>
#include <QStringList>

using namespace std;

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT


public:
    explicit AddBookDialog(QWidget *parent = 0);
    void basicInit();
    void closeEvent(QCloseEvent *event);
    ~AddBookDialog();

private slots:
    void on_nextButton_clicked();

    void on_cancelButton_clicked();

    void on_backButton_clicked();


    void on_labelAddNewAuthor_linkActivated(const QString &link);

    void on_labelAddNewAuthorBack_linkActivated(const QString &link);

    void on_labelAddNewAuthorForward_linkActivated(const QString &link);

    void on_btnChoosePhoto_clicked();

    void on_editBookAuthorSurname_editingFinished();

private:
    Ui::AddBookDialog *ui;
    vector <vector <QString> > authorNames;
    int currentAuthorBook;
    QSqlQuery activequery;
    QCompleter *bookCategoryCompleter;
    QCompleter *bookAuthorSurnames;
    QCompleter *bookAuthorNames;
    //QCompleter *bookAuthorMiddleNames;
    QStringList bookCategoryList;
    QStringList bookAuthorSurnameList;
    QStringList bookAuthorNamesList;
    //QStringList bookAuthorMiddleNamesList;
};

#endif // ADDBOOKDIALOG_H
