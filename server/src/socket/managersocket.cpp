/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ManagerSocket.cpp
 * Author: glebmillenium
 * 
 * Created on 21 января 2017 г., 11:03
 */

#include "managersocket.h"

ManagerSocket::ManagerSocket() {
    this->listener = socket(AF_INET, SOCK_STREAM, 0);
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(5800);
    this->addr.sin_addr.s_addr = INADDR_ANY;
    connectorDB = new ConnectorDB();
}

ManagerSocket::ManagerSocket(int port) {
    this->listener = socket(AF_INET, SOCK_STREAM, 0);
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = INADDR_ANY;
    connectorDB = new ConnectorDB();
}

void ManagerSocket::run() {
    /* Простаивание потоков в ожидании коннекта ~15sec*/
    timeval timeout;
    timeout.tv_sec = 15;
    timeout.tv_usec = 0;

    if (this->listener < 0) {
        perror("socket");
        exit(1);
    }
    fcntl(this->listener, F_SETFL, O_NONBLOCK);

    if (bind(this->listener, (struct sockaddr *) & this->addr, sizeof (this->addr)) < 0) {
        perror("bind");
        exit(2);
    }

    listen(listener, 10);

    set<int> clients;
    clients.clear();
    while (1) {
        // Заполняем множество сокетов
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener, &readset);

        for (set<int>::iterator it = clients.begin(); it != clients.end(); it++)
            FD_SET(*it, &readset);

        // Задаём таймаут
        // Ждём события в одном из сокетов
        int mx = max(listener, *max_element(clients.begin(), clients.end()));
        if (select(mx + 1, &readset, NULL, NULL, &timeout) <= 0) {
            continue;
        }

        // Определяем тип события и выполняем соответствующие действия
        if (FD_ISSET(listener, &readset)) {
            // Поступил новый запрос на соединение, используем accept
            int sock = accept(listener, NULL, NULL);
            if (sock < 0) {
                perror("accept");
                exit(3);
            }

            fcntl(sock, F_SETFL, O_NONBLOCK);
            clients.insert(sock);
        }

        for (set<int>::iterator it = clients.begin(); it != clients.end(); it++) {
            if (FD_ISSET(*it, &readset)) {
                char* data_client = new char[1024];
                int bytes_read = read(*it, data_client, 1024);
                if (bytes_read <= 0) {
                    close(*it);
                    clients.erase(*it);
                    continue;
                }
                if(!strcmp("--get_types", data_client))
                {
                    char* result = serializeGetTypes(connectorDB->selectTypeResource(), 50);
                    send(*it, result, strlen(result), 0);
                    continue;
                }
                if(containsInBeginFirstStr("--get_marks ", data_client))
                {
                    char* index = new char[120];
                    strcpy(index, &data_client[12]);
                    char* result = serializeGetTypes(
                                connectorDB->selectDataResourceOnlyIdAndData(atoi(index)), 120);
                    send(*it, result, strlen(result), 0);
                    continue;
                }
                if(containsInBeginFirstStr("--get_data ", data_client))
                {
                    char* result = new char[1048576];
                    strcpy(result, "");
                    char* index = new char[50];
                    strcpy(index, &data_client[11]);
                    char* path = connectorDB->getPathFileData(atoi(index));

                    string line;
                    ifstream myfile(path);
                    if (myfile.is_open())
                    {
                        while (getline(myfile,line) )
                        {
                            char* read = (char*) line.c_str();
                            strcat(result, read);
                            strcat(result, "||");
                        }
                        result[strlen(result) - 2] = '\0';
                        myfile.close();
                    }
                    send(*it, result, strlen(result), 0);
                }
                if(containsInBeginFirstStr("--get_forecast ", data_client))
                {
                    char* result = new char[1048576];
                    strcpy(result, " ");
                    char* index = new char[50];
                    strcpy(index, &data_client[15]);
                    char* path = connectorDB->getPathFileForecast(atoi(index));
                    if(strlen(path))
                    {
                        string line;
                        ifstream myfile(path);
                        if (myfile.is_open())
                        {
                            while (getline(myfile,line) )
                            {
                                char* read = (char*) line.c_str();
                                strcat(result, read);
                                strcat(result, "||");
                            }
                            result[strlen(result) - 2] = '\0';
                            myfile.close();
                        }
                    }
                    send(*it, result, strlen(result), 0);
                }
            }
        }
    }
}


char* ManagerSocket::serializeGetTypes(vector<tuple<int, QString>> resultQuery, int maxSize)
{
    char* result = new char[resultQuery.size() * maxSize];
    sprintf(result, "");
    for(int i = 0; i < resultQuery.size(); i++)
    {
        char* newLine = new char[maxSize];
        sprintf(newLine, "%d,%s", std::get<0>(resultQuery.at(i)),
                std::get<1>(resultQuery.at(i)).toStdString().c_str());
        strcat(result, newLine);
        if(i != (resultQuery.size() - 1))
        {
            strcat(result, "||");
        }
    }
    strcat(result, "\0");
    return result;
}

bool ManagerSocket::containsInBeginFirstStr(char* str1, char* str2)
{
    if(strlen(str1) > strlen(str2))
    {
        return false;
    }
    else
    {
        bool result = true;
        for(int i = 0; i < strlen(str1); i++)
        {
            if(str1[i] != str2[i])
            {
                result = false;
            }
        }
        return result;
    }
}
