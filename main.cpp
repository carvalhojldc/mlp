#include <iostream>

#include "mlp.h"

using std::cout;

int main(void)
{
    MLP mlp({ 2, 3, 2,1 });

    std::vector<std::vector<double>> X= { {0,0}, \
                                          {0,1}, \
                                          {1,0}, \
                                          {1,1}, };
    std::vector<double> d;
    // AND d = { 0, 0, 0, 1};
    // OR d = { 1, 1, 1, 0};
    // XOR
    d = { 0, 1, 1, 0};

    mlp.fit(X, d, 100000, 0.1, 0.001);

    cout << "\nProcess:";
    for(int x=0; x<X.size(); x++)
    {
        cout << "\n";
        cout << mlp.process(X[x]);
    }

    return 0;
}
