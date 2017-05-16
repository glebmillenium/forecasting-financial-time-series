#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "qdebug.h"
#include "../core/statisticalparameters.h"
#include "../core/neuronetwork.h"
#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "qwt_scale_draw.h"
#include "ui_mainwindow.h"
#include "../core/interactionwithnetwork.h"
#include "dialoguploaddata.h"
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableWidgetItem>
#include "../core/datescaledraw.h"
#include "../core/connectordb.h"
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

    void on_ButtonAddRow_clicked();

    void on_ButtonPasteRow_clicked();

    void on_ButtonDeleteRow_clicked();

    void on_ButtonUploadData_clicked();

    void changeIndex(int index);

    void changeIndex2(int index);

private:

    Ui::ViewData *ui;
    DialogUploadData* upload = new DialogUploadData(this);
    QMetaObject::Connection m_connection;
    QStandardItemModel *model;
    QwtPlot *plot;
    QwtPlotCurve *curve;
    ConnectorDB* conn;
    void setGraphData();
    void beginSelectCombobox();
    vector<tuple<int, QString>> TypeResource;
    vector<tuple<int, QString, QString, QString, int>> DataResource;
    vector<tuple<int, QString>> NeuralNetwork;
};

#endif // VIEWDATA_H
