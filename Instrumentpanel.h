#ifndef INSTRUMENTPANEL_H
#define INSTRUMENTPANEL_H

#include <QObject>
#include <QLabel>
#include <QPaintEvent>
#include <QWidget>
#include <QDockWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLCDNumber>
#include <QTime>
#include "DigitalDisplay.h"

class InstrumentPanel : public QWidget
{
    Q_OBJECT
public:
    explicit InstrumentPanel(QWidget *parent = nullptr);
    /*~InstrumentPanel();*/ // destructor
    void ProcessingSpeed(QString);
    void ProcessingDistance(double);
    void ProcessingTimestamp(QString);
signals:
    void SignalSendDistance(double);
protected:
     void paintEvent(QPaintEvent *event);
     bool requestAndroidPermissions();

public slots:
    void SlotReceiveLatLongAltSpeedTimestampDistance(QString,QString,QString,QString,QString,double);
    void SlotReceiveSoundCheckBox(int state);
    void SlotReceiveEndKmlFile(void);

private:
    QString speed,strMaxSpeed,strAvgSpeed;
    QPainter *circle;
    QColor innerColor,archColor,archColorMaxSpeed,archColorAvgSpeed;
    QRect  speedTextPosition,AvgSpeedTextPosition,MaxSpeedTextPosition;
    int startAngle,spanAngle ;
    int spanAngleMaxSpeed,spanAngleAvgSpeed;
    int iCurrentSpeed,iAvgSpeed,iMaxSpeed;    
    double dCurrentSpeed,dAvgSpeed;
    QCheckBox *checkBoxSound;
    QComboBox *selectSpeed;

    DigitalDisplay *Odometer;
    DigitalDisplay *Time;
    QTime *t;
    double dOdometer;
    long lNumberOfSamples;
    int64_t i64PreviousTimestamp;
    QString qstFileName,qstFolder;
    QFile *FileName;
    QString Latitude;
    QString Longitude;
    QString Altitude;
    QString Speed;
    QString Timestamp;
    int iIndex;
};

#endif // INSTRUMENTPANEL_H
