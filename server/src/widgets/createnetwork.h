#ifndef CREATENETWORK_H
#define CREATENETWORK_H

#include <QWidget>
#include "qstandarditemmodel.h"
#include "core/formationpredictedmodel.h"
#include "core/statisticalparameters.h"
#include "core/defs.h"
#include <QDebug>
#include <vector>
#include "time.h"

using namespace std;

namespace Ui {
class CreateNetwork;
}

class CreateNetwork : public QWidget
{
    Q_OBJECT

public:
    explicit CreateNetwork(int col, int maxCol, QStandardItemModel* model, QWidget *parent = 0);
    ~CreateNetwork();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateNetwork *ui;
    QStandardItemModel* model;
};

#endif // CREATENETWORK_H
