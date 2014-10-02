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

void QPSQLConnectionDialog::on_okButton_clicked()
{
    accept();
}

QPSQLConnectionDialog::~QPSQLConnectionDialog()
{
}
