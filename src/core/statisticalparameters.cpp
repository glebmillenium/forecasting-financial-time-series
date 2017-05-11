#include "statisticalparameters.h"

StatisticalParameters::StatisticalParameters(float* sampleFromStatistic, int size)
{
    this->expectedValue = 0.0;
    this->sampleSize = size;
    for(int i = 0; i < this->sampleSize; i++)
    {
        this->expectedValue += *(sampleFromStatistic + i);
    }
    this->expectedValue /= this->sampleSize;
    this->dispersion = 0.0;
    for(int i = 0; i < this->sampleSize; i++){
        this->dispersion += (*(sampleFromStatistic + i) - this->expectedValue) *
                (*(sampleFromStatistic + i) - this->expectedValue);
    }
    this->dispersion /= this->sampleSize;
    this->standardDeviation = sqrt(this->dispersion);
    this->sample = (float *) malloc(size * sizeof(float));
    for(int i = 0; i < this->sampleSize; i++) {
        sample[i] = *(sampleFromStatistic + i);
    }

}

float* StatisticalParameters::getTreatmentDataRecording(int classifier)
{
    float *dataRecording = new float[this->sampleSize];
    float lineSegment = ((float) 1.0) / ((float)classifier);
    float beginningSegment;
    float x0 = -1.0;
    float x1 = -1.0;
    beginningSegment = 0.0;

    qDebug() << "sigma" << this->standardDeviation << "dispersion: " << this->dispersion << "M: " << this->expectedValue;
    for(int j = 0; j < classifier; j++)
    {
        qDebug() << "y = " << beginningSegment;
        x0 = quantileFunctionOfTheNormalDistribution(beginningSegment);
        beginningSegment += lineSegment;
        x1 = quantileFunctionOfTheNormalDistribution(beginningSegment);
        qDebug() << x0 << " " << x1;
    }

    for(int i = 0; i < this->sampleSize; i++){
        beginningSegment = 0.0;
        for(int j = 0; j < classifier; j++)
        {
            if(beginningSegment == 0.0)
            {
                x0 = -100.0 * this->standardDeviation;
            }
            else
            {
                x0 = quantileFunctionOfTheNormalDistribution(beginningSegment);
            }
            beginningSegment += lineSegment;
            if(beginningSegment == 1.0){
                x1 = 100.0 * this->standardDeviation;
            }
            else
            {
                x1 = quantileFunctionOfTheNormalDistribution(beginningSegment);
            }
            if((x0 <= this->sample[i]) && (this->sample[i] < x1)){
                dataRecording[i] = beginningSegment - lineSegment / 2.0;
                break;
            }
        }
    }

    /*for(int i = 0; i < this->sampleSize; i++){
        qDebug() << dataRecording[i];
    }*/

    return dataRecording;
}

int StatisticalParameters::getSizeSample(){
    return this->sampleSize;
}

float StatisticalParameters::quantileFunctionOfTheNormalDistribution(float p)
{
    return this->expectedValue + this->standardDeviation * sqrt(2.0) * erf(2.0 * p - 1.0);
}

