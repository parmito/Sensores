#ifndef SOUND_H
#define SOUND_H

#include <QCheckBox>
#include <QObject>
#include <QWidget>

class Sound : public QWidget
{
    Q_OBJECT
public:
    explicit Sound(QWidget *parent = nullptr);

signals:


private:
    QCheckBox *ptrCheckBox;
};

#endif // SOUND_H
