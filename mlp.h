#ifndef MLP_H
#define MLP_H

#include "layer.h"

class MLP
{
private:
    std::vector<Layer> network;

    std::vector<double> insertThreshold(std::vector<double> input)
    {
        std::vector<double> newInput;

        newInput.push_back(-1);
        newInput.insert(newInput.end(), input.begin(), input.end());

        return newInput;
    }

    double getError(std::vector<double> d, std::vector<double> y)
    {
        double error = 0.0;

        for(int i=0; i<d.size(); i++)
            error += pow(d[i]-y[i],2);
        error *= (1./d.size());
        return error;
    }

    double forward(std::vector<double> X)
    {
        std::vector<double> inputs;
        std::vector<double> outputs;
        Layer * layer;
        Neuron * neuron;

        inputs = insertThreshold(X);

        // run of all layers of the network
        for(int l=0; l<network.size(); l++)
        {
            layer = &(network[l]);

            outputs.clear();

            // run of all neurons of layer(l)
            for(int n=0; n<layer->neurons.size(); n++)
            {
                neuron = &(layer->neurons[n]);

                neuron->setWeightedInput(inputs);
                outputs.push_back( neuron->getOutput() );
            }

            inputs = insertThreshold(outputs);
        }

        return outputs[0];
    }

    void backForward(int x, std::vector<double> d, double learningRate)
    {
        Layer * layer;
        Neuron * neuron;

        int lastLayer = network.size()-1;
        for(int l=lastLayer; l>=0; l--)
        {
            layer = &(network[l]);

            if(l == lastLayer) // last layer
            {
                std::vector<double> dataD;
                dataD.push_back(d[x]);

                for(int n=0; n<layer->neurons.size(); n++)
                {
                    neuron = &(layer->neurons[n]);
                    neuron->sigma = (dataD[n]-neuron->getOutput())*neuron->getOutput_d();
                    neuron->updateWeights(learningRate);
                }
            }
            else // others layers
            {
                Layer * nextLayer = &(network[l+1]);
                Neuron * neuronNextLayer;

                for(int n=0; n<layer->neurons.size(); n++)
                {
                    neuron = &(layer->neurons[n]);
                    neuron->sigma = 0.0;
                    for(int nl=0; nl<nextLayer->neurons.size(); nl++)
                    {
                        neuronNextLayer = &(nextLayer->neurons[nl]);

                        neuron->sigma += (neuronNextLayer->sigma*neuronNextLayer->weights[n+1]);
                    }
                    neuron->sigma *= neuron->getOutput_d();
                    neuron->updateWeights(learningRate);
                }
            }
        }
    }

public:
    MLP(std::vector<int> network)
    {
        for(int i=1; i<network.size(); i++)
            this->network.push_back( Layer(network[i], network[i-1]) );
    }

    void fit(std::vector<std::vector<double>> X, std::vector<double> d, \
                int epochs, double learningRate, double mse)
    {
        std::vector<double> y;
        double error;
        int contEpochs = 1;

        for(int i=0; i<d.size(); i++)
            y.push_back(0);

        printf("Training [ learningRate: %lf, mse: %lf ] ... \n", learningRate, mse);
        do
        {
            for(int x=0; x<X.size(); x++)
            {
                y[x] = forward(X[x]);
                backForward(x, d, learningRate);
            }

            error = getError(d, y);

            contEpochs++;
        }
        while((contEpochs <= epochs) && (error > mse));

        printf("\nfinish: [ epochs: %d, error: %lf ]\n", contEpochs, error );

    }

    double process(std::vector<double> X)
    {
        return forward(X);
    }
};

#endif // MLP_H
