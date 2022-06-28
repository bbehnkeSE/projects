#include "layers.hpp"

int main()
{
    // Create XOR training data
    // input values
    Vector x1(2), x2(2), x3(2), x4(2);
    x1 << 0, 0;
    x2 << 0, 1;
    x3 << 1, 0;
    x4 << 1, 1;

    // Correct values
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

    Vector output = train(network, X, Y);

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