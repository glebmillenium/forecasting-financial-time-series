/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectorDB.h
 * Author: glebmillenium
 *
 * Created on 18 февраля 2017 г., 1:58
 */

#ifndef CONNECTORDB_H
#define CONNECTORDB_H
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <QString>
#include <QStringList>

#include "mysql_connection.h"

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include <cppconn/prepared_statement.h>

using namespace std;

class ConnectorDB {
public:
    ConnectorDB();
    ConnectorDB(const ConnectorDB& orig);
    virtual ~ConnectorDB();
    
    static bool tryConnection(char* ip, char* login, char* password, char* schema);
    vector<tuple<int, QString>> selectTypeResource();
    vector<tuple<int, QString, QString, QString, int>> selectDataResource(int id_type_resources);
private:
    sql::Driver *driver;
    sql::Connection *con;
    
    char* SQLStringToChar(sql::SQLString str);
    char* getCurrentTime();
};

#endif /* CONNECTORDB_H */

