/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectorDB.cpp
 * Author: glebmillenium
 * 
 * Created on 18 февраля 2017 г., 1:58
 */

#include "connectordb.h"

using namespace std;

ConnectorDB::ConnectorDB() {
    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "neural_network", "neural");
        con->setSchema("forecast_time_series");
    } catch (sql::SQLException &e) {
        std::cout << "ERR: " << e.what();
        cout << "constructor" << endl;
    }
}

ConnectorDB::ConnectorDB(const ConnectorDB& orig) {
}

ConnectorDB::~ConnectorDB() {
}

char* ConnectorDB::getCurrentTime() {
    char* buffer = new char[80];
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    char* format = (char*) "%Y%m%d%H%M%S";
    strftime(buffer, 80, format, timeinfo);
    return buffer;
}

char* ConnectorDB::SQLStringToChar(sql::SQLString str) {
    char* result = new char[1024];
    int i;
    for (i = 0; i < 1024; i++) {
        if (str[i] == '\0') {
            result[i] = '\0';
            break;
        }
        result[i] = str[i];
    }
    return result;
}

vector<tuple<int, QString, QString, QString, int>> ConnectorDB::selectDataResource(int id_type_resources)
{
    vector<tuple<int, QString, QString, QString, int>> result;
    try {
        char* query = new char[256];
        sprintf(query, "SELECT data_resources.id_data_resources, "
                       "data_resources.url_remote,"
                       "data_resources.path_file_contains_data, "
                       "data_resources.name_data,"
                       "data_resources.number_col_forecast FROM `data_resources`"
                       "WHERE id_type_resources = %d;", id_type_resources);
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(query);
        while (res->next()) {
            result.push_back(std::make_tuple(
                                 (int) res->getInt("id_data_resources"),
                                 QString::fromUtf8(SQLStringToChar(res->getString("url_remote"))),
                                 QString::fromUtf8(SQLStringToChar(res->getString("path_file_contains_data"))),
                                 QString::fromUtf8(SQLStringToChar(res->getString("name_data"))),
                                 (int) res->getInt("number_col_forecast")));
        }
        if(result.size() == 0)
        {
            result.push_back(std::make_tuple(-1, "", "", "", -1));
        }
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__ << endl;
        cout << "# ERR: function in selectDataResource" << endl;
        cout << "# ERR: " << e.what() << endl;
        cout << " (MySQL error code: " << e.getErrorCode() << endl;
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        result.clear();
        result.push_back(std::make_tuple(-1, "", "", "", -1));
    }
    return result;
}

vector<tuple<int, QString>> ConnectorDB::selectTypeResource()
{
    vector<tuple<int, QString>> result;
    try {
        char* query = new char[128];
        sprintf(query, "SELECT type_resources.id_type_resources, type_resources.name_resource "
                       "FROM type_resources");
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(query);
        while (res->next()) {
            result.push_back(std::make_tuple((int) res->getInt("id_type_resources"),
                             QString::fromUtf8(SQLStringToChar(res->getString("name_resource")))));
        }
        if(result.size() == 0)
        {
            result.push_back(std::make_tuple(-1, ""));
        }
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: function in getAllCommands";
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        result.clear();
        result.push_back(std::make_tuple(-1, ""));
    }
    return result;
}

bool ConnectorDB::tryConnection(char* ip, char* login, char* password, char* schema)
{
    try {
        sql::Driver *driver;
        sql::Connection *con;
        driver = get_driver_instance();
        con = driver->connect(ip, login, password);
        con->setSchema(schema);
        return true;
    } catch (sql::SQLException &e) {
        std::cout << "ERR: " << e.what();
        cout << "constructor" << endl;
        return false;
    }
}
