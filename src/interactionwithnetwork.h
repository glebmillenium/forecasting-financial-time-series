#ifndef INTERACTIONWITHNETWORK_H
#define INTERACTIONWITHNETWORK_H

#include <curl.h>
#include <QtCore>
#include <QStandardItemModel>
#include <QString>
#include <iostream>
#include <string>
#include <fstream>
#include <QModelIndex>
#include <QMainWindow>
#include <QString>

using std::string;
using std::iostream;
using std::ifstream;

class InteractionWithNetwork
{
public:
    InteractionWithNetwork();
    static void setNameColumns(QStandardItemModel *model, const char* fileName);
    static void getQuandlData(const char* urlDownload, const char* outFileName);
    static int countRowsInTable(const char* fileName);
    static int countColumnsInTable(const char* fileName);
    static void fillingTable(const char* fileName, QStandardItemModel *model, QWidget *window);
};

#endif // INTERACTIONWITHNETWORK_H
