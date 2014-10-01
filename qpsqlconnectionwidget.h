#ifndef QPSQLCONNECTIONWIDGET_H
#define QPSQLCONNECTIONWIDGET_H

#include <QDialog>

namespace Ui {
class QPSQLConnectionWidget;
}

class QPSQLConnectionWidget : public QDialog
{
    Q_OBJECT

public:
    explicit QPSQLConnectionWidget(QWidget *parent = 0);
    ~QPSQLConnectionWidget();

private:
    Ui::QPSQLConnectionWidget *ui;
};

#endif // QPSQLCONNECTIONWIDGET_H
