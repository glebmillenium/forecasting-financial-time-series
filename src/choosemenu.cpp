#include "choosemenu.h"
#include "ui_choosemenu.h"
#include "connectordb.h"
#include <QString>

ChooseMenu::ChooseMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMenu)
{
    ui->setupUi(this);
    ui->statusServer->setText(QString::fromUtf8(ConnectorDB::tryConnection("tcp://127.0.0.1:3306", "neural_network", "neural",
                                                        "forecast_time_series")));
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


