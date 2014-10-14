#include "library.h"
#include "qpsqlconnectiondialog.h"
#include <QSettings>

Library::Library(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(preferencesButton,SIGNAL(clicked()),
            this,SLOT(init()));
}

QSqlError Library::createConnection(const QString &host, const QString &user,
                               const QString &passwd, int port)
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(QString("QPSQL"),QString("libj"));
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(passwd);
    db.setPort(port);
    db.setDatabaseName(tr("libdb"));
    if(!db.open(user,passwd)){
        err = db.lastError();
    }
    return err;
}

void Library::init()
{
    QPSQLConnectionDialog dialog(this);
    if(dialog.exec() != QDialog::Accepted)
        return;
    QSqlError err = createConnection(dialog.hostName(), dialog.userName(), dialog.password(),
                                     dialog.port());
    if(err.type() != QSqlError::NoError){
        QMessageBox::warning(this,tr("Ошибка соединения"),tr("Не удалось соединиться с сервером "
                                                             "баз данных: ") + err.text());
    }
    else{
        emit statusMessage(tr("Соединено: %1").arg(dialog.userName()));
    }


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
