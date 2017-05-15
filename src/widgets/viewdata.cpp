#include "viewdata.h"
#include "ui_viewdata.h"
#include <QDebug>

ViewData::ViewData(QWidget *parent) :
    ui(new Ui::ViewData)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);

    this->conn = new ConnectorDB();
    beginSelectCombobox();

    /*const char* fileName = "file.csv";
    const char* link =
            "https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff";
    InteractionWithNetwork::getQuandlData(link, fileName);
    model = new QStandardItemModel(InteractionWithNetwork::countRowsInTable(fileName),
                                   InteractionWithNetwork::countColumnsInTable(fileName));
    InteractionWithNetwork::setNameColumns(model, fileName);
    InteractionWithNetwork::fillingTable(fileName, model, this);
    */
}

ViewData::~ViewData()
{
    delete ui;
}

void ViewData::setGraphData()
{
    int n = 256;
    double x[n];
    double y[n];
    int t = 0;
    for(double i = -100.0; i < 100.0; i += 1.0)
    {
         x[t] = i;
         y[t] = i*i;
         t++;
    }
    //curve->setData(x, y, n);

}

void ViewData::on_ButtonAddRow_clicked()
{
    int row = model->rowCount();
    model->insertRows(row,1);
    QModelIndex index = model->index(row, 0);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void ViewData::on_ButtonPasteRow_clicked()
{
    int row = ui->tableView->currentIndex().row();
    model->insertRows(row,1);
    QModelIndex index = model->index(row, 1);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void ViewData::on_ButtonDeleteRow_clicked()
{
    model->removeRows(ui->tableView->currentIndex().row(), 1);
}


void ViewData::on_ButtonUploadData_clicked()
{
    int index = ui->Mark->currentIndex();
    upload->showing(std::get<1>(DataResource[index]), std::get<2>(DataResource[index]));
    if (upload->exec() == QDialog::Accepted)
    {
       this->model = upload->model;
       ui->tableView->setModel(this->model);
    }
}

void ViewData::beginSelectCombobox()
{
    this->TypeResource = conn->selectTypeResource();
    for(int i = 0; i < TypeResource.size(); i++)
    {
        ui->TypeMaterial->addItem(std::get<1>(TypeResource[i]));
    }
    ui->Mark->clear();
    int index = ui->TypeMaterial->currentIndex();
    tuple<int, QString> getter = TypeResource[index];
    this->DataResource = conn->selectDataResource(std::get<0>(getter));
    for(int i = 0; i < DataResource.size(); i++)
    {
        ui->Mark->addItem(std::get<3>(DataResource[i]));
    }

    const char* fileName = qPrintable(std::get<2>(this->DataResource[index]));
    char* fullFileName = new char[256];
    sprintf(fullFileName, "/home/glebmillenium/repositories/%s", fileName);
    int countColumns = InteractionWithNetwork::countColumnsInTable(fullFileName);
    int countRows = InteractionWithNetwork::countRowsInTable(fullFileName);
    model = new QStandardItemModel(countRows, countColumns);
    InteractionWithNetwork::setNameColumns(model, fullFileName);

    InteractionWithNetwork::fillingTable(fullFileName, model, this);
    ui->tableView->setModel(model);

    connect(ui->TypeMaterial, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex(int)));
    m_connection = connect(ui->Mark, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex2(int)));
}

void ViewData::changeIndex(int index)
{
    tuple<int, QString> getter = TypeResource[index];
    this->DataResource = conn->selectDataResource(std::get<0>(getter));
    QObject::disconnect(m_connection);
    ui->Mark->clear();
    for(int i = 0; i < DataResource.size(); i++)
    {
        ui->Mark->addItem(std::get<3>(DataResource[i]));
    }
    changeIndex2(ui->Mark->currentIndex());
    m_connection = connect(ui->Mark, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex2(int)));
}

void ViewData::changeIndex2(int index)
{
    model->clear();
    char* fullFileName = new char[256];
    sprintf(fullFileName, "/home/glebmillenium/repositories/%s",
            std::get<2>(this->DataResource[index]).toStdString().c_str());
    int countRows = InteractionWithNetwork::countRowsInTable(fullFileName);
    if(countRows > -1)
    {
        int countColumns = InteractionWithNetwork::countColumnsInTable(fullFileName);
        model = new QStandardItemModel(countRows, countColumns);
        InteractionWithNetwork::setNameColumns(model, fullFileName);
        InteractionWithNetwork::fillingTable(fullFileName, model, this);
        ui->tableView->setModel(model);
    }
}
