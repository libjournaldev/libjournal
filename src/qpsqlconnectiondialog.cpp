#include "qpsqlconnectiondialog.h"

#include <QSqlDatabase>

QPSQLConnectionDialog::QPSQLConnectionDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
}

QString QPSQLConnectionDialog::userName() const
{
    return ui.userName->text();
}

QString QPSQLConnectionDialog::dataBase() const
{
    return ui.dataBase->text();
}

QString QPSQLConnectionDialog::password() const
{
    return ui.password->text();
}

QString QPSQLConnectionDialog::hostName() const
{
    return ui.hostName->text();
}

int QPSQLConnectionDialog::port() const
{
    return ui.port->value();
}

QPSQLConnectionDialog::~QPSQLConnectionDialog()
{
}
