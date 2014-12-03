#ifndef EDITACCOUNTDIALOG_H
#define EDITACCOUNTDIALOG_H

#include "ui_editaccountdialog.h"
#include <QDialog>
#include <QSqlRecord>

class EditAccountDialog : public QDialog, private Ui::EditAccountDialog
{
    Q_OBJECT

public:
    EditAccountDialog(QWidget *parent, const QSqlRecord &rec);
    EditAccountDialog(QWidget *parent = 0);
    ~EditAccountDialog();

    QString readerName() const { return nameLineEdit->text(); }
    QString readerSurname() const { return surnameLineEdit->text(); }
    QString readerMiddleName() const { return middleNameLineEdit->text(); }
    QString readerAdress() const { return adressLineEdit->text(); }
    QString readerTelephone() const { return telephoneLineEdit->text(); }
    QString readerBirthDate() const { return birthDateEdit->date().toString("yyyy-MM-dd"); }
    int readerDepartment() const { return departmentComboBox->currentIndex()+1; }

};

#endif // EDITACCOUNTDIALOG_H
