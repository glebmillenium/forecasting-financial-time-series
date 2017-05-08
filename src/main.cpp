#include "mainwindow.h"
#include <QApplication>

/// main.cpp
#include <iostream>
using std::cout;

#define MAIN                      // коcтыль из sisocks.h
#define SOCK_ERRORS  // verbose socket errors

#include "sisocks.h"
#include "Rconnection.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
