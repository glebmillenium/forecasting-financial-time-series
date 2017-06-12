#-------------------------------------------------
#
# Project created by QtCreator 2017-05-11T11:30:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = forecast
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/include/qwt /usr/include/curl
LIBS += -L/usr/local -lcrypt -lfann -lqwt-qt5 -lmysqlcppconn -std=c++0x -pthread

SOURCES += main.cpp \
    widgets/viewdata.cpp \
    widgets/settings.cpp \
    widgets/dialoguploaddata.cpp \
    widgets/choosemenu.cpp \
    socket/managersocket.cpp \
    remote_connect_RServ/Rconnection.cc \
    core/statisticalparameters.cpp \
    core/interactionwithnetwork.cpp \
    core/datescaledraw.cpp \
    core/connectordb.cpp \
    core/defs.cpp \
    widgets/viewforecast.cpp \
    widgets/createnetwork.cpp \
    core/formationpredictedmodel.cpp \
    widgets/mainwindow.cpp

HEADERS  += \
    widgets/viewdata.h \
    widgets/settings.h \
    widgets/dialoguploaddata.h \
    widgets/choosemenu.h \
    socket/managersocket.h \
    remote_connect_RServ/sisocks.h \
    remote_connect_RServ/Rsrv.h \
    remote_connect_RServ/Rconnection.h \
    remote_connect_RServ/config.h \
    core/statisticalparameters.h \
    core/interactionwithnetwork.h \
    core/datescaledraw.h \
    core/connectordb.h \
    core/defs.h \
    widgets/viewforecast.h \
    widgets/createnetwork.h \
    core/formationpredictedmodel.h \
    widgets/mainwindow.h

FORMS    += \
    widgets/viewdata.ui \
    widgets/settings.ui \
    widgets/dialoguploaddata.ui \
    widgets/choosemenu.ui \
    widgets/viewforecast.ui \
    widgets/createnetwork.ui \
    widgets/mainwindow.ui

unix: CONFIG += link_pkgconfig \
                qwt

unix: PKGCONFIG += libcurl
