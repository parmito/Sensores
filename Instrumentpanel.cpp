#include "Instrumentpanel.h"

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPalette>
#include <QSound>
#include <QSoundEffect>
#include <Sound.h>

InstrumentPanel::InstrumentPanel(QWidget *parent) : QWidget(parent)
{
    speed = "0";

    innerColor = Qt::yellow;
    archColor = Qt::gray;
    archColorMaxSpeed = QColor(250,38,160);
    archColorAvgSpeed = QColor(247,148,137);

    speedTextPosition = QRect(-70,130,700,700);

    startAngle = 225*16;

    spanAngle = 0;
    spanAngleMaxSpeed = 0;
    spanAngleAvgSpeed = 0;

    iCurrentSpeed = 0;
    iAvgSpeed = 0;
    iMaxSpeed = 0;
    lNumberOfSamples = 1;

    checkBoxSound = new QCheckBox("Sound ON",this);


    /*"border-width: 10px;"
    "border-color: lime;"
    "border-width: 2px;"
    "border-radius: 20px;"
    "border-color: beige;"*/

    checkBoxSound->setStyleSheet("color: black;"
                            "background-color: lime;"
                            "selection-color: white;"
                            "selection-background-color: lime;"
                            "text-decoration:none;"
                            "border-style:none;");


    checkBoxSound->setGeometry(10,0,400,100);
    checkBoxSound->setCheckState(Qt::Checked);
    /*checkBoxSound->setParent(this);*/
    connect(checkBoxSound,SIGNAL(stateChanged(int)),this,SLOT(SlotReceiveSoundCheckBox(int)));


    selectSpeed = new QComboBox(this);

    /*QPalette pal = palette();
     set black background */
    /*pal.setColor(QPalette::Background, Qt::green);
    selectSpeed->setAutoFillBackground(true);
    selectSpeed->setPalette(pal);*/

    /*selectSpeed->setStyleSheet("background-color:green");*/



    /*"min-width: 50em;"*/
    /*"padding: 6px;"*/
    /*"border-style: outset;"*/
    /*"font: bold 14px;"*/
    /*"border-style: outset;"*/
    /*"background-color: white;"*/
    /*"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);"*/
    selectSpeed->setStyleSheet("color: black;"                            
                            "selection-color: white;"
                            "selection-background-color: lime;"
                            "background-color: lime;"
                            "border-width: 50px;"
                            "border-color: lime;"
                            "border-radius: 20px;"
                            "cursor: none;"
                            "text-decoration:none;"
                            "border-style:none;");


    selectSpeed->addItem("50 Km/h", Qt::DisplayRole);
    selectSpeed->addItem("60 Km/h", Qt::DisplayRole);
    selectSpeed->addItem("100 Km/h", Qt::DisplayRole);
    selectSpeed->addItem("110 Km/h", Qt::DisplayRole);
    selectSpeed->addItem("120 Km/h", Qt::DisplayRole);
    selectSpeed->addItem("130 Km/h", Qt::DisplayRole);

    selectSpeed->setGeometry(600,0,400,100);

    dOdometer = 0;
    Odometer = new DigitalDisplay();
    Odometer->setGeometry(300,1400,400,200);
    Odometer->setMode(QLCDNumber::Dec);
    Odometer->setDigitCount(6);
    Odometer->setParent(this);


    /*selectSpeed->setParent(this);*/
}

void InstrumentPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    circle = new QPainter(this);

    circle->setRenderHint(QPainter::Antialiasing, true);
    circle->translate(width() / 2, height() / 2);


    circle->setPen(QPen(Qt::black, 50, Qt::SolidLine, Qt::RoundCap));
    circle->drawEllipse(QRect(-800 / 2, -800 / 2, 800, 800));


    circle->setPen(QPen(innerColor, 50, Qt::SolidLine, Qt::RoundCap));
    circle->drawEllipse(QRect(-700 / 2, -700 / 2, 700, 700));

    QRect boundingRect;
    QFont font = circle->font();
    font.setPixelSize(180);
    font.setBold(true);
    circle->setFont(font);


    /*  Speed   */
    circle->setPen(QPen(Qt::gray, 50, Qt::SolidLine, Qt::RoundCap));
    font.setPixelSize(180);
    font.setBold(true);
    circle->setFont(font);
    circle->drawText(speedTextPosition,0, speed, &boundingRect);

    /*    Km/h  */
    circle->setPen(QPen(Qt::black, 50, Qt::SolidLine, Qt::RoundCap));
    font.setPixelSize(140);
    font.setBold(true);
    circle->setFont(font);
    circle->drawText(QRect(-165 ,-100, 600, 600),0, tr("Km/h"), &boundingRect);

    /*    Max Speed */
    circle->setPen(QPen(archColorMaxSpeed, 50, Qt::SolidLine, Qt::RoundCap));
    font.setPixelSize(80);
    font.setBold(true);
    circle->setFont(font);
    circle->drawText(MaxSpeedTextPosition,0, strMaxSpeed, &boundingRect);

    /*    Avg Speed */
    circle->setPen(QPen(archColorAvgSpeed, 75, Qt::SolidLine, Qt::RoundCap));
    font.setPixelSize(80);
    font.setBold(true);
    circle->setFont(font);
    circle->drawText(AvgSpeedTextPosition,0, strAvgSpeed, &boundingRect);


    /*    Max Speed Arch  */    
    circle->setPen(QPen(archColorMaxSpeed, 50, Qt::SolidLine, Qt::SquareCap));    
    circle->drawArc(QRect(-600 / 2, -600 / 2, 600, 600),startAngle,spanAngleMaxSpeed);

    /*    Avg Speed Arch  */
    circle->setPen(QPen(archColorAvgSpeed, 50, Qt::SolidLine, Qt::SquareCap));
    circle->drawArc(QRect(-500 / 2, -500 / 2, 500, 500),startAngle,spanAngleAvgSpeed);

    /*    Speed Arch  */
    circle->setPen(QPen(archColor, 50, Qt::SolidLine, Qt::SquareCap));
    circle->drawArc(QRect(-400 / 2, -400 / 2, 400, 400),startAngle,spanAngle);
    circle->end();


    Odometer->display(dOdometer);
    Odometer->show();
}


