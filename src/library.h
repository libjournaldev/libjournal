#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>
#include "ui_library.h"

class Library : public QWidget, private Ui::Library
{
    Q_OBJECT

public:
    Library(QWidget *parent = 0);
    virtual ~Library();
    void somevoid();
public slots:
    void initConnection();
signals:
    void statusMessage(const QString &message);

};

#endif // LIBRARY_H
