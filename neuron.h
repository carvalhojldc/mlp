#ifndef NEURON_H
#define NEURON_H

#include <random>
#include <vector>

#include "outputsignal.h"

class Neuron
{
private:
    double randomWeight()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist (0,0.5);

        return dist(mt);
    }

    double sumInputs;
    OutputSignal outSignal;
    std::vector<double> inputs;

public:
    double sigma;
    std::vector<double> weights;

    Neuron(int numberInputs)
    {
        for(int i=0; i<numberInputs+1; i++)
        {
            weights.push_back( randomWeight() );
        }

        this->sigma = 0.0;
    }

    void setWeightedInput(std::vector<double> inputs)
    {
        this->inputs = inputs;
        double sum = 0.0;
        for(int i=0; i<inputs.size(); i++)
        {
            sum += inputs[i]*weights[i];
        }

        sumInputs = sum;
    }

    void updateWeights(double learningRate)
    {
        for(int w=0; w<weights.size(); w++)
        {
            weights[w] = weights[w] + learningRate * sigma * inputs[w];
        }
    }

    double getOutput()
    {
        return outSignal.tangh( sumInputs );
    }

    double getOutput_d()
    {
        return outSignal.tangh_d( sumInputs );
    }
};


#endif // NEURON_H
