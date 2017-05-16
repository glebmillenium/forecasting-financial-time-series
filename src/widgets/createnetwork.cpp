#include "createnetwork.h"
#include "ui_createnetwork.h"

CreateNetwork::CreateNetwork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateNetwork)
{
    ui->setupUi(this);
}

CreateNetwork::~CreateNetwork()
{
    delete ui;
}
