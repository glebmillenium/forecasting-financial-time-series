#include "mainwindow.h"

class DateScaleDraw: public QwtScaleDraw
{
public:
    DateScaleDraw( const QTime &base ):
        baseTime( base )
    {
        setLabelRotation( -45.0 );
    }
    virtual QwtText label( double v ) const
    {
        return (QwtText) "Dada";
    }

private:
    QTime baseTime;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

    const char* fileName = "file.csv";
    const char* link =
            "https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff";
    InteractionWithNetwork::getQuandlData(link, fileName);
    model = new QStandardItemModel(InteractionWithNetwork::countRowsInTable(fileName),
                                   InteractionWithNetwork::countColumnsInTable(fileName));
    InteractionWithNetwork::setNameColumns(model, fileName);
    InteractionWithNetwork::fillingTable(fileName, model, this);
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
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


void MainWindow::on_pushButton_2_clicked()
{
    upload = new DialogUploadData();
    upload->show();
}

void MainWindow::setGraphData()
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

void MainWindow::on_ButtonAddRow_clicked()
{
    int row = model->rowCount();
    model->insertRows(row,1);
    QModelIndex index = model->index(row, 0);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void MainWindow::on_ButtonPasteRow_clicked()
{
    int row = ui->tableView->currentIndex().row();
    model->insertRows(row,1);
    QModelIndex index = model->index(row, 1);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void MainWindow::on_ButtonDeleteRow_clicked()
{
    model->removeRows(ui->tableView->currentIndex().row(), 1);
}

