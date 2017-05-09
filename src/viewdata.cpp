#include "viewdata.h"
#include "ui_viewdata.h"


ViewData::ViewData(QWidget *parent) :
    ui(new Ui::ViewData)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);

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
    /*const char* fileName = "file.csv";
    const char* link =
            "https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff";
    InteractionWithNetwork::getQuandlData(link, fileName);
    model = new QStandardItemModel(InteractionWithNetwork::countRowsInTable(fileName),
                                   InteractionWithNetwork::countColumnsInTable(fileName));
    InteractionWithNetwork::setNameColumns(model, fileName);
    InteractionWithNetwork::fillingTable(fileName, model, this);
    */

}

ViewData::~ViewData()
{
    delete ui;
}

void ViewData::on_pushButton_clicked()
{
    float sample[model->rowCount()];
    for(int i = 0; i < model->rowCount(); i++){
        sample[i] = model->data(model->index(i, 1),Qt::DisplayRole).toFloat();
    }
    StatisticalParameters *statistic = new StatisticalParameters(sample, sizeof(sample)/sizeof(float));
    float* data = statistic->getTreatmentDataRecording(8);
    //qDebug() << data[0];
    NeuroNetwork *network = new NeuroNetwork(3, 1, data, statistic->getSizeSample());
}

void ViewData::setGraphData()
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
    upload->showing(QString("https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff"));
    if (upload->exec() == QDialog::Accepted)
    {
       this->model = upload->model;
       ui->tableView->setModel(this->model);
    }
}
