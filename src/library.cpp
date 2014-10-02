#include "library.h"
#include "qpsqlconnectiondialog.h"
#include <QSettings>

Library::Library(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

}

void Library::initConnection()
{
    QPSQLConnectionDialog dialog(this);
    if(dialog.exec() != QDialog::Accepted)
        return;

    /*
    QSettings conf(QSettings::NativeFormat, QSettings::UserScope,
                   "LibSoft", "LibJournal");
    */
}

Library::~Library()
{

}
