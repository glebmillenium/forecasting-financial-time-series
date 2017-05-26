#include "widgets/mainwindow.h"
#include <QApplication>
#include "core/defs.h"
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    MainWindow w;
    w.show();
    return a.exec();
}
