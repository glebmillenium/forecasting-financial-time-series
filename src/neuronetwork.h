#ifndef NEURONETWORK_H
#define NEURONETWORK_H
#include "floatfann.h"

class NeuroNetwork
{
public:
    NeuroNetwork(int input, int output, float* listData, int listDataSize);
private:
    fann *ann;
    struct fann_train_data *data;
};

#endif // NEURONETWORK_H
