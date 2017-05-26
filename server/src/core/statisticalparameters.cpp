#include "statisticalparameters.h"

#define MAIN         // коcтыль из sisocks.h
#define SOCK_ERRORS  // verbose socket errors

#include "remote_connect_RServ/Rconnection.h"
#include "remote_connect_RServ/sisocks.h"

StatisticalParameters::StatisticalParameters(vector<float> sampleFromStatistic)
{
    this->sample = sampleFromStatistic;
}

int StatisticalParameters::getSizeSample(){
    return this->sample.size();
}

float StatisticalParameters::getExpectedValue()
{
    float expectedValue = 0.0;
    for(int i = 0; i < sample.size(); i++)
    {
        expectedValue += sample.at(i);
    }
    return expectedValue /= sample.size();
}

float StatisticalParameters::getStandartDeviation()
{
    float dispersion = 0.0;
    float expectedValue = getExpectedValue();
    for(int i = 0; i < this->sample.size(); i++){
        dispersion += (sample.at(i) - expectedValue) *
                (sample.at(i) - expectedValue);
    }
    dispersion /= sample.size();
    return sqrt(dispersion);
}

vector<float> StatisticalParameters::getSample()
{
    return this->sample;
}

float StatisticalParameters::getMinValue()
{
    float min = sample.at(0);
    for(int i = 0; i < sample.size(); i++)
    {
        if(sample.at(i) < min)
        {
            min = sample.at(i);
        }
    }
    return min;
}

float StatisticalParameters::getMaxValue()
{
    float max = sample.at(0);
    for(int i = 0; i < sample.size(); i++)
    {
        if(sample.at(i) > max)
        {
            max = sample.at(i);
        }
    }
    return max;
}

vector<float> StatisticalParameters::getDifferentionSeries(vector<float> series)
{
    for(int i = 0; i < series.size() - 1; i++)
    {
        series.at(i) = series.at(i + 1) - series.at(i);
    }
    series.pop_back();
    return series;
}

bool StatisticalParameters::checkStateRServe()
{
    initsocks(); // нужно только под Win32 - ничего не делает в unix
    Rconnection *rc = new Rconnection();
    int i = rc->connect();
    if(i)
        return false;
    else
        return true;
}

vector<float> StatisticalParameters::getScaledVectorForHyperbolicTangens()
{
    float x_min = getMinValue();
    float x_max = getMaxValue();
    vector<float> result;
    for(int i = 0; i < sample.size(); i++)
    {
        result.push_back(getScaledValueHyperbolicTangens(sample.at(i), x_min, x_max));
    }
    return result;
}

vector<float> StatisticalParameters::getScaledVectorForHyperbolicTangens_2()
{
    float M = getExpectedValue();
    float sigma = this->getStandartDeviation();
    vector<float> result;
    float temp;
    for(int i = 0; i < sample.size(); i++)
    {
        temp = (sample.at(i) - M) / (3 * sigma / (2.0 * M_PI));
        result.push_back(1.0 / (1 + exp(-temp)));
    }
    return result;
}

vector<float> StatisticalParameters::getScaledVectorForHyperbolicTangens(vector<float> otherSample)
{
    float x_min = getMinValue();
    float x_max = getMaxValue();
    vector<float> result;
    for(int i = 0; i < otherSample.size(); i++)
    {
        result.push_back(getScaledValueHyperbolicTangens(otherSample.at(i), x_min, x_max));
    }
    return result;
}



float StatisticalParameters::getScaledValueHyperbolicTangens(float x)
{
    float x_min = getMinValue();
    float x_max = getMaxValue();
    StatisticalParameters::getScaledValueHyperbolicTangens(x, x_min, x_max);
}

float StatisticalParameters::getScaledValueHyperbolicTangens(float x, float x_min, float x_max)
{
    float a = -1.0;
    float b = 1.0;
    return (x - x_min) * (b - a) / (x_max - x_min) + a;
}

float StatisticalParameters::getScaledReverseValueHyperbolicTangens(float x)
{
    float x_min = getMinValue();
    float x_max = getMaxValue();
    return getScaledReverseValueHyperbolicTangens(x, x_min, x_max);
}

float StatisticalParameters::getScaledReverseValueHyperbolicTangens(float x, float x_min, float x_max)
{
    float a = -1.0;
    float b = 1.0;
    return x_min + (x - a) * (x_max - x_min) / (b - a);
}

