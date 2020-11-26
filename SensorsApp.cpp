// SensorsApp.cpp
#include "SensorsApp.h"
#include <QDebug>
#include <QGeoSatelliteInfoSource>


SensorsApp::SensorsApp(QObject *parent)
    : QObject(parent)
{               
    /*myTimer = new QTimer(this);
    myTimer->start(5000);
    connect(myTimer, SIGNAL (timeout()), this, SLOT (PeriodicFunction()));*/


    CurrentLatitude = CurrentLongitude = PreviousLatitude = PreviousLongitude = 0;

    // Create the compass sensor
    m_CompassSensor = new QCompass(this);
    m_AccelerometerSensor =  new QAccelerometer(this);
    m_AltimeterSensor =  new QAltimeter(this);
    m_AmbientTemperatureSensor = new QAmbientTemperatureSensor(this);

    QGeoPositionInfoSource *m_GeoPositionSensor = QGeoPositionInfoSource::createDefaultSource(this);

    if (m_GeoPositionSensor) {
               connect(m_GeoPositionSensor, SIGNAL(positionUpdated(QGeoPositionInfo)),
                       this, SLOT(positionUpdated(QGeoPositionInfo)));
               m_GeoPositionSensor->startUpdates();
           }

    if(m_AmbientTemperatureSensor){
        qDebug() << "Ambient Temperature Sensor exists";
        connect(m_AmbientTemperatureSensor, SIGNAL(readingChanged()),
                this, SLOT(temperatureUpdated()));
    }

    // Set the orientation mode to fixed so that sensor
    // readings aren't affected by device orientation
    m_CompassSensor->setAxesOrientationMode
                        (QCompass::FixedOrientation);

    /*bool res = connect(m_CompassSensor,
                       SIGNAL(readingChanged()),
                       this,
                       SLOT(compassReadingChanged()));*/


    m_AccelerometerSensor->setAccelerationMode(QAccelerometer::Combined);

    bool res = connect(m_AccelerometerSensor,
                       SIGNAL(readingChanged()),
                       this,
                       SLOT(accelerometerReadingChanged()));

    /*res = connect(m_AltimeterSensor,
                       SIGNAL(readingChanged()),
                       this,
                       SLOT(altimeterReadingChanged()));*/
    Q_ASSERT(res);
    Q_UNUSED(res);

    m_CompassSensor->start();
    m_AccelerometerSensor->start();
    /*m_AltimeterSensor->start();*/
    m_AmbientTemperatureSensor->start();

}

void SensorsApp::compassReadingChanged()
{
    QCompassReading *reading = m_CompassSensor->reading();

    qreal azimuth = reading->azimuth();
    qDebug() << "The azimuth is" << azimuth << "degrees.";
}

void SensorsApp::accelerometerReadingChanged()
{
    /*qDebug() << "Slot:accelerometerReadingChanged";*/
    static qreal PreviousX = 0;
    static qreal PreviousY = 0;
    static qreal PreviousZ = 0;
    /*static qreal xLineSeriesAxisAccelX = 0,xLineSeriesAxisAccelY = 0, xLineSeriesAxisAccelZ = 0;*/

    QAccelerometerReading *reading = m_AccelerometerSensor->reading();

    if(reading != nullptr)
    {
        qreal x = (qint32)(reading->x()*10);
        qreal y = (qint32)(reading->y()*10);
        qreal z = (qint32)(reading->z()*10);

        x = (int)x/10;
        y = (int)y/10;
        z = (int)z/10;


        /*qDebug() << "X:" << QString::number(x) << "degrees.";
        qDebug() << "Y:" << QString::number(y) << "degrees.";
        qDebug() << "Z:" << QString::number(z) << "degrees.";*/


        if (( x > 0 && x > PreviousX*1.2) || ( x < 0  && x < PreviousX*1.2))
        {
            PreviousX = x;
            emit SensorsApp::cppSendAccelX(QString::number(x));
            emit SensorsApp::cppSignalNumberAccelX(x);
            /*xLineSeriesAxisAccelX++;*/
            /*emit SensorsApp::cppSendAccelXInt(xLineSeriesAxisAccelX,x);*/
        }

        if (( y > 0 && y > PreviousY*1.2) || ( y < 0  && y < PreviousY*1.2))
        {
            PreviousY = y;
            emit SensorsApp::cppSendAccelY(QString::number(y));
            emit SensorsApp::cppSignalNumberAccelY(y);
            /*xLineSeriesAxisAccelY++;*/
            /*emit SensorsApp::cppSendAccelYInt(xLineSeriesAxisAccelY,y);*/
        }

        if (( z > 0 && z > PreviousZ*1.2) || ( z < 0  && z < PreviousZ*1.2))
        {
            PreviousZ = z;
            emit SensorsApp::cppSendAccelZ(QString::number(z));
            emit SensorsApp::cppSignalNumberAccelZ(z);
            /*xLineSeriesAxisAccelZ++;*/
            /*emit SensorsApp::cppSendAccelYInt(xLineSeriesAxisAccelY,y);*/
        }
        /*QString str;
        str = QString("%1").arg(x, 0, 'g', 13);*/
    }
}

void SensorsApp::altimeterReadingChanged()
{
    QAltimeterReading *reading = m_AltimeterSensor->reading();
    static qreal PreviousAltitude = 0;

    if(reading != nullptr)
    {

        qreal altitude = reading->altitude();
        qDebug() << "The altitude is" << altitude << "meters.";

        if (altitude != PreviousAltitude) emit SensorsApp::cppSendAltitude(QString::number(altitude));
    }
}


 /*void SensorsApp::PeriodicFunction() {
    qDebug() << "PeriodicFunction()";
}*/


void SensorsApp::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "Position updated:" << info;

    QDateTime timestamp = info.timestamp();
    /*QDate Day = timestamp.date();*/
    QDateTime Time = timestamp.toLocalTime();

    QGeoCoordinate position = info.coordinate();

    CurrentLatitude = position.latitude();
    CurrentLongitude= position.longitude();
    double altitude = (qint32)(position.altitude()*10);
    int speed = (qint32)(info.attribute(QGeoPositionInfo::GroundSpeed)*36);

    altitude = altitude/10;
    speed = speed/10;

    if((PreviousLatitude != 0) && (PreviousLongitude != 0))
    {
        if((CurrentLatitude != PreviousLatitude) || (CurrentLongitude != PreviousLongitude))
        {
            lDistance = distance(PreviousLatitude, PreviousLongitude,
                                 CurrentLatitude, CurrentLongitude);
        }
    }

    PreviousLatitude = CurrentLatitude;
    PreviousLongitude= CurrentLongitude;

    emit SensorsApp::cppSendTimestamp(Time.toString());
    emit SensorsApp::cppSendLatitude(QString::number(CurrentLatitude));
    emit SensorsApp::cppSendLongitude(QString::number(CurrentLongitude));
    emit SensorsApp::cppSendAltitude(QString::number(altitude));
    emit SensorsApp::cppSendSpeed(QString::number(speed));    
    emit SensorsApp::cppSendDistance(lDistance);
}

void SensorsApp::temperatureUpdated()
{
    qDebug() << "Temperature updated";
    /*QAmbientTemperatureReading *reading = m_AmbientTemperatureSensor->reading();
    qDebug() << "Temperature:" << reading->temperature();*/
}

// Utility function for
// converting degrees to radians
long double SensorsApp::toRadians(long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double SensorsApp::distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}
