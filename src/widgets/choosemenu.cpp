#include "choosemenu.h"
#include "ui_choosemenu.h"
#include "../core/connectordb.h"
#include <QString>
#include "viewforecast.h"

#define MAIN         // коcтыль из sisocks.h
#define SOCK_ERRORS  // verbose socket errors

#include "remote_connect_RServ/Rconnection.h"
#include "remote_connect_RServ/sisocks.h"

ChooseMenu::ChooseMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMenu)
{
    ui->setupUi(this);
    QPixmap viewDataPixar(
                "/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/viewData.png");
    ui->viewData->setIcon(viewDataPixar);
    QPixmap viewDataSourcePixar(
                "/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/viewDataSource.png");
    ui->viewDataSource->setIcon(viewDataSourcePixar);
    QPixmap viewForecastPixar(
                "/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/viewForecast.png");
    ui->viewForecast->setIcon(viewForecastPixar);
    QPixmap viewStatisticPixar(
                "/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/viewStatistic.png");
    ui->viewStatistic->setIcon(viewStatisticPixar);

    QIcon pix("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/retry.png");
    ui->retryConnect->setIcon(pix);
    ui->retrySocket->setIcon(pix);
    ui->retryDB->setIcon(pix);
    QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/unsuccessfull.png");

    ui->statusServer->setPixmap(myPixmap);
    if(ConnectorDB::tryConnection("tcp://127.0.0.1:3306", "neural_network", "neural",
                                  "forecast_time_series"))
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/successfull.png");
        ui->statusDB->setPixmap(myPixmap);
        ui->retryDB->setVisible(false);
    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/unsuccessfull.png");
        ui->statusDB->setPixmap(myPixmap);
        ui->retryDB->setVisible(true);
    }
    Rconnection* rc = new Rconnection();
    if(!rc->connect())
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/successfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(false);

    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/unsuccessfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(true);
    }
}


ChooseMenu::~ChooseMenu()
{
    delete ui;
}

void ChooseMenu::on_viewData_clicked()
{
    ViewData* p = new ViewData(this);
    p->show();
}

void ChooseMenu::on_retryConnect_clicked()
{
    system("R CMD Rserve --no-save");
    Rconnection* rc = new Rconnection();
    if(!rc->connect())
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/successfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(false);

    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/unsuccessfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(true);
    }

}

void ChooseMenu::on_viewForecast_clicked()
{
    ViewForecast* p = new ViewForecast();
    p->show();
}
