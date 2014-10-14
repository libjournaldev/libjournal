#ifndef SPINBOX_H
#define SPINBOX_H

#include <QSpinBox>

class SpinBox : public QSpinBox
{
    Q_OBJECT
public:
    SpinBox(QWidget *parent = 0) : QSpinBox(parent) {}

    virtual int valueFromText(const QString &text) const
    {
      if (text.isEmpty())
        return minimum();
      return QSpinBox::valueFromText(text);
    }
    virtual QString textFromValue(int v) const
    {
      if (v == minimum())
        return QString();
      return QSpinBox::textFromValue(v);
    }
};

#endif // SPINBOX_H
