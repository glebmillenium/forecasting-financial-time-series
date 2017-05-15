#include "interactionwithnetwork.h"

void InteractionWithNetwork::getQuandlData(const char* urlDownload, const char* outFileName){
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outFileName,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, urlDownload);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}
int InteractionWithNetwork::countRowsInTable(const char* fileName){
    string s;
    ifstream file;
    file.open(fileName);
    int i = 0;
    while(getline(file, s)){
        i++;
    }
    file.close();
    return i - 1;
}

int InteractionWithNetwork::countColumnsInTable(const char* fileName){
    string s;
    ifstream file;
    file.open(fileName);
    getline(file, s);
    std::string token;
    std::string delim = ",";
    int j = 0;
    size_t prev = 0, pos = 0;
    do
    {
        pos = s.find(delim, prev);
        if (pos == string::npos) pos = s.length();
        string token = s.substr(prev, pos-prev);
        if (!token.empty()) j++;
        prev = pos + delim.length();
    }
    while (pos < s.length() && prev < s.length());
    file.close();
    return j;
}

QStringList InteractionWithNetwork::setNameColumns(QStandardItemModel *model, const char* fileName){
    string s;
    ifstream file;
    file.open(fileName);
    getline(file, s);
    std::string token;
    std::string delim = ",";
    size_t prev = 0, pos = 0;
    QStringList list;
    do
    {
        pos = s.find(delim, prev);
        if (pos == string::npos) pos = s.length();
        string token = s.substr(prev, pos-prev);
        if (!token.empty()) list << QString::fromStdString(token);
        prev = pos + delim.length();
    }
    while (pos < s.length() && prev < s.length());
    model->setHorizontalHeaderLabels(list);
    file.close();
    return list;
}

void InteractionWithNetwork::fillingTable(const char* fileName,
                              QStandardItemModel *model,
                                          QWidget *window)
{
    string s;
    ifstream file;
    file.open(fileName);
    int j, i;
    size_t prev, pos;
    std::string delim = ",";   

    getline(file, s);
    i = 0;
    while(getline(file, s)){
        j = 0;
        prev = 0, pos = 0;
        do
        {
            QModelIndex index = model->index(i, j);
            pos = s.find(delim, prev);
            if (pos == string::npos) pos = s.length();
            string token = s.substr(prev, pos-prev);
            if (token.empty()) token = " ";
            model->setData(index, QString::fromStdString(token));
            prev = pos + delim.length();
            j++;
        }
        while (pos < s.length() && prev < s.length());
        i++;
    }
    file.close();
}
