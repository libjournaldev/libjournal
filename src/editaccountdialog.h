#ifndef EDITACCOUNTDIALOG_H
#define EDITACCOUNTDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class EditAccountDialog;
}

class EditAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAccountDialog(QWidget *parent, const QSqlRecord &rec);
    ~EditAccountDialog();

    QSqlRecord getEditedAccount() const;

private:
    Ui::EditAccountDialog *ui;
};

#endif // EDITACCOUNTDIALOG_H
