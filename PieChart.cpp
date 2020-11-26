#include "PieChart.h"

#include <QDebug>

PieChart::PieChart(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

void PieChart::paint(QPainter *painter)
{
    qDebug() << "paint, cpp";
    QPen pen(m_color, 4);

    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}

QString PieChart:: name() const{
    qDebug() << "name, cpp"<< m_name;
    return m_name;

}
void PieChart::setName(const QString &name)
{
    qDebug() << "setName, cpp";
    m_name = name;
}

QColor PieChart::color() const{
    qDebug() << "color, cpp" << m_color;

    return m_color;
}

void PieChart::setColor(const QColor &color)
{
    qDebug() << "setColor, cpp";
    if (color != m_color) {
      m_color = color;
      update();   // repaint with the new color
      emit colorChanged();
    }
}
  void PieChart::clearChart()
  {
      setColor(QColor(Qt::transparent));
      update();
      emit chartCleared();
  }
