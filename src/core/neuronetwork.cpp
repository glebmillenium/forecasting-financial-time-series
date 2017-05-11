#include "neuronetwork.h"
#include "qdebug.h"

NeuroNetwork::NeuroNetwork(int input, int output, float* listData, int listDataSize)
{
    this->ann = fann_create_standard(3, input, 4, output);
    fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);//тип обучения: по количеству ошибок
    fann_set_bit_fail_limit(ann, 0);//допускаемое количество ошибочных
    //fann_set_train_error_function(ann, FANN_ERRORFUNC_TANH);
    fann_set_train_error_function(ann, FANN_ERRORFUNC_LINEAR);
    fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
    data = fann_create_train(listDataSize - input - output, input, output);
    for(int i = 0; i < listDataSize; i++) {
        qDebug() << listData[i];
    }
    /*for(int i = 0; i < listDataSize - input; i++){
        for(int j = 0; j < input; j++){
            data->input[i][j] = *(listData + i + j);
        }
        for(int j = 0; j < output; j++){
            data->output[i][j] = *(listData + i + input + j);
        }
    }*/
}
