#include "Instrumentpanel.h"

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPalette>
#include <QSound>
#include <QSoundEffect>
#include <Sound.h>
#include <string>


#include <QtAndroidExtras/QtAndroid>
#include <QStandardPaths>
#include <QtGlobal>
#include <QFile>
#include <QDir>

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
    dAvgSpeed = 0;
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
                            "border-radius: 20px;"
                            "padding: 6px;"
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
                            "selection-color : white;"
                            "selection-background-color: lime;"
                            "background-color: lime;"
                            "border-color: lime;"
                            "text-decoration:none;"
                            "border-radius: 10px;"
                            "border-style: outset;"
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
    Odometer->setDigitCount(6);
    Odometer->setParent(this);

    t = new QTime(0, 0, 0);
    Time = new DigitalDisplay();
    Time->setGeometry(200,1650,600,200);
    Time->setDigitCount(8);
    Time->setParent(this);


    /*selectSpeed->setParent(this);*/

    QString qstFolder=QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString kmlHeader = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?> \r\n"
                                    "<kml xmlns=\"http://earth.google.com/kml/2.0\"> \r\n"
                                    " <Document>\r\n"
                                    "    <name>%1</name>\r\n"
                                    "    <visibility>0</visibility>\r\n"
                                    "    <open>1</open>\r\n");

    /*qWarning("Folder=%s",qPrintable(qstFolder));*/

    if(requestAndroidPermissions() == true)
    {
        qstFileName = QDateTime::currentDateTime().toString("/ddMMyyyy_hh:mm:ss");
        FileName=new QFile(qstFolder+qstFileName+".KML");

        QString formattedKmlHeader = kmlHeader.arg(qstFileName.replace("/","Rota_"));

        if (!FileName->exists())
        {
            /* create the folder, if necessary*/
            QDir* dir=new QDir(qstFolder);
            if (!dir->exists())
            {
                dir->mkpath(qstFolder);
            }
            FileName->open(QIODevice::WriteOnly);
            FileName->write(formattedKmlHeader.toLatin1());
            FileName->close();
        }

        /*if (FileName->exists())
        {
            qWarning("file exists");
            FileName->open(QIODevice::ReadOnly);
            QByteArray data=FileName->readAll();
            qWarning("file data=%s",data.constData());
            FileName->close();
        }*/
    }    
    i64PreviousTimestamp = QDateTime::currentMSecsSinceEpoch();
    iIndex = 0;
}

void InstrumentPanel::SlotReceiveEndKmlFile()
{
    QString kmlEndFile = QString("  </Document>\n"
                                    "</kml>");

    qDebug() << "End KML File";
    if(requestAndroidPermissions() == true)
    {
        if (FileName->exists())
        {
            FileName->open(QIODevice::WriteOnly | QIODevice::Append);
            FileName->write(kmlEndFile.toLatin1());
            FileName->close();
        }
    }
}


void InstrumentPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    circle = new QPainter(this);

    circle->setRenderHint(QPainter::Antialiasing, true);
    circle->translate(width() / 2, height() / 2);


    circle->setPen(QPen(Qt::lightGray, 50, Qt::SolidLine, Qt::RoundCap));
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
    circle->setPen(QPen(Qt::lightGray, 50, Qt::SolidLine, Qt::RoundCap));
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

    Time->display(t->toString());
    Time->show();

}

void InstrumentPanel::SlotReceiveLatLongAltSpeedTimestampDistance(QString Lat,QString Long,QString Alt,QString Speed,QString Timestamp,double Distance)
{
    this->Latitude = Lat;
    this->Longitude = Long;
    this->Altitude = Alt;
    this->Speed = Speed;
    this->Timestamp = Timestamp;


    QString kmlData = QString("<Placemark>\r\n"
                                " <name>%1</name>\r\n"
                                " <description>Speed:%2,Time:%6</description>\r\n"
                                " <Point>\r\n"
                                "  <coordinates>%3,%4,%5</coordinates>\r\n"
                                " </Point>\r\n"
                                "</Placemark>\r\n");

    this->iIndex++;

    QString kmlDataFormatted = kmlData.arg(QString::number(this->iIndex),this->Speed,this->Longitude,this->Latitude,this->Altitude,this->Timestamp);

    if(requestAndroidPermissions() == true)
    {
        if (FileName->exists())
        {
            FileName->open(QIODevice::WriteOnly | QIODevice::Append);
            FileName->write(kmlDataFormatted.toLatin1());
            FileName->close();

        }
    }

    ProcessingSpeed(this->Speed);
    ProcessingTimestamp(this->Timestamp);
    ProcessingDistance(Distance);
}



void InstrumentPanel::ProcessingSpeed(QString value)
/*void InstrumentPanel::SlotReceiveSpeed(QString value)*/
{
    speed = value;
    iCurrentSpeed = speed.toInt();
    dCurrentSpeed = speed.toDouble();

    if(lNumberOfSamples > 0)
    {
        dAvgSpeed = dAvgSpeed + (dCurrentSpeed - dAvgSpeed)/lNumberOfSamples;
        lNumberOfSamples++;
    }
    else
    {
        lNumberOfSamples++;
        dAvgSpeed = ((lNumberOfSamples-1)*dAvgSpeed +dCurrentSpeed)/lNumberOfSamples;
        lNumberOfSamples++;
    }

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

    iAvgSpeed = (int)dAvgSpeed;
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

void InstrumentPanel::ProcessingDistance(double distance)
/*void InstrumentPanel::SlotReceiveDistance(double distance)*/
{
    dOdometer +=distance;
}

void InstrumentPanel::ProcessingTimestamp(QString timestamp)
/*void InstrumentPanel::SlotReceiveTimestamp(QString timestamp)*/
{
    int64_t i64CurrentMSec,i64DeltaMSec;

    i64CurrentMSec = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    i64DeltaMSec = i64CurrentMSec - i64PreviousTimestamp;
    i64PreviousTimestamp = i64CurrentMSec;

    qDebug()<<"DeltaTimestamp::"<<i64DeltaMSec;

    QTime n;
    n = t->addMSecs(i64DeltaMSec);
    *t = n;

    Q_UNUSED(timestamp);



/*    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1] ").arg(dt);


    QFile outFile(":/LogFile.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&outFile);
    textStream << txt << Qt::endl;

    outFile.close();*/
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



bool InstrumentPanel::requestAndroidPermissions(){

    const QVector<QString> permissions({"android.permission.WRITE_EXTERNAL_STORAGE",
                                        "android.permission.READ_EXTERNAL_STORAGE"});

    for(const QString &permission : permissions){
        auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return false;
        }
    }

    return true;
}


