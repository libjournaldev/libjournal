#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>

namespace Ui {
class Library;
}

class Library : public QWidget
{
    Q_OBJECT

public:
    Library(QWidget *parent = 0);
    ~Library();

private:
    Ui::Library *ui;
};

#endif // LIBRARY_H
