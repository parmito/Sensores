#include "DigitalDisplay.h"

DigitalDisplay::DigitalDisplay(QWidget *parent) : QLCDNumber(parent)
{
    setMode(QLCDNumber::Dec);
    setStyleSheet("background-color: lightgray;"
                  "border-radius: 20px;");
    setSegmentStyle(Filled);
}
