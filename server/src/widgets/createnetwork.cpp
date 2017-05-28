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
    ui->scale->addItem("Линейное шкалирование");
    ui->scale->addItem("Мягкое шкалирование");
    ui->comboBox->setCurrentIndex(col);
    ui->lineEdit->setText(std::to_string(errorLearning).c_str());
}

CreateNetwork::~CreateNetwork()
{
    delete ui;
}

vector<double> CreateNetwork::getPredict()
{
    return this->predictValues;
}

vector<double> CreateNetwork::releasePredict(int step)
{
    bool DS = false;
    bool emissions = false;
    bool linearScale = true;
    if(ui->DS->isChecked()) DS = true;
    if(ui->emissions->isChecked()) emissions = true;
    if(ui->scale->currentIndex() == 1) linearScale = false;
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
    if(DS)
    {
        ar = StatisticalParameters::getDifferentionSeries(ar);
    }
    currentValue = lastValue;
    sp = new StatisticalParameters(ar);
    if(linearScale)
    {
        scaledVector = sp->getScaledVectorForHyperbolicTangens();
    }
    else
    {
        scaledVector = sp->getScaledVectorForHyperbolicTangens_2();
    }
    if(emissions)
    {
        //sp->removeOfEmissions();
    }
    t=clock();
    if(linearScale)
    {
        fpm = new FormationPredictedModel(scaledVector, 0.0, FANN_SIGMOID_SYMMETRIC, FANN_TRAIN_RPROP);
    }
    else
    {
        fpm = new FormationPredictedModel(scaledVector, 0.0, FANN_SIGMOID, FANN_TRAIN_RPROP);
    }
    fpm->genesisNeuralNetwork();
    predict = fpm->predicted(7);
    predictValues.clear();
    predictValues.push_back(currentValue);
    qDebug() << "Old value: " << currentValue;
    for(int i = 0; i < predict.size(); i++)
    {
        if(linearScale)
        {
            delta = sp->getScaledReverseValueHyperbolicTangens(predict.at(i));
        }
        else
        {
            delta = sp->getScaledReverseValueHyperbolicTangens_2(predict.at(i));
        }
        if(DS)
        {
            currentValue += delta;
        } else
        {
            currentValue = delta;
        }
        predictValues.push_back(currentValue);
        qDebug() << "value: " << currentValue;
    }
    qDebug() << "----------Time: " << clock() - t << " --------";
    return this->predictValues;
}
