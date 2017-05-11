#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "qdebug.h"
#include "statisticalparameters.h"
#include "neuronetwork.h"
#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "qwt_scale_draw.h"
#include "ui_mainwindow.h"
#include "interactionwithnetwork.h"
#include "dialoguploaddata.h"
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableWidgetItem>
#include "datescaledraw.h"
#include "connectordb.h"
#include <QString>
#include <tuple>

using namespace std;

namespace Ui {
class ViewData;
}

class ViewData : public QMainWindow
{
    Q_OBJECT

public:
    QStringListModel listModel;
    explicit ViewData(QWidget *parent = 0);
    ~ViewData();

private slots:
    void on_pushButton_clicked();

    void on_ButtonAddRow_clicked();

    void on_ButtonPasteRow_clicked();

    void on_ButtonDeleteRow_clicked();

    void on_ButtonUploadData_clicked();

private:
    Ui::ViewData *ui;
    DialogUploadData* upload = new DialogUploadData(this);
    QStandardItemModel *model;
    QwtPlot *plot;
    QwtPlotCurve *curve;
    ConnectorDB* conn;
    void setGraphData();
    void beginSelectCombobox();
    vector<tuple<int, QString>> TypeResource;
    vector<tuple<int, QString>> DataResource;
    vector<tuple<int, QString>> NeuralNetwork;
};

#endif // VIEWDATA_H
