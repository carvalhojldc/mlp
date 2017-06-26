#ifndef OUTPUTSIGNAL_H
#define OUTPUTSIGNAL_H

#include <cmath>

class OutputSignal
{
public:
    double sigmoid(double u)
    {
        return 1./(1.+exp(-u));
    }

    double sigmod_d(double u)
    {
        return sigmoid(u)*(1.-sigmoid(u));
    }

    double tangh(double u)
    {
        return tanh(u);
    }

    double tangh_d(double u)
    {
        return 2./(cosh(2.*u) + 1.);
    }

    double linear(double u)
    {
        return u;
    }

    double linear_u(double u)
    {
        return 1;
    }
};

#endif // OUTPUTSIGNAL_H