void InstrumentPanel::SlotReceiveSpeed(QString value)
{
    speed = value;
    iCurrentSpeed = speed.toInt();

    if((iCurrentSpeed > 0) && (lNumberOfSamples > 0))
    {
        iAvgSpeed = ((lNumberOfSamples-1)*iAvgSpeed +iCurrentSpeed)/lNumberOfSamples;
        lNumberOfSamples++;
    }
    else
    {
        if(lNumberOfSamples == 0)
        {
            lNumberOfSamples++;
            iAvgSpeed = ((lNumberOfSamples-1)*iAvgSpeed +iCurrentSpeed)/lNumberOfSamples;
            lNumberOfSamples++;
        }
    }

    /*static int i = 0;
    spanAngle = -(i) * ((225/210)*16);
    i++;*/


    if (iCurrentSpeed > iMaxSpeed)
    {
        iMaxSpeed = iCurrentSpeed;
    }

    if(iCurrentSpeed >=100)
    {
        speedTextPosition = QRect(-160 , 130, 700, 700);
    }
    else
    {
        if(iCurrentSpeed >=10)
        {
            speedTextPosition = QRect(-100 , 130, 700, 700);
        }
        else
        {
            speedTextPosition = QRect(-60 , 130, 700, 700);
        }
    }

    if(iAvgSpeed >=100)
    {
        AvgSpeedTextPosition = QRect(-60 , 90, 700, 700);
    }
    else
    {
        if(iAvgSpeed >=10)
        {
            AvgSpeedTextPosition = QRect(-40 , 90, 700, 700);
        }
        else
        {
            AvgSpeedTextPosition = QRect(-30 , 85, 700, 700);
        }
    }

    if(iMaxSpeed >=100)
    {
        MaxSpeedTextPosition = QRect(-60 , 25, 700, 700);
    }
    else
    {
        if(iMaxSpeed >=10)
        {
            MaxSpeedTextPosition = QRect(-40 , 25, 700, 700);
        }
        else
        {
            MaxSpeedTextPosition = QRect(-30 , 25, 700, 700);
        }
    }


    int iThresholdSpeed;
    switch (selectSpeed->currentIndex())
    {
        case 0:
            iThresholdSpeed = 50;
        break;

        case 1:
            iThresholdSpeed = 60;
        break;

        case 2:
            iThresholdSpeed = 100;
        break;

        case 3:
            iThresholdSpeed = 110;
        break;

        case 4:
            iThresholdSpeed = 120;
        break;

        case 5:
            iThresholdSpeed = 130;
        break;

        default:
            iThresholdSpeed = 50;
            break;
    }

    if(iCurrentSpeed >= iThresholdSpeed)
    {
        innerColor = Qt::red;
        if(checkBoxSound->isChecked() == true)
        {
            QSound::play("assets:/sounds/alert.wav");
        }
    }
    else
    {
        innerColor = Qt::green;
    }
    spanAngle = -(iCurrentSpeed) * ((264/210)*16);
    spanAngleAvgSpeed = -(iAvgSpeed) * ((264/210)*16);
    spanAngleMaxSpeed = -iMaxSpeed * ((264/210)*16);

    strMaxSpeed = QString::number(iMaxSpeed);
    strAvgSpeed = QString::number(iAvgSpeed);
    update();
}

void InstrumentPanel::SlotReceiveDistance(double distance)
{
    dOdometer +=distance;
}

void InstrumentPanel::SlotReceiveSoundCheckBox(int state)
{
    qDebug()<<"SlotReceiveSoundCheckBox";

    if(state == Qt::Checked)
    {
        qDebug()<<"SOUND ON";
        checkBoxSound->setText("Sound ON");
    }
    else
    {
        qDebug()<<"SOUND OFF";
        checkBoxSound->setText("Sound OFF");
    }
}





