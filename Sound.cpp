#include "Sound.h"

#include <QStyle>

Sound::Sound(QWidget *parent) : QWidget(parent)
{    
    ptrCheckBox = new QCheckBox("SOUND ON", NULL);
    ptrCheckBox->setFixedSize(20,20);
    /*ptrCheckBox->setStyle(QStyle::CT_CheckBox);*/
    ptrCheckBox->setCheckState(Qt::Checked);
    ptrCheckBox->animateClick(1000);
}
