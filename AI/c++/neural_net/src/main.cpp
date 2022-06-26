#include "layers.hpp"

void printVec(Vector vec)
{
    std::cout << "\nVector:\n" << vec << std::endl;
}

int main()
{
    // Create XOR training data
    Vector x1(2), x2(2), x3(2), x4(2);
    x1 << 0, 0;
    x2 << 0, 1;
    x3 << 1, 0;
    x4 << 1, 1;

    Vector y1(1), y2(1), y3(1), y4(1);
    y1 << 0;
    y2 << 1;
    y3 << 1;
    y4 << 0;

    std::vector<Vector> X { x1, x2, x3, x4 };
    std::vector<Vector> Y { y1, y2, y3, y4 };

    // Setup function pointers
    void (*HTPtr) (Vector&) { &hyperTan };
    void (*HTPPtr)(Vector&) { &hyperTanPrime };

    // Create network
    std::vector<Layer*> network
    {
        new Dense(2, 3),
        new Activation<void(*)(Vector&)>(HTPtr, HTPPtr),
        new Dense(3, 1),
        new Activation<void(*)(Vector&)>(HTPtr, HTPPtr)
    };

    // Training loop
    int    epochs       = 10000;
    double learningRate = 0.1;
    Vector output;
    Vector gradient;

    for(int i = 0; i < epochs; ++i)
    {
        for(int j = 0; j < X.size(); ++j)
        {
            // Forward propagation
            output = X[j];
            for(auto layer: network)
                output = layer->forward(output);

            // Backward propagation
            gradient = msePrime(Y[j], output);
            for(auto it = network.rbegin(); it != network.rend(); ++it)
                gradient = (*it)->backward(gradient, learningRate);
        }
    }

    std::cout << "\nFinal output:\n"
              << "--------------------\n"
              << "Correct : Prediction\n"
              << "--------:-----------\n";
    for(int i = 0; i < X.size(); ++i)
    {
        output = X[i];
        for(auto layer: network)
            output = layer->forward(output);

        std::cout << "      " << Y[i] << " : " << output << std::endl;
    }

    // Free memory
    for(auto it = network.begin(); it != network.end(); ++it)
        delete &it;

    return 0;
}