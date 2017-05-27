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
    this->conn = new ConnectorDB();

    beginSelectCombobox();
}

ViewForecast::~ViewForecast()
{
    delete ui;
}

void ViewForecast::setGraphData(vector<double> date, vector<double> value)
{
    int n = date.size();
    double x[n];
    double y[n];
    for(int i = 0; i < n; i++)
    {
         x[i] = date.at(i);
         y[i] = value.at(i);
    }
    curve->setSamples(x,y,n);
    curve->attach(plot);
    plot->replot();
}

void ViewForecast::beginSelectCombobox()
{
    this->TypeResource = conn->selectTypeResource();
    if(TypeResource.size() != 0)
    {
        for(int i = 0; i < TypeResource.size(); i++)
        {
            ui->TypeMaterial->addItem(std::get<1>(TypeResource[i]));
        }
        ui->Mark->clear();
        int index = ui->TypeMaterial->currentIndex();
        tuple<int, QString> getter = TypeResource[index];
        this->DataResource = conn->selectDataResource(std::get<0>(getter));

        if(DataResource.size() != 0)
        {
            for(int i = 0; i < DataResource.size(); i++)
            {
                ui->Mark->addItem(std::get<3>(DataResource[i]));
            }

            const char* fileName = qPrintable(std::get<2>(this->DataResource[index]));
            char* fullFileName = new char[256];

            sprintf(fullFileName, "%s%s", dataStore, fileName);
            int countColumns = InteractionWithNetwork::countColumnsInTable(fullFileName);
            int countRows = InteractionWithNetwork::countRowsInTable(fullFileName);
            model = new QStandardItemModel(countRows, countColumns);
            InteractionWithNetwork::setNameColumns(model, fullFileName);

            InteractionWithNetwork::fillingTable(fullFileName, model, this);
            ui->tableView->setModel(model);

            m_connection = connect(ui->Mark, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex2(int)));
            connect(ui->TypeMaterial, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex(int)));
            index = ui->Mark->currentIndex();
            this->NeuralNetwork = conn->getNeuralNetwork(std::get<0>(this->DataResource[index]));
            if(this->NeuralNetwork.size() != 0)
            {
                for(int i = 0; i < this->NeuralNetwork.size(); i++)
                {
                    ui->NeuralNetwork->addItem(std::get<1>(this->NeuralNetwork[i]));
                }
                changeIndex3(ui->NeuralNetwork->currentIndex());
                n_connection = connect(ui->NeuralNetwork, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex3(int)));
                p = new CreateNetwork(1, model->columnCount(), this->model, ui->widget_2);
                ui->pushButton->setChecked(false);
                p->close();
            }
        }
    }

}

void ViewForecast::changeIndex(int index)
{
    tuple<int, QString> getter = TypeResource[index];
    this->DataResource = conn->selectDataResource(std::get<0>(getter));
    QObject::disconnect(m_connection);
    ui->Mark->clear();
    if(this->DataResource.size() != 0)
    {
        for(int i = 0; i < DataResource.size(); i++)
        {
            ui->Mark->addItem(std::get<3>(DataResource[i]));
        }
        changeIndex2(ui->Mark->currentIndex());
        m_connection = connect(ui->Mark, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex2(int)));
    }
}

void ViewForecast::changeIndex2(int index)
{
    model->clear();
    ui->NeuralNetwork->clear();
    char* fullFileName = new char[256];
    sprintf(fullFileName, "%s%s", dataStore,
            std::get<2>(this->DataResource[index]).toStdString().c_str());
    int countRows = InteractionWithNetwork::countRowsInTable(fullFileName);
    if(countRows > -1)
    {
        QObject::disconnect(n_connection);
        int countColumns = InteractionWithNetwork::countColumnsInTable(fullFileName);
        model = new QStandardItemModel(countRows, countColumns);
        InteractionWithNetwork::setNameColumns(model, fullFileName);
        InteractionWithNetwork::fillingTable(fullFileName, model, this);
        ui->tableView->setModel(model);
        this->NeuralNetwork = conn->getNeuralNetwork(std::get<0>(this->DataResource[index]));
        if(this->NeuralNetwork.size() != 0)
        {
            for(int i = 0; i < this->NeuralNetwork.size(); i++)
            {
                ui->NeuralNetwork->addItem(std::get<1>(this->NeuralNetwork[i]));
            }
            changeIndex3(ui->NeuralNetwork->currentIndex());
            n_connection = connect(ui->NeuralNetwork, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex3(int)));
        }
        changeIndex3(ui->NeuralNetwork->currentIndex());
        delete p;


        QString temp;
        QRegExp re("\\d*\.\\d*");
        vector<double> dateCol;
        vector<double> ar;
        for(int i = model->rowCount() - 1; i >= 0; i--)
        {
            QStringList pieces = model->item(i, 0)->text().split("-");
            temp = model->item(i, 1)->text();
            if(re.exactMatch(temp))
            {
                ar.push_back(temp.toDouble());
                int year = QString(pieces.at(0)).toInt();
                int month = QString(pieces.at(1)).toInt();
                int day = QString(pieces.at(2)).toInt();

                dateCol.push_back(year * 10000 + month * 100 + day);
            }
        }

        setGraphData(dateCol, ar);

        p = new CreateNetwork(1, model->columnCount(), this->model, ui->widget_2);
        ui->pushButton->setChecked(false);
        ui->tabWidget->setCurrentWidget(ui->tab);
        n_connection = connect(ui->NeuralNetwork, SIGNAL(currentIndexChanged(int)), SLOT(changeIndex3(int)));
    }
}

void ViewForecast::changeIndex3(int index)
{
    //this->NeuralNetwork[index]
}

void ViewForecast::on_pushButton_clicked()
{
    ui->tab_3->setHidden(false);
    if(ui->pushButton->isChecked())
    {
        p->show();
        ui->tabWidget->setCurrentWidget(ui->tab_3);
    }
    else
    {
        p->close();
    }
}
