#ifndef SENSORAPP_H
#define SENSORAPP_H
// SensorsApp.h

#include <QObject>
#include <QCompass>
#include <QAccelerometer>
#include <QTimer>
#include <QAltimeter>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QAmbientTemperatureReading>
#include <QGeoSatelliteInfo>

class SensorsApp : public QObject
{
    Q_OBJECT
public:

    explicit SensorsApp(QObject *parent = 0);
    virtual ~SensorsApp() {}

signals:
    void cppSendAccelX(QString);
    void cppSignalNumberAccelX(qreal);
    void cppSendAccelXInt(qreal,qreal);

    void cppSendAccelY(QString);
    void cppSignalNumberAccelY(qreal);
    void cppSendAccelYInt(qreal,qreal);

    void cppSendAccelZ(QString);
    void cppSignalNumberAccelZ(qreal);
    void cppSendAccelZInt(qreal,qreal);

    void cppSendLatLongAltSpeedTimestampDistance(QString,QString,QString,QString,QString,double);
public slots:
    void compassReadingChanged();
    void accelerometerReadingChanged(); 
    void positionUpdate(const QGeoPositionInfo &info);
    void temperatureUpdated();
private:
    QCompass *m_CompassSensor;    
    QAccelerometer *m_AccelerometerSensor;
    QAltimeter *m_AltimeterSensor;
    QGeoPositionInfoSource *m_GeoPositionSensor;
    QAmbientTemperatureSensor *m_AmbientTemperatureSensor;
    int theValue;
    QTimer *myTimer;
    qreal x;
    double CurrentLatitude,CurrentLongitude,PreviousLatitude,PreviousLongitude,dDistance,dPreviousSpeed;
    long double toRadians(const long double degree);
    long double distance(long double lat1, long double long1,long double lat2, long double long2);

};
#endif /* SENSORSAPP_H_ */
