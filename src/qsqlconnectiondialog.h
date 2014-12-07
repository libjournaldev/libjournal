#ifndef QSQLCONNECTIONDIALOG_H
#define QSQLCONNECTIONDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_qsqlconnectiondialog.h"

class QSQLConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    QSQLConnectionDialog(QWidget *parent = 0);
    ~QSQLConnectionDialog();
    QString userName() const;
    QString dataBase() const;
    QString password() const;
    QString hostName() const;
    int port() const;

private:
    Ui::QSQLConnectionDialog ui;
};

#endif // QSQLCONNECTIONDIALOG_H
