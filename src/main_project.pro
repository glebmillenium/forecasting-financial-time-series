#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T22:40:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main_project
TEMPLATE = app
include ( /usr/local/qwt-6.1.3/features/qwt.prf )

LIBS += -L/usr/local/lib -lfann

SOURCES += main.cpp\
        mainwindow.cpp \
    interactionwithnetwork.cpp \
    statisticalparameters.cpp \
    neuronetwork.cpp \
    dialoguploaddata.cpp

HEADERS  += mainwindow.h \
    curl.h \
    curlbuild.h \
    curlrules.h \
    curlver.h \
    easy.h \
    mprintf.h \
    multi.h \
    stdcheaders.h \
    typecheck-gcc.h \
    interactionwithnetwork.h \
    statisticalparameters.h \
    neuronetwork.h \
    dialoguploaddata.h

FORMS    += mainwindow.ui \
    dialoguploaddata.ui

DISTFILES += \
    main_project.pro.user

unix: CONFIG += link_pkgconfig \
            qwt
unix: PKGCONFIG += libcurl
