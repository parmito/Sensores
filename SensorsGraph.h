#ifndef SENSORSGRAPH_H
#define SENSORSGRAPH_H

#include <QDebug>
#include <QTimer>
#include <QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QWidget>


using namespace QtCharts;

class SensorsGraph : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsGraph(QWidget *parent = nullptr,const QString title = "Title", QChart::ChartTheme theme = QChart::ChartThemeBrownSand );
    QChartView *Chart(void);
    void setPen(const QPen &pen);

signals:

public slots:
    void UpdateSlot();
    void AccelerometerUpdate(qreal);

private:
    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;
    QTimer *myTimer;
    QValueAxis *axisX,*axisY;
    qreal x,y,ymax;
    qreal localYmax,localYmin,localXmax;
    QPen *localPen;
};

#endif // SENSORSGRAPH_H
