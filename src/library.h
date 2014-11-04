#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>
#include <QtSql>
#include "ui_library.h"
#include "searchaccountdialog.h"

class Library : public QWidget, private Ui::Library
{
    Q_OBJECT

public:
    Library(QWidget *parent = 0);
    virtual ~Library();
    QSqlError createConnection(const QString &host, const QString &dataBase, const QString &user,
                          const QString &passwd, int port);
public slots:
    void init();
signals:
    void statusMessage(const QString &message);

private:
    SearchAccountDialog *searchAccount;
    QSqlDatabase db;
};

#endif // LIBRARY_H
