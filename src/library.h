#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>
#include <QtSql>
#include "ui_library.h"

class Library : public QWidget, private Ui::Library
{
    Q_OBJECT

public:
    Library(QWidget *parent = 0);
    virtual ~Library();
public slots:
    void init();
    QSqlError createConnection(const QString &host, const QString &user,
                          const QString &passwd, int port);
signals:
    void statusMessage(const QString &message);

};

#endif // LIBRARY_H
