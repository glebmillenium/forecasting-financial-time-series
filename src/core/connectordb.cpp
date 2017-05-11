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

char* ConnectorDB::getCommandsFromAvailaibleTable() {

    char* result = new char[16384];
    strcpy(result, "");

    try {
        char* query = new char[128];
        sql::SQLString command;
        sprintf(query, "SELECT * FROM available_commands JOIN commands "
                "WHERE available_commands.id_command = commands.id_command");
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(query);
        while (res->next()) {
            command = res->getString("message");
            strcat(result, SQLStringToChar(command));
            strcat(result, (char*) "\n");
        }
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: function in getCommandsFromAvailaibleTable";
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        result = (char*) "";
    }
    return result;
}

void ConnectorDB::setCommandsInAvailaibleTable(char* id_application) {
    char* query = new char[128];
    char* insert = new char[128];
    sprintf(query,
            "SELECT * FROM commands "
            "WHERE (id_application = 1) OR (id_application = %s)", id_application);
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery(query);

    sql::SQLString command;
    sql::PreparedStatement *pstmt;
    pstmt = con->prepareStatement("TRUNCATE TABLE available_commands");
    pstmt->executeUpdate();
    int i = 0;
    while (res->next()) {
        command = res->getString("id_command");
        sprintf(insert,
                "INSERT INTO available_commands(id, id_command)"
                " VALUES(%d, %s)", i, SQLStringToChar(command));
        pstmt = con->prepareStatement(insert);
        pstmt->executeUpdate();
        i++;
    }
}

void ConnectorDB::setDefaultCommandsInAvailaibleTable() {
    char* query = new char[128];
    char* insert = new char[128];
    sprintf(query,
            "SELECT * FROM commands "
            "WHERE (id_application = 1)");
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery(query);

    sql::SQLString command;
    sql::PreparedStatement *pstmt;
    pstmt = con->prepareStatement("TRUNCATE TABLE available_commands");
    pstmt->executeUpdate();
    int i = 0;
    while (res->next()) {
        command = res->getString("id_command");
        sprintf(insert,
                "INSERT INTO available_commands(id, id_command)"
                " VALUES(%d, %s)", i, SQLStringToChar(command));
        pstmt = con->prepareStatement(insert);
        pstmt->executeUpdate();
        i++;
    }
}

vector<string> ConnectorDB::getHistoryAction() {
    vector<string> result;
    try {
        sql::Statement *stmt;
        sql::ResultSet *res;
        char* query = new char[256];
        sprintf(query, "SELECT * "
                "FROM history JOIN commands "
                "WHERE history.id_command = commands.id_command");
        stmt = con->createStatement();
        res = stmt->executeQuery(query);
        if (!res->next()) {
            return result;
        } else {
            sql::SQLString command;
            do {
                command = res->getString("message");
                string str(SQLStringToChar(command));
                result.push_back(str);
            } while (res->next());
        }
        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: " << e.what();
        cout << "function: getHistoryAction " << endl;
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return result;
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

char* ConnectorDB::getAllCommands()
{
    char* result = new char[16384];
    strcpy(result, "");

    try {
        char* query = new char[128];
        sql::SQLString command;
        sprintf(query, "SELECT * FROM commands ");
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(query);
        while (res->next()) {
            command = res->getString("message");
            strcat(result, SQLStringToChar(command));
            strcat(result, (char*) "\n");
        }
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: function in getAllCommands";
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        result = (char*) "";
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

char* ConnectorDB::tryConnection(char* ip, char* login, char* password, char* schema)
{
    try {
        sql::Driver *driver;
        sql::Connection *con;
        driver = get_driver_instance();
        con = driver->connect(ip, login, password);
        con->setSchema(schema);
        return "Успешное соединение";
    } catch (sql::SQLException &e) {
        std::cout << "ERR: " << e.what();
        cout << "constructor" << endl;
        return "Не удалось подключиться";
    }
}
