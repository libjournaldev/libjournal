#include "editaccountdialog.h"
#include "ui_editaccountdialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

EditAccountDialog::EditAccountDialog(QWidget *parent, const QSqlRecord &rec) :
    QDialog(parent),
    ui(new Ui::EditAccountDialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/images/editAccount.png"));
    setWindowTitle(tr("Редактирование карты (ID %1)").arg(rec.value(0).toInt()));

    QSqlDatabase activeDB = QSqlDatabase::database("libj");
    QStringList departments;
    QSqlQuery query("SELECT * FROM departmentTable", activeDB);
    while(query.next()) departments << query.value("departmentFullName").toString();
    ui->departmentComboBox->addItems(departments);

    ui->nameLineEdit->setText(rec.value("readerName").toString());
    ui->surnameLineEdit->setText(rec.value("readerSurname").toString());
    ui->middleNameLineEdit->setText(rec.value("readerMiddleName").toString());
    ui->adressLineEdit->setText(rec.value("readerAdress").toString());
    ui->telephoneLineEdit->setText(rec.value("readerTelephone").toString());
    ui->birthDateEdit->setDate(rec.value("readerBirthDate").toDate());
    ui->regDateEdit->setDate(rec.value("readerRegDate").toDate());
    int depID = rec.value("readerDepartmentID").toInt()-1;
    ui->departmentComboBox->setCurrentIndex(depID);

    // ui->birthDateEdit->date().toString("yyyy-MM-dd");
}

EditAccountDialog::~EditAccountDialog()
{
    delete ui;
}
