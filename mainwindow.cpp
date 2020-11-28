#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

#include <Instrumentpanel.h>
#include "PieChart.h"
#include <SensorsApp.h>
#include <SensorsGraph.h>
#include <Sound.h>
#include <QQuickView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtQuick/qquickview.h>

#include <QLineSeries>
#include <QLabel>
#include <QCamera>

#include <QPushButton>
#include <QStackedLayout>
#include <QComboBox>
#include <QStackedWidget>
#include <QToolBar>
#include <QListWidget>
#include <QIcon>
#include <QDockWidget>
#include <QCheckBox>

#define PRIMEIRA_VERSAO 0
#define SEGUNDA_VERSAO 0

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{        
    qmlRegisterType<PieChart>("Charts", 1, 0, "PieChart");
    ui->setupUi(this);

    /*QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setParent(this);
    container->setMinimumSize(640,150);
    container->setMaximumSize(640,150);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl("qrc:///main.qml"));

    QObject *object = view->rootObject();*/
    SensorsApp *sensor = new SensorsApp();

   /* QLineSeries *series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);*/

   /* QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
    chart->setMinimumSize(800,400);
    chart->setMaximumSize(800,400);*/

    /*QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);*/
    /*chartView->setParent(this);*/


#if PRIMEIRA_VERSAO

    SensorsGraph *pSensorGraphRnd = new SensorsGraph(this,"Randomico",QChart::ChartThemeLight);
    SensorsGraph *pSensorGraphAccelX = new SensorsGraph(this,"Accelerometer: x",QChart::ChartThemeLight);
    SensorsGraph *pSensorGraphAccelY = new SensorsGraph(this,"Accelerometer: y",QChart::ChartThemeLight);
    SensorsGraph *pSensorGraphAccelZ = new SensorsGraph(this,"Accelerometer: z",QChart::ChartThemeLight);

    QWidget *window = new QWidget();
    QGridLayout *pLayout = new QGridLayout();   
    QLabel *pLabel = new QLabel();
    QPushButton *pButton = new QPushButton();


    pLabel->setText("Speed:");
    pButton->setText("Gps");
    pButton->setMaximumSize(100,100);


    /*pLayout->setAlignment(window,Qt::AlignLeft);*/
    /*pLayout->setSpacing(10);*/
    /*pLayout->addWidget(container);*/
    /*pLayout->addWidget(pSensorGraphRnd->Chart());*/


    pLayout->addWidget(pLabel);
    pLayout->addWidget(pButton);
    pLayout->addWidget(pSensorGraphAccelX->Chart());
    pLayout->addWidget(pSensorGraphAccelY->Chart());
    pLayout->addWidget(pSensorGraphAccelZ->Chart());

    window->setLayout(pLayout);
    setFixedSize(this->size().width(),this->size().height());
    setCentralWidget(window);
#endif

    QWidget *firstTab = new QWidget();
    QWidget *secondTab = new QWidget();
    QWidget *thirdTab = new QWidget();
    QWidget *fourthTab = new QWidget();

    SensorsGraph *pSensorGraphAccelX = new SensorsGraph(this,"Accelerometer: x",QChart::ChartThemeLight);
    SensorsGraph *pSensorGraphAccelY = new SensorsGraph(this,"Accelerometer: y",QChart::ChartThemeLight);
    SensorsGraph *pSensorGraphAccelZ = new SensorsGraph(this,"Accelerometer: z",QChart::ChartThemeLight);
    SensorsGraph *pSensorGraphRnd = new SensorsGraph(this,"Randomico",QChart::ChartThemeLight);

    QPen penBlue(Qt::blue, 4, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen penGreen(Qt::green, 4, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen penRed(Qt::red, 4, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    pSensorGraphAccelX->setPen(penBlue);
    pSensorGraphAccelY->setPen(penGreen);
    pSensorGraphAccelZ->setPen(penRed);

    QGridLayout *pFirstLayout = new QGridLayout();
    pFirstLayout->addWidget(pSensorGraphAccelX->Chart());
    pFirstLayout->addWidget(pSensorGraphAccelY->Chart());
    pFirstLayout->addWidget(pSensorGraphAccelZ->Chart());
    firstTab->setLayout(pFirstLayout);


    /*****************************************************
     *
     *
     *                  2nd TAB
     *
     *
     ****************************************************/
    QGridLayout *pSecondLayout = new QGridLayout();
    /*pSecondLayout->addWidget(pSensorGraphAccelY->Chart());*/

    InstrumentPanel *cluster = new InstrumentPanel();
    cluster->repaint();


   /* pSecondLayout->addWidget(checkBoxSound);*/
    pSecondLayout->addWidget(cluster);
    secondTab->setLayout(pSecondLayout);


    /*****************************************************
     *
     *
     *                  3rd TAB
     *
     *
     ****************************************************/
    QGridLayout *pThirdLayout = new QGridLayout();
   /* pThirdLayout->addWidget(pSensorGraphAccelZ->Chart());*/

#if 0
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QRgb(0x1d1d4f));
    view->setRootEntity(rootEntity);

    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);
    container->setFocusPolicy(Qt::NoFocus);

    setCentralWidget(container);

    Qt3DRender::QCamera *cameraEntity = view->camera();

    // X+ -> right
    // Y+ -> away
    // Z+ -> up
    cameraEntity->lens()->setPerspectiveProjection(
        45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, -5, 5.0f));
    cameraEntity->setUpVector(QVector3D(0, 0, 1));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController *camController = new
        Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);

    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);

    lightEntity->addComponent(light);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(
        lightEntity);
    lightTransform->setTranslation(QVector3D(-20, 20, 20));
    lightEntity->addComponent(lightTransform);

    Qt3DCore::QEntity *sceneLoaderEntity = nullptr;
    Qt3DRender::QSceneLoader *loader = nullptr;

    /*sceneLoaderEntity = new Qt3DCore::QEntity(rootEntity);
      loader = new Qt3DRender::QSceneLoader(sceneLoaderEntity);
      loader->setObjectName("object1.dae");
      sceneLoaderEntity->addComponent(loader);
      loader->setSource(
          QUrl(QString("file:../Qt3DTests/Models/object1.dae")));*/
