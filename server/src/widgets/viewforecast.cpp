#include "viewforecast.h"
#include "ui_viewforecast.h"
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include "qwt_picker_machine.h"

ViewForecast::ViewForecast(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewForecast)
{
    ui->setupUi(this);
    setPlotter();
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    this->conn = new ConnectorDB();
    beginSelectCombobox();
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
            double year = QString(pieces.at(0)).toDouble();
            double month = QString(pieces.at(1)).toDouble();
            month--;
            double day = QString(pieces.at(2)).toDouble();
            dateCol.push_back(fromDateToDouble(year, month, day));
        }
    }
    setGraphData(dateCol, ar);
    ui->pushButton_2->setVisible(false);
}

double ViewForecast::fromDateToDouble(double year, double month, double day)
{
    return year * 100 + (100 * (30.4 * month + day) / 366.0001);
}

void ViewForecast::setPlotter()
{
    plot_data = new QwtPlot(this->ui->widget);
    plot_data->setAxisScaleDraw(QwtPlot::xBottom, new DateScaleDraw(QTime::currentTime()));

    // Включить сетку
    QwtPlotGrid *grid = new QwtPlotGrid(); //
    grid->setMajorPen(QPen( Qt::gray, 1 )); // цвет линий и толщина
    grid->attach( plot_data ); // добавить сетку к полю графика
    // Включить возможность приближения/удаления графика
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(plot_data->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
    // Включить возможность перемещения по графику
    QwtPlotPanner *d_panner = new QwtPlotPanner( plot_data->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
    // Включить отображение координат курсора и двух перпендикулярных
    // линий в месте его отображения
    // #include <qwt_plot_picker.h>

     // настройка функций
    QwtPlotPicker *d_picker =
            new QwtPlotPicker(
                QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
    QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
    QwtPicker::ActiveOnly, // включение/выключение
    plot_data->canvas() ); // ассоциация с полем
    // Цвет перпендикулярных линий
    d_picker->setRubberBandPen( QColor( Qt::red ) );

    // цвет координат положения указателя
    d_picker->setTrackerPen( QColor( Qt::black ) );

    // непосредственное включение вышеописанных функций
    d_picker->setStateMachine( new QwtPickerDragPointMachine() );

    curve = new QwtPlotCurve("x(y)");
    curve->setStyle(QwtPlotCurve::Lines);
    curve->setPen( Qt::blue, 2 ); // цвет и толщина кривой
    curve->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    // Маркеры кривой
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2), QSize(3, 3));
    curve->setSymbol( symbol );

    curvePredict = new QwtPlotCurve("x(y)");
    curvePredict->setStyle(QwtPlotCurve::Lines);
    curvePredict->setPen( Qt::green, 2 ); // цвет и толщина кривой
    curvePredict->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    // Маркеры кривой
    QwtSymbol *symbol2 = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2), QSize(3, 3));
    curvePredict->setSymbol( symbol2 );
}

ViewForecast::~ViewForecast()
{
    delete ui;
}

void ViewForecast::setGraphData(vector<double> date, vector<double> value)
{
    plot_data->setTitle( "Qwt demonstration" ); // заголовок
    plot_data->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    plot_data->setAxisTitle(QwtPlot::yLeft, "Y");
    plot_data->setAxisTitle(QwtPlot::xBottom, "X");
    plot_data->insertLegend( new QwtLegend() );

    curve->setTitle( "Demo Curve" );


    int n = date.size();
    double x[n];
    double y[n];
    for(int i = 0; i < n; i++)
    {
         x[i] = date.at(i);
         y[i] = value.at(i);
    }
    curve->setSamples(x,y,n);
    curve->attach(plot_data);
    plot_data->resize(500, 350);
    plot_data->replot();
}

void ViewForecast::setGraphPredict(vector<double> date, vector<double> value)
{
    plot_data->setTitle( "Qwt demonstration" ); // заголовок
    plot_data->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    plot_data->setAxisTitle(QwtPlot::yLeft, "Y");
    plot_data->setAxisTitle(QwtPlot::xBottom, "X");
    plot_data->insertLegend( new QwtLegend() );

    curvePredict->setTitle( "Predict" );


    int n = date.size();
    double x[n];
    double y[n];
    for(int i = 0; i < n; i++)
    {
         x[i] = date.at(i);
         y[i] = value.at(i);
    }
    curvePredict->setSamples(x,y,n);
    curvePredict->attach(plot_data);
    plot_data->resize(500, 350);
    plot_data->replot();
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
                double year = QString(pieces.at(0)).toDouble();
                double month = QString(pieces.at(1)).toDouble();
                month--;
                double day = QString(pieces.at(2)).toDouble();
                dateCol.push_back(year * 100 + (100 * (30.4 * month + day) / 366.0001));
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
        ui->pushButton_2->setVisible(true);
    }
    else
    {
        p->close();
        ui->pushButton_2->setVisible(false);
    }
}

void ViewForecast::on_pushButton_2_clicked()
{
    QStringList pieces = model->item(0, 0)->text().split("-");
    double year = QString(pieces.at(0)).toDouble();
    double month = QString(pieces.at(1)).toDouble();
    month--;
    double day = QString(pieces.at(2)).toDouble();
    vector<double> date;
    date.push_back(year * 100 + (100 * (30.4 * month + day) / 366.0001));
    for(int i = 1; i <= 7; i++)
    {
        date.push_back(year * 100 + (100 * (30.4 * month + day + i) / 366.0001));
    }
    vector<double> predict = p->releasePredict(7);
    setGraphPredict(date, predict);
    char* namePredictFile = std::to_string(conn->getFreeIdNeuralNetwork()).c_str();
    //this->NeuralNetwork[index];
}
