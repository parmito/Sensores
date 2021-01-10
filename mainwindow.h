#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Instrumentpanel.h>
#include <QMainWindow>
#include <SensorsApp.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void cppSendEndKmlFile(void);

private:
    Ui::MainWindow *ui;
    SensorsApp *sensor;
    InstrumentPanel *cluster;
};
#endif // MAINWINDOW_H
