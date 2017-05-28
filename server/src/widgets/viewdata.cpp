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
}

ViewData::~ViewData()
{
    delete ui;
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
    sprintf(fullFileName, "%s%s", dataStore, fileName);
    int countColumns = InteractionWithNetwork::countColumnsInTable(fullFileName);
    int countRows = InteractionWithNetwork::countRowsInTable(fullFileName);
    model = new QStandardItemModel(countRows, countColumns);
    InteractionWithNetwork::setNameColumns(model, fullFileName);

    InteractionWithNetwork::fillingTable(fullFileName, model, this);
    ui->tableView->setModel(model);
    m_connection = connect(ui->Mark, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex2(int)));
    connect(ui->TypeMaterial, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex(int)));
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
    sprintf(fullFileName, "%s%s", dataStore,
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
