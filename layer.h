#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"

class Layer
{
public:
    std::vector<Neuron> neurons;

    Layer(int numberNeurons, int numberInputs)
    {
        for(int n=0; n < numberNeurons; n++)
        {
            neurons.push_back( Neuron(numberInputs) );
        }
    }
};

#endif // LAYER_H
