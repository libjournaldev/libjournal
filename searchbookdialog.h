#ifndef SEARCHBOOKDIALOG_H
#define SEARCHBOOKDIALOG_H

#include <QWidget>

namespace Ui {
class searchbookdialog;
}

class searchbookdialog : public QWidget
{
    Q_OBJECT

public:
    explicit searchbookdialog(QWidget *parent = 0);
    ~searchbookdialog();

private:
    Ui::searchbookdialog *ui;
};

#endif // SEARCHBOOKDIALOG_H
