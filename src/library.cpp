#include "library.h"
#include "qsqlconnectiondialog.h"
#include <QSettings>
#include <QDebug>
#include <QPixmap>

Library::Library(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(preferencesButton, SIGNAL(clicked()), this, SLOT(init()));
    searchAccount = NULL;
}

QSqlError Library::createConnection(const QString &host, const QString &dataBase, const QString &user,
                      const QString &passwd, int port)
{
    QApplication::setOverrideCursor(Qt::BusyCursor);
    if(QSqlDatabase::contains("libj"))
        db = QSqlDatabase::database("libj");
    else
        db = QSqlDatabase::addDatabase(QString("QMYSQL"),QString("libj"));
    db.setHostName(host);
    db.setDatabaseName(dataBase);
    db.setUserName(user);
    db.setPassword(passwd);
    db.setPort(port);
    if(!db.open(user,passwd)){
        QApplication::restoreOverrideCursor();
        QSqlError err = db.lastError();
        db = QSqlDatabase();
        return err;
    }
    else
        emit statusMessage(tr("Соединено: %1").arg(user));
        if(!searchAccount) searchAccount = new SearchAccountWidget();
        searchBook = new SearchBookWidget();
        connect(searchAccountButton,SIGNAL(clicked()),
                searchAccount,SLOT(show()));
        connect(searchBookButton,SIGNAL(clicked()),searchBook,SLOT(show()));
    QApplication::restoreOverrideCursor();
    return QSqlError();
}

void Library::init()
{
    bool iniExist = QFileInfo(QDir::currentPath(),"server.ini").exists();
    static bool warningAppeared = false;
    if(iniExist && !warningAppeared && !QSqlDatabase::database("libj").isOpen())
    {
        QSettings s("server.ini",QSettings::IniFormat);
        s.beginGroup("SQLCONFIG");
        QSqlError err = createConnection(s.value("server").toString(),s.value("db").toString(),
                         s.value("login").toString(),s.value("password").toString(),
                         s.value("port").toInt());
        if(err.type() != QSqlError::NoError)
        {
            QMessageBox::warning(this,tr("Ошибка соединения"),tr("Не удалось соединиться с сервером "
                                                             "баз данных: ") + err.text());
            warningAppeared = true;
            emit statusMessage(tr("Отключен"));
        }
        s.endGroup();
    }
    else
    {
        QSQLConnectionDialog dialog(this);
        if(dialog.exec() != QDialog::Accepted)
            return;
        QSqlError err = createConnection(dialog.hostName(), dialog.dataBase(), dialog.userName(),
                                         dialog.password(), dialog.port());
        if(err.type() != QSqlError::NoError)
        {
            QMessageBox::warning(this,tr("Ошибка соединения"),tr("Не удалось соединиться с сервером "
                                                                 "баз данных: ") + err.text());
            warningAppeared = true;
            emit statusMessage(tr("Отключен"));
        }
        else
        {
            QSettings settings("server.ini",QSettings::IniFormat);
            settings.beginGroup("SQLCONFIG");
            settings.setValue("login",dialog.userName());
            settings.setValue("password",dialog.password());
            settings.setValue("server",dialog.hostName());
            settings.setValue("db",dialog.dataBase());
            settings.setValue("port",dialog.port());
            settings.endGroup();
        }
    }
}

Library::~Library()
{
    if(searchAccount) delete searchAccount;
}
