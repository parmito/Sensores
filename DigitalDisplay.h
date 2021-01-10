#ifndef ODOMETER_H
#define ODOMETER_H

#include <QLCDNumber>
#include <QWidget>

class DigitalDisplay : public QLCDNumber
{
    Q_OBJECT
public:
    explicit DigitalDisplay(QWidget *parent = nullptr);
};

#endif // ODOMETER_H
