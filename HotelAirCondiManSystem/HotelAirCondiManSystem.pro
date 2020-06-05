#-------------------------------------------------
#
# Project created by QtCreator 2020-05-19T20:28:04
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotelAirCondiManSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    client.cpp \
    receptionist.cpp \
    manager.cpp \
    admin.cpp \
    login.cpp \
    databasestatus.cpp \
    databasereport.cpp \
    admincontroller.cpp \
    report.cpp \
    record.cpp \
    clientcontroller.cpp \
    receptionist_controller.cpp

HEADERS += \
        mainwindow.h \
    client.h \
    receptionist.h \
    manager.h \
    admin.h \
    login.h \
    databasestatus.h \
    databasereport.h \
    admincontroller.h \
    report.h \
    record.h \
    clientcontroller.h \
    receptionist_controller.h

FORMS += \
    mainwindow.ui \
    client.ui \
    receptionist.ui \
    manager.ui \
    admin.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