float StatisticalParameters::getScaledReverseValueHyperbolicTangens_2(float x)
{
    float M = getExpectedValue();
    float sigma = this->getStandartDeviation();
    return M + 3.0 * sigma * log(sqrt(-1.0 + 1.0 / (1.0 - x))) / M_PI;
}

int StatisticalParameters::removeOfEmissions()
{
    initsocks(); // нужно только под Win32 - ничего не делает в unix
    Rconnection *rc = new Rconnection();
    int i = rc->connect();
    double d[] = {1.5, 2.4, 5.6, -1.2, 0.6, 1.7, 1.0, 2.0, -0.5};/*[this->sample.size()];
    for(int i = 0; i < this->sample.size(); i++)
    {
        d[i] = sample.at(i);
    }*/
    Rdouble* rd = new Rdouble(d, 9);
    rc->assign("d", rd);
    delete rd;
    rc->eval("library(tseries);");
    rc->eval("library(nortest);");
    rc->eval("library(fBasics);");
    rc->eval("result <- cvmTest(d);");
    Rdouble *x = (Rdouble*) rc->eval("result@test$statistic;");
    qDebug() << "input1";
    if (1) {
            qDebug() << "input2";
            qDebug() << x->doubleAt(0) << "\n";
    } else {
        cout << "BAD";
    }

    delete rc;
    // создаем объект подключения к Rserve.
    // Параметры конструктора по умолчанию - "127.0.0.1", 6311.
    // если хотим использовать unix sockets, то следует передавать такие параметры:
    // Rconnection *rc = new Rconnection("/home/zoberg/mysocket", -1);
    /*Rconnection *rc = new Rconnection();

    int i=rc->connect();
    if (i) {
        char msg[128];
        sockerrorchecks(msg, 128, -1);
        printf("unable to connect (result=%d, socket:%s).\n", i, msg); return i;
    }

    double d[6] = { 1.5, 2.4, 5.6, -1.2, 0.6, 1.7 };

    // присвоим определенный выше массив переменной "a" в R
    Rdouble *rd = new Rdouble(d, 6);
    rc->assign("a", rd);
    delete rd;
    qDebug() << "input";
    // создаем матрицу "b" размером 2 x 3 и считаем произведение матриц b * t(b)
    Rdouble *x = (Rdouble*) rc->eval("b<-matrix(a,2); b%*%t(b)");

    if (x) { // если всё прошло хорошо, то получаем результат
        cout << x << "\n";

        // получим размерность получившейся в результате матрицы
        Rinteger *dim = (Rinteger*) x->attribute("dim");
        if (dim)
            cout << dim->intAt(0) << " by " << dim->intAt(1) << " matrix\n";

        // выведем матрицу результата (без форматирования)
        double *d = x->doubleArray();
        int i=0, ct = x->length();
        while (i < ct) {
            cout << d[i++] << " ";
        }
        cout << "\n";

        // освободим память
        delete x;
    }

    // присваивание массива целых чисел переменной i в R
    int ia[6] = { 1, 4, 6, 3, 5 , 2 };
    Rinteger *ri = new Rinteger(ia, 6);
    rc->assign("i", ri);
    delete ri;

    // Ирисы Фишера — это набор данных для задачи классификации,
    // на примере которого Рональд Фишер в 1936 году продемонстрировал
    // работу разработанного им метода дискриминантного анализа.
    // Этот набор данных есть в R, получим его
    Rvector *iris = (Rvector*) rc->eval("data(iris); iris");
    if (!iris) {
        cout << "oops! couldn't get iris data\n"; delete rc; return 0;
    }

    // теперь из этого набора данных выберем ширину чашелистиков (sepal width) -
    // дешевая операция без обращения к Rserve, так как мы уже имеем все необходимые данные
    Rdouble *sw = (Rdouble*) iris->byName("Sepal.Width");
    double *swd = sw->doubleArray();

    // and print it ...
    {
        int i=0, ct=sw->length();
        while (i<ct) {
            cout << swd[i++] << " ";
        }
        cout << "\n";
     }

    // Следует освобождать только память, выделенную под iris,
    // деструктор sw вызывается автоматически.
    delete iris;

    // освободим объект соединения. Соединение будет разорвано.
    delete rc;*/
}
