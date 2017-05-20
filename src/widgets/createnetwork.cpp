#include "createnetwork.h"
#include "ui_createnetwork.h"
#include "core/formationpredictedmodel.h"
#include "core/statisticalparameters.h"
#include <QDebug>
#include <vector>

CreateNetwork::CreateNetwork(int col, int maxCol, QStandardItemModel* model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateNetwork)
{
    this->model = model;
    ui->setupUi(this);
    for(int i = 1; i <= maxCol; i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }
    ui->comboBox->setCurrentIndex(col);
    ui->lineEdit->setText("5");
}

CreateNetwork::~CreateNetwork()
{
    delete ui;
}

void CreateNetwork::on_pushButton_clicked()
{
    int chooseCols = ui->comboBox->currentText().toInt() - 1;
    int size = 0;
    vector<float> ar;
    QRegExp re("\\d*\.\\d*");
    QString temp;
    for(int i = this->model->rowCount() - 1; i >= 0; i--)
    {
        temp = model->item(i, chooseCols)->text();
        if(re.exactMatch(temp))
        {
            ar.push_back(temp.toFloat());
        }
    }
    float currentValue = ar.at(ar.size() - 1);
    ar = StatisticalParameters::getDifferentionSeries(ar);
    StatisticalParameters* sp = new StatisticalParameters(ar);
    vector<float> scaledVector = sp->getScaledVectorForHyperbolicTangens();
    //sp->removeOfEmissions();

    FormationPredictedModel* fpm = new FormationPredictedModel(scaledVector, 0.0);
    fpm->genesisNeuralNetwork();
    vector<float> predict = fpm->predicted(7);

    float last = currentValue;
    for(int i = predict.size() - 1; i >= 0; i--)
    {
        currentValue += sp->getScaledReverseValueHyperbolicTangens(predict.at(i));
        qDebug() << currentValue;
    }
    qDebug() << "Old value: " << last;
}
