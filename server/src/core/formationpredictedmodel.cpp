#include "formationpredictedmodel.h"
#include <QDebug>

FormationPredictedModel::FormationPredictedModel(vector<float> dataList,
                                                 double allowableLearningError,
                                                 fann_activationfunc_enum func, fann_train_enum train,
                                                 char* predictedModel,
                                                 char *method)
{
    this->func = func;
    this->dataList = dataList;
    this->allowableLearningError = allowableLearningError;
    this->numberOfInputs = 15;
    this->numberOfHidden = 1;
    this->numberOfOutputs = 1;
    this->allowedNumberMistakesInTraining = allowedNumberMistakesInTraining;
}

void FormationPredictedModel::genesisNeuralNetwork()
{
    int optimalInput, optimalHidden;
    float minimalMSETrain = 10.0, minimalMSETest = 10.0;
    int maxWindow;
    fann *formingAnn;
    if((dataList.size() - 30) < 54) maxWindow = 20; else maxWindow = 54;
    for(int inputNeuron = 3; inputNeuron < maxWindow; inputNeuron ++) // max 52
    {
        this->numberOfInputs = inputNeuron;
        struct fann_train_data* data = formingTrainDataForNeuralNetwork();

        float minHiddenNeurons = (this->numberOfOutputs * data->num_data) / (1 + log2(data->num_data));
        float maxHiddenNeurons = this->numberOfOutputs *
                (data->num_data/this->numberOfOutputs + 1) *
                (this->numberOfInputs + this->numberOfOutputs + 1) + this->numberOfOutputs;
        int L_min = ceil(minHiddenNeurons/(data->num_input + data->num_output));
        int L_max = ceil(maxHiddenNeurons/(data->num_input + data->num_output));
        //qDebug() << "Hidden min: " << L_min << " max: " << L_max;
        for(int hiddenNeuron = L_min; hiddenNeuron <= L_max; hiddenNeuron++)
        {
            this->numberOfHidden = hiddenNeuron;

            formingAnn = fann_create_standard(3, this->numberOfInputs, this->numberOfHidden, this->numberOfOutputs);
            fann_init_weights(formingAnn, data);
            setInitialStateNeuralNetwork(formingAnn);

            tuple<vector<int>, vector<int>> set = getParetoData(round(data->num_data * 0.7), data->num_data);
            vector<int> setTrain = std::get<0>(set);
            vector<int> setTest = std::get<1>(set);

            struct fann_train_data* trainData = getChooseData(data, setTrain);
            struct fann_train_data* testData = getChooseData(data, setTest);

            //qDebug() << "Start learning process: input: " << inputNeuron << " hidden: " << hiddenNeuron;
            float MSE_train;
            float MSE_test;
            for(int i = 0; i < 1500; i++)
            {
                fann_train_on_data(formingAnn, trainData, 1, 0, this->allowableLearningError);
                MSE_train = fann_get_MSE(formingAnn);
                MSE_test = fann_test_data(formingAnn, testData);

                if(MSE_test < minimalMSETrain && MSE_train < minimalMSETest)
                {
                    this->ann = formingAnn;
                    minimalMSETest = MSE_test;
                    minimalMSETrain = MSE_train;
                    optimalInput = this->numberOfInputs;
                    optimalHidden = this->numberOfHidden;
                }
            }
        }
    }
    qDebug() << "best input: " << optimalInput  << "best hidden: " << optimalHidden
             << "MSE train: " << minimalMSETrain << "MSE test: " << minimalMSETest;
    this->ready = true;
}

fann *FormationPredictedModel::getNeuralNetwork()
{
    return this->ann;
}

void FormationPredictedModel::saveNeuralNetwork(const char* fileName)
{
    fann_save(this->ann, fileName);
}

vector<float> FormationPredictedModel::predicted(int step, vector<float> otherSample)
{
    vector<float> predict;
    if(ready)
    {
        fann_type input[this->numberOfInputs];
        vector<float> newData = otherSample;
        for(int k = 0; k < step; k++)
        {
            int j = 0;
            for(int i = newData.size() - this->numberOfInputs; i < newData.size(); i++)
            {
                input[j++] = newData.at(i);
            }
            fann_type* answer = fann_run(ann, input);
            newData.push_back(answer[0]);
            predict.push_back(answer[0]);
        }
    }
    return predict;
}

vector<float> FormationPredictedModel::predicted(int step)
{
    vector<float> predict;
    if(ready)
    {
        fann_type input[this->numberOfInputs];
        vector<float> newData = dataList;
        for(int k = 0; k < step; k++)
        {
            int j = 0;
            for(int i = newData.size() - this->numberOfInputs; i < newData.size(); i++)
            {
                input[j] = newData.at(i);
                j++;
            }
            fann_type* answer = fann_run(ann, input);
            newData.push_back(answer[0]);
            predict.push_back(answer[0]);
        }
    }
    return predict;
}

fann_train_data* FormationPredictedModel::formingTrainDataForNeuralNetwork()
{
    struct fann_train_data *data;
    data = fann_create_train(this->dataList.size() - this->numberOfInputs - this->numberOfOutputs + 1,
                             this->numberOfInputs, this->numberOfOutputs);
    for(int i = 0; i < this->dataList.size() - this->numberOfInputs; i++){
        for(int j = 0; j < this->numberOfInputs; j++){
            data->input[i][j] = dataList.at(i + j);
        }
        for(int j = 0; j < this->numberOfOutputs; j++){
            data->output[i][j] = dataList.at(i + this->numberOfInputs + j);
        }
    }
    return data;
}

fann_train_data* FormationPredictedModel::getChooseData(fann_train_data* data, vector<int> choose)
{
    struct fann_train_data *result = fann_create_train(choose.size(),
                                                       this->numberOfInputs, this->numberOfOutputs);;
    for(int i = 0; i < choose.size(); i++)
    {
        result->input[i] = data->input[choose.at(i)];
        result->output[i] = data->output[choose.at(i)];
    }
    return result;
}

tuple<vector<int>, vector<int>> FormationPredictedModel::getParetoData(int needSizeTest, int maxSize)
{
    srand(time(0));
    vector<int> setTrain;
    vector<int> setTest;
    int temp;
    do
    {
       temp = rand() % maxSize;
       if(std::find(setTrain.begin(), setTrain.end(), temp) == setTrain.end())
       {
           setTrain.push_back(temp);
       }
    } while(setTrain.size() != needSizeTest);

    for(int i = 0; i < maxSize; i++)
    {
         if(std::find(setTrain.begin(), setTrain.end(), i) == setTrain.end())
         {
             setTest.push_back(i);
         }
    }
    tuple<vector<int>, vector<int>> tup = std::make_tuple(setTrain, setTest);
    return tup;
}

void FormationPredictedModel::setInitialStateNeuralNetwork(fann *ann)
{
    fann_set_train_stop_function(ann, FANN_STOPFUNC_MSE);//тип обучения: по количеству ошибок
    //fann_set_bit_fail_limit(ann, 0);//допускаемое количество ошибочных
    //fann_set_train_error_function(ann, FANN_ERRORFUNC_TANH);
    //fann_set_train_error_function(ann, FANN_ERRORFUNC_LINEAR);
    fann_set_training_algorithm(ann, this->train);
    fann_set_activation_function_hidden(ann, this->func);
    fann_set_activation_function_output(ann, this->func);
}
