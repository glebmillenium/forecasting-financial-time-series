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
}
