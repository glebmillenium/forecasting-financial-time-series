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
    QIcon pix("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/retry.png");
    ui->retryConnect->setIcon(pix);
    ui->retrySocket->setIcon(pix);
    QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/unsuccessfull.png");

    ui->statusServer->setPixmap(myPixmap);
    if(ConnectorDB::tryConnection("tcp://127.0.0.1:3306", "neural_network", "neural",
                                  "forecast_time_series"))
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/successfull.png");
        ui->statusDB->setPixmap(myPixmap);
    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/src/other/unsuccessfull.png");
        ui->statusDB->setPixmap(myPixmap);
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

void ChooseMenu::on_settings_clicked()
{
    Settings* p = new Settings();
    p->show();
}



void ChooseMenu::on_retryConnect_clicked()
{
    system("sh /home/glebmillenium/repositories/forecasting-financial-time-series/src/other/start_R.sh");
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
