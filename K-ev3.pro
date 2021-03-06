#-------------------------------------------------
#
# Project created by QtCreator 2019-03-07T13:14:45
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = K-ev3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# This is defined to ease switching between win and linux versions of program.
# Windows version was used for quicker compilation and easier debug for parts that weren't platform specific.
DEFINES += RPI=1

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 debug force_debug_info

QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

INCLUDEPATH += wiringPi/wiringPi

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    meterbar.cpp \
    menu.cpp \
    button.cpp \
    serial.cpp \
    pushbuttons.cpp \
    entry.cpp \
    entrytemp.cpp \
    entryerrors.cpp \
    #entrystats.cpp \
    entrystatus.cpp \
    entryseriallog.cpp \
    entrymotor.cpp \
    clock.cpp \
    notice.cpp

HEADERS += \
        mainwindow.h \
    meterbar.h \
    menu.h \
    button.h \
    serial.h \
    pushbuttons.h \
    entry.h \
    entrytemp.h \
    entryerrors.h \
    #entrystats.h \
    entrystatus.h \
    entryseriallog.h \
    entrymotor.h \
    clock.h \
    notice.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


unix {
    LIBS += -L/usr/local/include -lwiringPi
}

RESOURCES += \
    pics.qrc
