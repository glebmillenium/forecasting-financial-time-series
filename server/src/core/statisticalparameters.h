#ifndef STATISTICALPARAMETERS_H
#define STATISTICALPARAMETERS_H
#include "qdebug.h"
#include "malloc.h"
#include <math.h>
#include <vector>
using namespace std;

class StatisticalParameters
{
public:
    StatisticalParameters(vector<float> sampleFromStatistic);
    float* getTreatmentDataRecording(int classifier);
    int getSizeSample();
    float getExpectedValue();
    float getStandartDeviation();
    int removeOfEmissions();
    vector<float> getSample();
    float getMinValue();
    float getMaxValue();
    static vector<float> getDifferentionSeries(vector<float> series);
    static bool checkStateRServe();
    vector<float> getScaledVectorForHyperbolicTangens();
    vector<float> getScaledVectorForHyperbolicTangens(vector<float> otherSample);
    vector<float> getScaledVectorForHyperbolicTangens_2();
    float getScaledReverseValueHyperbolicTangens_2(float x);
    float getScaledValueHyperbolicTangens(float x);
    static float getScaledValueHyperbolicTangens(float x, float x_min, float x_max);
    float getScaledReverseValueHyperbolicTangens(float x);
    static float getScaledReverseValueHyperbolicTangens(float x, float x_min, float x_max);
private:
    vector<float> sample;
    float quantileFunctionOfTheNormalDistribution(float p);
};

#endif // STATISTICALPARAMETERS_H
