#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget = new ChooseMenu(ui->widget);
    ui->widget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Help_triggered()
{

}

void MainWindow::on_Settings_triggered()
{
    Settings* p = new Settings();
    p->show();
}
