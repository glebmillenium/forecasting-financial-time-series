#include "createnetwork.h"
#include "ui_createnetwork.h"

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
    ui->lineEdit->setText(std::to_string(errorLearning).c_str());
}

CreateNetwork::~CreateNetwork()
{
    delete ui;
}

void CreateNetwork::on_pushButton_clicked()
{
    int chooseCols = ui->comboBox->currentText().toInt() - 1;
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
    float lastValue = ar.at(ar.size() - 1);
    float delta;
    int t;
    float currentValue;
    vector<float> scaledVector;
    vector<float> predict;
    FormationPredictedModel* fpm;
    StatisticalParameters* sp;
    //ar = StatisticalParameters::getDifferentionSeries(ar);


    t=clock();
    currentValue = lastValue;
    sp = new StatisticalParameters(ar);
    scaledVector = sp->getScaledVectorForHyperbolicTangens();
    //sp->removeOfEmissions();
    fpm = new FormationPredictedModel(scaledVector, 0.0, FANN_SIGMOID_SYMMETRIC, FANN_TRAIN_RPROP);
    fpm->genesisNeuralNetwork();
    predict = fpm->predicted(7);
    qDebug() << "Old value: " << currentValue;
    for(int i = 0; i < predict.size(); i++)
    {
        delta = sp->getScaledReverseValueHyperbolicTangens(predict.at(i));
        //currentValue += delta;
        qDebug() << "change:" << delta << "value: " << currentValue;
    }
    qDebug() << "----------Time: " << clock() - t << " --------";

    t=clock();
    currentValue = lastValue;
    sp = new StatisticalParameters(ar);
    scaledVector = sp->getScaledVectorForHyperbolicTangens_2();
    //sp->removeOfEmissions();
    fpm = new FormationPredictedModel(scaledVector, 0.0, FANN_SIGMOID, FANN_TRAIN_RPROP);
    fpm->genesisNeuralNetwork();
    predict = fpm->predicted(7);
    qDebug() << "Old value: " << currentValue;
    for(int i = 0; i < predict.size(); i++)
    {
        delta = sp->getScaledReverseValueHyperbolicTangens_2(predict.at(i));
        //currentValue += delta;
        qDebug() << "change:" << delta << "value: " << currentValue;
    }
    qDebug() << "----------Time: " << clock() - t << " --------";

    /*
    t=clock();
    currentValue = lastValue;
    sp = new StatisticalParameters(ar);
    scaledVector = sp->getScaledVectorForHyperbolicTangens_2();
    //sp->removeOfEmissions();
    fpm = new FormationPredictedModel(scaledVector, 0.0, FANN_SIGMOID, FANN_TRAIN_RPROP);
    fpm->genesisNeuralNetwork();
    predict = fpm->predicted(7);
    qDebug() << "Old value: " << currentValue;
    for(int i = 0; i < predict.size(); i++)
    {
        delta = sp->getScaledReverseValueHyperbolicTangens_2(predict.at(i));
        currentValue += delta;
        qDebug() << "change:" << delta << "value: " << currentValue;
    }
    qDebug() << "--------------";
    qDebug() << "----------Time: " << clock() - t << " --------";

    t=clock();
    currentValue = lastValue;
    sp = new StatisticalParameters(ar);
    scaledVector = sp->getScaledVectorForHyperbolicTangens();
    //sp->removeOfEmissions();
    fpm = new FormationPredictedModel(scaledVector, 0.0, FANN_SIGMOID_SYMMETRIC, FANN_TRAIN_QUICKPROP);
    fpm->genesisNeuralNetwork();
    predict = fpm->predicted(7);
    qDebug() << "Old value: " << currentValue;
    for(int i = 0; i < predict.size(); i++)
    {
        delta = sp->getScaledReverseValueHyperbolicTangens(predict.at(i));
        currentValue += delta;
        qDebug() << "change:" << delta << "value: " << currentValue;
    }
    qDebug() << "----------Time: " << clock() - t << " --------";

    t=clock();
    currentValue = lastValue;
    sp = new StatisticalParameters(ar);
    scaledVector = sp->getScaledVectorForHyperbolicTangens_2();
    //sp->removeOfEmissions();
    fpm = new FormationPredictedModel(scaledVector, 0.0, FANN_SIGMOID, FANN_TRAIN_QUICKPROP);
    fpm->genesisNeuralNetwork();
    predict = fpm->predicted(7);
    qDebug() << "Old value: " << currentValue;
    for(int i = 0; i < predict.size(); i++)
    {
        delta = sp->getScaledReverseValueHyperbolicTangens_2(predict.at(i));
        currentValue += delta;
        qDebug() << "change:" << delta << "value: " << currentValue;
    }
    qDebug() << "--------------";
    qDebug() << "----------Time: " << clock() - t << " --------";
    */
}
