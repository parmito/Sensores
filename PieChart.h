#ifndef PIECHART_H
#define PIECHART_H


#include <QtQuick/QQuickPaintedItem>
#include <QPen>
#include <QPainter>
#include <QColor>

class PieChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    PieChart(QQuickItem *parent = 0);
    Q_INVOKABLE void clearChart();

    QString name() const;
    void setName(const QString &name);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter);

signals:
    void chartCleared();
    void colorChanged();

private:
    QString m_name;
    QColor m_color;
};


#endif // PIECHART_H