#endif

    /*pThirdLayout->addWidget(solid);
    thirdTab->setLayout(pThirdLayout);*/

    /*****************************************************
     *
     *
     *                  4th TAB
     *
     *
     ****************************************************/
    QGridLayout *pFourthLayout = new QGridLayout();
   /* pFourthLayout->addWidget(pSensorGraphRnd->Chart());*/
    fourthTab->setLayout(pFourthLayout);

    QDockWidget *dock = new QDockWidget(tr("Verwaltung"), this);
    /*dock->setFeatures(QDockWidget::DockWidgetMovable);*/


    QFont font("Verdana", 5, QFont::Helvetica);
    dock->setFont(font);
    //set the color of the dockwidget
    dock->setAutoFillBackground(false);
    QPalette qpal;
    qpal.setColor(QPalette::Active,QPalette::Window,QColor(210,239,109));
    dock->setBackgroundRole(QPalette::Window);
    dock->setPalette(qpal);
    //end set color
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QListWidget *carList = new QListWidget(dock);
    QFont listFont("Helvetica",-1,-1,true);
    carList->setFont(listFont);

    QStringList carName("Car1");
    carName.append("Car2");
    carName.append("Car3");
    carName.append("Car4");
    carName.append("Car5");

    QIcon icon= QIcon("assets:img/nivus.png");

    foreach(QString str, carName) {
        QListWidgetItem *item = new QListWidgetItem(icon, str, carList);
        carList->addItem(item);
    }

    pFourthLayout->addWidget(carList);
    fourthTab->setLayout(pFourthLayout);


    /*****************************************************
     *
     *
     *                  TOOLBAR
     *
     *
     ****************************************************/
    QToolBar *toolBar = new QToolBar();
    QLabel *label = new QLabel("Sensores",toolBar);
    toolBar->addSeparator();
    toolBar->addWidget(label);


    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->addTab(firstTab,"Acelerômetro");
    tabWidget->addTab(secondTab,"Velocidade");
    tabWidget->addTab(thirdTab,"Solido");
    tabWidget->addTab(fourthTab,"QWidgetList");


    this->layout()->setMenuBar(toolBar);
    this->setCentralWidget(tabWidget);
    tabWidget->setCurrentIndex(0);
    this->setWindowTitle("Mobile Sensors");

    connect(sensor, SIGNAL(cppSendSpeed(QString)),
                     cluster, SLOT(SlotReceiveSpeed(QString)));

    connect(sensor, SIGNAL(cppSendDistance(double)),
                     cluster, SLOT(SlotReceiveDistance(double)));




