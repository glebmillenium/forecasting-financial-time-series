#ifndef VIEWFORECAST_H
#define VIEWFORECAST_H

#include <QWidget>
#include "../core/statisticalparameters.h"
#include <QMainWindow>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "qwt_scale_draw.h"
#include "qwt_plot_grid.h"
#include "qwt_legend.h"
#include <qwt_symbol.h>
#include "../core/interactionwithnetwork.h"
#include "dialoguploaddata.h"
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableWidgetItem>
#include "../core/datescaledraw.h"
#include "../core/connectordb.h"
#include <QString>
#include <tuple>
#include "createnetwork.h"

namespace Ui {
class ViewForecast;
}

class ViewForecast : public QWidget
{
    Q_OBJECT

public:
    explicit ViewForecast(QWidget *parent = 0);
    ~ViewForecast();

    static double fromDateToDouble(double year, double month, double day);
private slots:
    void changeIndex(int index);
    void changeIndex2(int index);
    void changeIndex3(int index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::ViewForecast *ui;
    QwtPlot *plot_data;
    QwtPlotCurve *curve;
    QwtPlotCurve *curvePredict;
    ConnectorDB* conn;
    vector<tuple<int, QString>> TypeResource;
    vector<tuple<int, QString, QString, QString, int>> DataResource;
    vector<tuple<int, QString, int, int, QString, QString, QString, int, int, int>> NeuralNetwork;
    QMetaObject::Connection m_connection;
    QMetaObject::Connection n_connection;
    QStandardItemModel *model;
    void setGraphData(vector<double> date, vector<double> values);
    void beginSelectCombobox();
    void setPlotter();
    void setGraphPredict(vector<double> date, vector<double> value);
    void setForecastWidgets(int col, int maxCol);
    vector<double> releasePredict(int step);
    FormationPredictedModel* fpm;
    void saveForecast(const char *path, vector<double> predict);
    vector<double> getForecast(const char *pathForecast);
};

#endif // VIEWFORECAST_H
