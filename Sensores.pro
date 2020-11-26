QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += qml quick \
      sensors \
      widgets \
      positioning \
      charts \
      quick \
      multimedia \
      3dcore \
      3dextras \
      3drender \
      3dinput \
      3dlogic \
      3danimation \


SOURCES += \
    DigitalDisplay.cpp \
    Instrumentpanel.cpp \
    PieChart.cpp \
    SensorsApp.cpp \
    SensorsGraph.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DigitalDisplay.h \
    Instrumentpanel.h \
    PieChart.h \
    SensorsApp.h \
    SensorsGraph.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/assets/img/nivus.png \
    android/assets/sounds/alert.wav \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    main.qml

RESOURCES += \
    qml.qrc

ANDROID_ABIS = armeabi-v7a

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

INSERT_APP_NAME = "Sensores"
INSERT_APP_LIB_NAME = "Solido"
INSERT_VERSION_CODE =  "1.0.0"
INSERT_VERSION_NAME = "Gabriele"

contains(ANDROID_TARGET_ARCH,) {
    ANDROID_ABIS = \
        armeabi-v7a
}
