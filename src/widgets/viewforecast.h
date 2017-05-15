#ifndef VIEWFORECAST_H
#define VIEWFORECAST_H

#include <QWidget>
#include "../core/statisticalparameters.h"
#include "../core/neuronetwork.h"
#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "qwt_scale_draw.h"
#include "../core/interactionwithnetwork.h"
#include "dialoguploaddata.h"
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableWidgetItem>
#include "../core/datescaledraw.h"
#include "../core/connectordb.h"
#include <QString>
#include <tuple>

namespace Ui {
class ViewForecast;
}

class ViewForecast : public QWidget
{
    Q_OBJECT

public:
    explicit ViewForecast(QWidget *parent = 0);
    ~ViewForecast();

private slots:
    void changeIndex(int index);

private:
    Ui::ViewForecast *ui;
    QwtPlot *plot;
    QwtPlotCurve *curve;
    ConnectorDB* conn;
    vector<tuple<int, QString>> TypeResource;
    vector<tuple<int, QString, QString, QString, int>> DataResource;
    vector<tuple<int, QString>> NeuralNetwork;

    void setGraphData();
    void beginSelectCombobox();
};

#endif // VIEWFORECAST_H
