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
    connect(ui->TypeMaterial, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex(int)));
}

void ViewForecast::changeIndex(int index)
{
    ui->Mark->clear();
    tuple<int, QString> getter = TypeResource[index];
    this->DataResource = conn->selectDataResource(std::get<0>(getter));
    for(int i = 0; i < DataResource.size(); i++)
    {
        ui->Mark->addItem(std::get<3>(DataResource[i]));
    }
}
