#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStringListModel listModel;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_ButtonAddRow_clicked();

    void on_ButtonPasteRow_clicked();

    void on_ButtonDeleteRow_clicked();

    void on_ButtonUploadData_clicked();

private:
    Ui::MainWindow *ui;
    DialogUploadData *upload;
    QStandardItemModel *model;
    QwtPlot *plot;
    QwtPlotCurve *curve;
    void setGraphData();
};

#endif // MAINWINDOW_H
