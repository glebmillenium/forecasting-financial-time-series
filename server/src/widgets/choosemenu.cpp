#include "choosemenu.h"
#include "ui_choosemenu.h"

ChooseMenu::ChooseMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMenu)
{
    ui->setupUi(this);
    QPixmap viewDataPixar(
                "/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/viewData.png");
    ui->viewData->setIcon(viewDataPixar);
    QPixmap viewDataSourcePixar(
                "/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/viewDataSource.png");
    ui->viewDataSource->setIcon(viewDataSourcePixar);
    QPixmap viewForecastPixar(
                "/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/viewForecast.png");
    ui->viewForecast->setIcon(viewForecastPixar);
    QIcon pix("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/retry.png");
    ui->retryConnect->setIcon(pix);
    ui->retrySocket->setIcon(pix);
    ui->retryDB->setIcon(pix);
    QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/unsuccessfull.png");

    ui->statusServer->setPixmap(myPixmap);
    if(ConnectorDB::tryConnection("tcp://127.0.0.1:3306", "neural_network", "neural",
                                  "forecast_time_series"))
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/successfull.png");
        ui->statusDB->setPixmap(myPixmap);
        ui->retryDB->setVisible(false);
    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/unsuccessfull.png");
        ui->statusDB->setPixmap(myPixmap);
        ui->retryDB->setVisible(true);
    }

    if(StatisticalParameters::checkStateRServe())
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/successfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(false);

    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/unsuccessfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(true);
    }

    QPixmap myupddata("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/unsuccessfull.png");
    ui->autoupdatedata->setIcon(myupddata);
    QPixmap myupdforecast("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/unsuccessfull.png");
    ui->autoupdateforeast->setIcon(myupdforecast);
}


ChooseMenu::~ChooseMenu()
{
    first.join();

    delete ui;
    exit(0);
}

void ChooseMenu::on_viewData_clicked()
{
    ViewData* p = new ViewData(this);
    p->show();
}

void ChooseMenu::on_retryConnect_clicked()
{
    system("R CMD Rserve --no-save");
    if(StatisticalParameters::checkStateRServe())
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/successfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(false);

    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/unsuccessfull.png");
        ui->statusR->setPixmap(myPixmap);
        ui->retryConnect->setVisible(true);
    }

}

void ChooseMenu::on_viewForecast_clicked()
{
    ViewForecast* p = new ViewForecast();
    p->show();
}

void ChooseMenu::on_retryDB_clicked()
{
    system("service mysql start");
    if(ConnectorDB::tryConnection(connectDB, loginDB, passwordDB,
                                  schemeDB))
    {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/successfull.png");
        ui->statusDB->setPixmap(myPixmap);
        ui->retryDB->setVisible(false);
    } else {
        QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/unsuccessfull.png");
        ui->statusDB->setPixmap(myPixmap);
        ui->retryDB->setVisible(true);
    }
}

void ChooseMenu::on_retrySocket_clicked()
{
    first = std::thread(startSocket);
    QPixmap myPixmap("/home/glebmillenium/repositories/forecasting-financial-time-series/server/src/other/successfull.png");
    ui->statusServer->setPixmap(myPixmap);
    ui->retrySocket->setVisible(false);
}

void ChooseMenu::startSocket()
{
    ManagerSocket* ms = new ManagerSocket(6000);
    ms->run();

}

