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
#include "DigitalDisplay.h"

class InstrumentPanel : public QWidget
{
    Q_OBJECT
public:
    explicit InstrumentPanel(QWidget *parent = nullptr);
signals:
    void SignalSendDistance(double);
protected:
     void paintEvent(QPaintEvent *event);

public slots:
    void SlotReceiveSpeed(QString);
    void SlotReceiveDistance(long);
    void SlotReceiveSoundCheckBox(int state);

private:
    QString speed,strMaxSpeed,strAvgSpeed;
    QPainter *circle;
    QColor innerColor,archColor,archColorMaxSpeed,archColorAvgSpeed;
    QRect  speedTextPosition,AvgSpeedTextPosition,MaxSpeedTextPosition;
    int startAngle,spanAngle ;
    int spanAngleMaxSpeed,spanAngleAvgSpeed;
    int iCurrentSpeed,iAvgSpeed,iMaxSpeed;
    QCheckBox *checkBoxSound;
    QComboBox *selectSpeed;

    DigitalDisplay *Odometer;
    double dOdometer;
};

#endif // INSTRUMENTPANEL_H
