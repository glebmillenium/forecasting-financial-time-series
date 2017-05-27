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
#include "core/defs.h"

using namespace std;

class ConnectorDB {
public:
    ConnectorDB();
    ConnectorDB(const ConnectorDB& orig);
    virtual ~ConnectorDB();
    
    static bool tryConnection(char* ip, char* login, char* password, char* schema);
    /**
     * Get id_type_resources, name_resource from type_resources
     *
     * @brief selectTypeResource
     * @return
     */
    vector<tuple<int, QString>> selectTypeResource();
    /**
     * Get id_data_resources, id_type_resources, url_remote, path_file_contains_data, name_data,
     *      number_col_forecast from data_resources
     * @brief selectDataResource
     * @param id_type_resources
     * @return
     */
    vector<tuple<int, QString, QString, QString, int>> selectDataResource(int id_type_resources);
    /**
     * Get id_neural_network, name_neural_network, first_param, second_param, path_file_contains_neural_network,
     *      path_file_contains_forecast, date_with_forecast, scale, differential_series
     * @brief getNeuralNetwork
     * @param id_data_resources
     * @return
     */
    vector<tuple<int, QString, int, int, QString, QString, QString, int, int>> getNeuralNetwork(int id_data_resources);
private:
    sql::Driver *driver;
    sql::Connection *con;
    
    char* SQLStringToChar(sql::SQLString str);
    char* getCurrentTime();
};

#endif /* CONNECTORDB_H */

