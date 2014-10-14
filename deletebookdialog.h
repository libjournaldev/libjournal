#ifndef DELETEBOOKDIALOG_H
#define DELETEBOOKDIALOG_H

#include <QWidget>

namespace Ui {
class deleteBookDialog;
}

class deleteBookDialog : public QWidget
{
    Q_OBJECT

public:
    explicit deleteBookDialog(QWidget *parent = 0);
    ~deleteBookDialog();

private:
    Ui::deleteBookDialog *ui;
};

#endif // DELETEBOOKDIALOG_H
