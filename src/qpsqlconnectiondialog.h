#ifndef QPSQLCONNECTIONDIALOG_H
#define QPSQLCONNECTIONDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_qpsqlconnectiondialog.h"

class QPSQLConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    QPSQLConnectionDialog(QWidget *parent = 0);
    ~QPSQLConnectionDialog();
    QString userName() const;
    QString dataBase() const;
    QString password() const;
    QString hostName() const;
    int port() const;

private slots:
    void on_okButton_clicked() { accept(); }
    void on_cancelButton_clicked() { reject(); }

private:
    Ui::QPSQLConnectionDialog ui;
};

#endif // QPSQLCONNECTIONDIALOG_H
