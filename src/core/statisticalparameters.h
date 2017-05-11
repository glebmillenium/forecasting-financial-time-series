#ifndef STATISTICALPARAMETERS_H
#define STATISTICALPARAMETERS_H
#include "malloc.h"
#include "qdebug.h"
#include <math.h>

class StatisticalParameters
{
public:
    StatisticalParameters(float* sampleFromStatistic, int size);
    float* getTreatmentDataRecording(int classifier);
    int getSizeSample();
private:
    float *sample;
    int sampleSize = -1;
    float expectedValue = -1.0;
    float standardDeviation = -1.0;
    float dispersion = -1.0;
    float quantileFunctionOfTheNormalDistribution(float p);
};

#endif // STATISTICALPARAMETERS_H
