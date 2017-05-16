#include "viewforecast.h"
#include "ui_viewforecast.h"


ViewForecast::ViewForecast(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewForecast)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);

    plot = new QwtPlot(this->ui->widget);
    plot->setAxisAutoScale(QwtPlot::xBottom);
    plot->setAxisScaleDraw(QwtPlot::xBottom, new DateScaleDraw(QTime::currentTime()));
    plot->setAxisAutoScale(QwtPlot::yLeft);
    curve = new QwtPlotCurve("x(y)");
    curve->setStyle(QwtPlotCurve::Lines);
    curve->setPen(QPen(Qt::blue));

    curve->attach(plot);
    plot->autoReplot();
    setGraphData();
    this->conn = new ConnectorDB();
    beginSelectCombobox();
}

ViewForecast::~ViewForecast()
{
    delete ui;
}

void ViewForecast::setGraphData()
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

void ViewForecast::beginSelectCombobox()
{
    this->TypeResource = conn->selectTypeResource();
    if(TypeResource.size() != 0)
    {
        for(int i = 0; i < TypeResource.size(); i++)
        {
            ui->TypeMaterial->addItem(std::get<1>(TypeResource[i]));
        }
        ui->Mark->clear();
        int index = ui->TypeMaterial->currentIndex();
        tuple<int, QString> getter = TypeResource[index];
        this->DataResource = conn->selectDataResource(std::get<0>(getter));
        if(DataResource.size() != 0)
        {
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
            m_connection = connect(ui->Mark, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex2(int)));
            connect(ui->TypeMaterial, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex(int)));
            index = ui->Mark->currentIndex();
            this->NeuralNetwork = conn->getNeuralNetwork(std::get<0>(this->DataResource[index]));
            if(this->NeuralNetwork.size() != 0)
            {
                for(int i = 0; i < this->NeuralNetwork.size(); i++)
                {
                    ui->NeuralNetwork->addItem(std::get<1>(this->NeuralNetwork[i]));
                }
                changeIndex3(ui->NeuralNetwork->currentIndex());
                n_connection = connect(ui->NeuralNetwork, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex3(int)));
            }
        }
    }
}

void ViewForecast::changeIndex(int index)
{
    tuple<int, QString> getter = TypeResource[index];
    this->DataResource = conn->selectDataResource(std::get<0>(getter));
    QObject::disconnect(m_connection);
    ui->Mark->clear();
    if(this->DataResource.size() != 0)
    {
        for(int i = 0; i < DataResource.size(); i++)
        {
            ui->Mark->addItem(std::get<3>(DataResource[i]));
        }
        changeIndex2(ui->Mark->currentIndex());
        m_connection = connect(ui->Mark, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex2(int)));
    }
}

void ViewForecast::changeIndex2(int index)
{
    model->clear();
    ui->NeuralNetwork->clear();
    char* fullFileName = new char[256];
    sprintf(fullFileName, "/home/glebmillenium/repositories/%s",
            std::get<2>(this->DataResource[index]).toStdString().c_str());
    int countRows = InteractionWithNetwork::countRowsInTable(fullFileName);
    if(countRows > -1)
    {
        QObject::disconnect(n_connection);
        int countColumns = InteractionWithNetwork::countColumnsInTable(fullFileName);
        model = new QStandardItemModel(countRows, countColumns);
        InteractionWithNetwork::setNameColumns(model, fullFileName);
        InteractionWithNetwork::fillingTable(fullFileName, model, this);
        ui->tableView->setModel(model);
        this->NeuralNetwork = conn->getNeuralNetwork(std::get<0>(this->DataResource[index]));
        if(this->NeuralNetwork.size() != 0)
        {
            for(int i = 0; i < this->NeuralNetwork.size(); i++)
            {
                ui->NeuralNetwork->addItem(std::get<1>(this->NeuralNetwork[i]));
            }
            changeIndex3(ui->NeuralNetwork->currentIndex());
            n_connection = connect(ui->NeuralNetwork, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex3(int)));
        }
        changeIndex3(ui->NeuralNetwork->currentIndex());
        n_connection = connect(ui->NeuralNetwork, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex3(int)));
    }
}

void ViewForecast::changeIndex3(int index)
{

}

void ViewForecast::on_pushButton_clicked()
{
    CreateNetwork* p = new CreateNetwork();
    p->show();
}