#if SEGUNDA_VERSAO
    secondPageWidget->setFixedSize(300,150);
    secondPageWidget->setWindowTitle("Gabi");
    QPushButton *m_button2 = new QPushButton("Entry",secondPageWidget);


    secondPageWidget->setFixedSize(300,150);
    secondPageWidget->setWindowTitle("Gabi");
    QPushButton *m_button2 = new QPushButton("Entry",secondPageWidget);

    thirdPageWidget->setFixedSize(300,150);
    thirdPageWidget->setWindowTitle("Nicole");
    QPushButton *m_button3 = new QPushButton("Exit",thirdPageWidget);


    QStackedWidget *stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(firstPageWidget);
    stackedWidget->addWidget(secondPageWidget);
    stackedWidget->addWidget(thirdPageWidget);


    this->setCentralWidget(stackedWidget);
    stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Test");
    resize(200,200);

#endif

      QTimer *myTimer = new QTimer(this);
      connect(myTimer, SIGNAL (timeout()), pSensorGraphRnd, SLOT (UpdateSlot()));
      connect(myTimer, SIGNAL (timeout()), sensor, SLOT (positionUpdate()));
      myTimer->start(1000);


    /*QObject::connect(sensor, SIGNAL(cppSendAccelX(QString)),
                     object->findChild<QObject *>("txtInputAccelX"), SIGNAL(qmlReceiveAccelX(QString)));*/

    QObject::connect(sensor, SIGNAL(cppSignalNumberAccelX(qreal)),
                     pSensorGraphAccelX, SLOT(AccelerometerUpdate(qreal)));

    /*QObject::connect(sensor, SIGNAL(cppSendAccelXInt(qreal,qreal)),
                     object->findChild<QObject *>("LineSeries"), SIGNAL(qmlReceiveLineSeries(qreal,qreal)));*/

    /*QObject::connect(sensor, SIGNAL(cppSendAccelY(QString)),
                     object->findChild<QObject *>("txtInputAccelY"), SIGNAL(qmlReceiveAccelY(QString)));*/

    QObject::connect(sensor, SIGNAL(cppSignalNumberAccelY(qreal)),
                     pSensorGraphAccelY, SLOT(AccelerometerUpdate(qreal)));

   /* QObject::connect(sensor, SIGNAL(cppSendAccelZ(QString)),
                     object->findChild<QObject *>("txtInputAccelZ"), SIGNAL(qmlReceiveAccelZ(QString)));*/

    QObject::connect(sensor, SIGNAL(cppSignalNumberAccelZ(qreal)),
                     pSensorGraphAccelZ, SLOT(AccelerometerUpdate(qreal)));

    /*QObject::connect(sensor, SIGNAL(cppSendAltitude(QString)),
                     object->findChild<QObject *>("txtInputAltitude"), SIGNAL(qmlReceiveAltitude(QString)));*/

    /*QObject::connect(sensor, SIGNAL(cppSendTimestamp(QString)),
                     object->findChild<QObject *>("txtInputTimestamp"), SIGNAL(qmlReceiveTimestamp(QString)));*/

    /*QObject::connect(sensor, SIGNAL(cppSendLatitude(QString)),
                     object->findChild<QObject *>("txtInputLatitude"), SIGNAL(qmlReceiveLatitude(QString)));*/

    /*QObject::connect(sensor, SIGNAL(cppSendLongitude(QString)),
                     object->findChild<QObject *>("txtInputLongitude"), SIGNAL(qmlReceiveLongitude(QString)));*/

    /*QObject::connect(sensor, SIGNAL(cppSendAltitude(QString)),
                     object->findChild<QObject *>("txtInputAltitude"), SIGNAL(qmlReceiveAltitude(QString)));*/

    /*QObject::connect(sensor, SIGNAL(cppSendSpeed(QString)),
                     object->findChild<QObject *>("txtInputSpeed"), SIGNAL(qmlReceiveSpeed(QString)));*/

   /* QObject *item = object->findChild<QObject *>("textInputAccelerometerX");
    if (item != nullptr)
    {
        QVariant strText = item->property("text");
        qDebug() << "string:"<< strText.toString();
        item->setProperty("text","0");
        strText = item->property("text");
        qDebug() << "string:"<< strText.toString();
    }*/
#if 0
    QObject *item2 = object->findChild<QObject *>("ChartA");
    if (item2 != nullptr)
    {
        QVariant color = item2->property("color");
        qDebug() << "color:"<< color.toString();
        item2->setProperty("color","orange");
        color = item2->property("color");
        qDebug() << "color:"<< color.toString();
    }

    QObject *item3 = object->findChild<QObject *>("ChartB");
    if(item3 != nullptr)
    {
        QVariant color2 = item3->property("color");
        qDebug() << "color:"<< color2.toString();
        item3->setProperty("color","green");
        color2 = item3->property("color");
        qDebug() << "color:"<< color2.toString();
    }
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

