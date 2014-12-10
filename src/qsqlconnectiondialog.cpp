#include "qsqlconnectiondialog.h"

#include <QSqlDatabase>
#include <QFileInfo>
#include <QDir>
#include <QSettings>

QSQLConnectionDialog::QSQLConnectionDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    setWindowIcon(QIcon(":/images/gear.png"));
    setWindowTitle("Сервер");
    bool iniExist = QFileInfo(QDir::currentPath(),"server.ini").exists();
    if(iniExist){
        QSettings s("server.ini",QSettings::IniFormat);
        s.beginGroup("SQLCONFIG");
        ui.hostName->setText(s.value("server").toString());
        ui.dataBase->setText(s.value("db").toString());
        ui.userName->setText(s.value("login").toString());
        ui.port->setValue(s.value("port").toInt());
        s.endGroup();
    }
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
