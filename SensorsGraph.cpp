#include "SensorsGraph.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QScreen>
using namespace QtCharts;

SensorsGraph::SensorsGraph(QWidget *parent,const QString title,QChart::ChartTheme theme ) : QWidget(parent)
{
    localYmax = 0;
    localYmin = 0;
    localXmax = 0;

    series = new QLineSeries();
    /*series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);*/

    chart = new QChart();
    chart->legend()->hide();    
    chart->addSeries(series);
    /*chart->createDefaultAxes();*/
    chart->setTitle(title);
    const QFont Font("Courier", 12, QFont::Courier, false);
    chart->setTitleFont(Font);

    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(theme);

    /*const QBrush brush("black",Qt::SolidPattern );
    chart->setBackgroundBrush(brush);*/

    axisX = new QValueAxis;
    axisX->setRange(0, 10);
    axisX->setTickCount(1);
    axisX->setLabelFormat("%d");
    axisX->setLabelsFont(Font);

    axisY = new QValueAxis;
    axisY->setRange(0, 10);
    axisY->setTickCount(1);
    axisY->setLabelFormat("%.1f");
    axisY->setLabelsFont(Font);


    /*chartView->chart()->setAxisY(axisY, series);*/
    x = 0,y = 0,ymax = 0;

}

void SensorsGraph::setPen(const QPen &pen)
{
    series->setPen(pen);
}

QChartView *SensorsGraph::Chart(void)
{
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setAxisX(axisX, series);
    chartView->chart()->setAxisY(axisY, series);

    return (chartView);
}

void SensorsGraph::UpdateSlot()
{
    series->append(x,y);

    axisX->setRange(0, x+1);
    axisY->setRange(0, 2*ymax);

    /*qDebug()<<"x,y:"<<x<<y;*/
    x++;

    qreal randomic = drand48();
    if(randomic > ymax) ymax = randomic;
    y = randomic;
}


void SensorsGraph::AccelerometerUpdate(qreal yAxis)
{
    /*qDebug()<<"Slot:"<<yAxis;*/

    if(yAxis > 0 && (yAxis > localYmax))
    {
        localYmax = 1.1*yAxis;
    }
    else
    {
        if(yAxis < 0 && (yAxis < localYmin))
        {
            localYmin = 1.1*yAxis;
        }
    }
    axisX->setRange(0, localXmax+1);
    axisY->setRange(localYmin, localYmax);
    series->append(localXmax,yAxis);

    localXmax++;
}

