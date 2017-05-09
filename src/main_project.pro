#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T22:40:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main_project
TEMPLATE = app
#include ( /usr/local/qwt-6.1.3/features/qwt.prf )
INCLUDEPATH += /usr/include/qwt /usr/include/curl
LIBS += -L/usr/local -lcrypt -lfann -lqwt-qt5 -lmysqlcppconn

SOURCES += Rconnection.cc\
    main.cpp\
    mainwindow.cpp \
    interactionwithnetwork.cpp \
    statisticalparameters.cpp \
    neuronetwork.cpp \
    dialoguploaddata.cpp \
    ManagerSocket.cpp \
    datescaledraw.cpp \
    ConnectorDB.cpp \
    viewdata.cpp \
    choosemenu.cpp

HEADERS  += mainwindow.h \
    interactionwithnetwork.h \
    statisticalparameters.h \
    neuronetwork.h \
    dialoguploaddata.h \
    Rsrv.h \
    ManagerSocket.h \
    datescaledraw.h \
    ConnectorDB.h \
    config.h \
    sisocks.h \
    Rconnection.h \
    config.h \
    viewdata.h \
    choosemenu.h

FORMS    += mainwindow.ui \
            dialoguploaddata.ui \
    viewdata.ui \
    choosemenu.ui

DISTFILES += \
    main_project.pro.user \
    main_project.pro.user.7adb7c2

unix: CONFIG += link_pkgconfig \
                qwt
unix: PKGCONFIG += libcurl
