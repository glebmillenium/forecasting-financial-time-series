#include "choosemenu.h"
#include "ui_choosemenu.h"

ChooseMenu::ChooseMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMenu)
{
    ui->setupUi(this);
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
