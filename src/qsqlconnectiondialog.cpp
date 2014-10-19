#include "qsqlconnectiondialog.h"

#include <QSqlDatabase>

QSQLConnectionDialog::QSQLConnectionDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
}

QString QSQLConnectionDialog::userName() const
{
    return ui.userName->text();
}

QString QSQLConnectionDialog::dataBase() const
{
    return ui.dataBase->text();
}

QString QSQLConnectionDialog::password() const
{
    return ui.password->text();
}

QString QSQLConnectionDialog::hostName() const
{
    return ui.hostName->text();
}

int QSQLConnectionDialog::port() const
{
    return ui.port->value();
}

QSQLConnectionDialog::~QSQLConnectionDialog()
{
}
