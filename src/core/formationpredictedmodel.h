#ifndef FORMATIONPREDICTEDMODEL_H
#define FORMATIONPREDICTEDMODEL_H
#include "floatfann.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <ctime>
using namespace std;

class FormationPredictedModel
{
public:
    FormationPredictedModel(vector<float> dataList, double allowableLearningError,
                            int allowedNumberMistakesInTraining = 0,
                            char* predictedModel = "neural_network:perceptron",
                            char* method = "immersion");
    void genesisNeuralNetwork();
    vector<float> predicted(int step);
    vector<float> predicted(int step, vector<float> otherSample);
private:
    fann_train_data* formingTrainDataForNeuralNetwork();
    //vector<fann_train_data*, fann_train_data*> dividedDataForNeuralNetworkOnParetoBreakdown(fann_train_data* data);
    tuple<vector<int>, vector<int>> getParetoData(int need_size, int max_size);
    fann_train_data* getChooseData(fann_train_data* data, vector<int> choose);
    void setInitialStateNeuralNetwork(fann *ann);
    int numberOfInputs;
    int numberOfOutputs;
    int numberOfHidden;
    vector<float> dataList;
    double allowableLearningError;
    int allowedNumberMistakesInTraining;
    bool ready = false;
    fann *ann;
};

#endif // FORMATIONPREDICTEDMODEL_H
