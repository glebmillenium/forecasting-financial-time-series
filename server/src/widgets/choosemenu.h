#ifndef CHOOSEMENU_H
#define CHOOSEMENU_H

#include "../core/connectordb.h"
#include <QString>
#include "viewforecast.h"
#include "../socket/managersocket.h"
#include <QWidget>
#include "viewdata.h"
#include "settings.h"
#include "../core/connectordb.h"
#include <iostream>
#include <thread>

using namespace std;
using std::cout;
namespace Ui {
class ChooseMenu;
}

class ChooseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseMenu(QWidget *parent = 0);
    ~ChooseMenu();
private slots:
    void on_viewData_clicked();

    void on_retryConnect_clicked();

    void on_viewForecast_clicked();

    void on_retryDB_clicked();

    void on_retrySocket_clicked();

private:
    Ui::ChooseMenu* ui;
    std::thread first;
    static void startSocket();
};

#endif // CHOOSEMENU_H
