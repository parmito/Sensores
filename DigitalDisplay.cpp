#include "DigitalDisplay.h"

DigitalDisplay::DigitalDisplay(QWidget *parent) : QLCDNumber(parent)
{
    setMode(QLCDNumber::Dec);
    setSegmentStyle(Filled);
}
