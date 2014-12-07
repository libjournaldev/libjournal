#include "editaccountdialog.h"
#include "ui_editaccountdialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QMessageBox>
#include <QDebug>

EditAccountDialog::EditAccountDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowIcon(QIcon(":/images/addAccount.png"));
    setWindowTitle("Новый читатель");
    dropAccountButton->hide();
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QRegExp re("(00)?([[3-9]\\d{1,2})(\\d{2})(\\d{7})$");
    telephoneLineEdit->setValidator(new QRegExpValidator(re, this));

    regDateEdit->setDate(QDate::currentDate());
    QSqlDatabase activeDB = QSqlDatabase::database("libj");
    QStringList departments;
    QSqlQuery q("SELECT * FROM departmentTable",activeDB);
    while(q.next()) departments << q.value("departmentFullName").toString();
    departmentComboBox->addItems(departments);

}

EditAccountDialog::EditAccountDialog(QWidget *parent, const QSqlRecord &rec) :
    QDialog(parent)
{
    setupUi(this);
    setWindowIcon(QIcon(":/images/editAccount.png"));
    setWindowTitle(tr("Редактирование карты (ID %1)").arg(rec.value(0).toInt()));

    QSqlDatabase activeDB = QSqlDatabase::database("libj");
    QStringList departments;
    QSqlQuery query("SELECT * FROM departmentTable", activeDB);
    while(query.next()) departments << query.value("departmentFullName").toString();
    departmentComboBox->addItems(departments);

    nameLineEdit->setText(rec.value("readerName").toString());
    surnameLineEdit->setText(rec.value("readerSurname").toString());
    middleNameLineEdit->setText(rec.value("readerMiddleName").toString());
    adressLineEdit->setText(rec.value("readerAdress").toString());
    telephoneLineEdit->setText(rec.value("readerTelephone").toString());
    birthDateEdit->setDate(rec.value("readerBirthDate").toDate());
    regDateEdit->setDate(rec.value("readerRegDate").toDate());
    regDateEdit->setReadOnly(true);
    int depID = rec.value("readerDepartmentID").toInt()-1;
    departmentComboBox->setCurrentIndex(depID);

    QRegExp re("(00)?([[3-9]\\d{1,2})(\\d{2})(\\d{7})$");
    telephoneLineEdit->setValidator(new QRegExpValidator(re, this));
}

void EditAccountDialog::on_dropAccountButton_clicked()
{
    int ans = QMessageBox::critical(this, "Удалить карту", "Вы уверены?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (ans == QMessageBox::Yes) emit done(-1); // -1 - код для searchaccountwidget.cpp:106
}

EditAccountDialog::~EditAccountDialog()
{

}
