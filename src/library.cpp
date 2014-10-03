#include "library.h"
#include "qpsqlconnectiondialog.h"
#include <QSettings>

Library::Library(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    /*
    preferencesButton->setIcon(QIcon(":/images/gear.png"));
    preferencesButton->setCheckable(false);
    */
}

void Library::initConnection()
{
    QPSQLConnectionDialog dialog(this);
    if(dialog.exec() != QDialog::Accepted)
        return;
    /*
    QSettings conf(QSettings::NativeFormat, QSettings::UserScope,
                   "LibSoft", "LibJournal");
    conf.beginGroup("psqlconf");
    conf.setValue("login",dialog.userName());
    conf.setValue("password",dialog.password());
    conf.setValue("server",dialog.hostName());
    conf.endGroup();
    */
}

Library::~Library()
{

}
