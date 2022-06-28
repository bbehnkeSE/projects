#include "layers.hpp"


//===========================================
// Error functions
//

// Mean squared error
double mse(Vector correct, Vector pred)
{
    return (correct - pred).array().square().mean();
}

Vector msePrime(Vector correct, Vector pred)
{
    return 2 * (pred - correct) / correct.rows();
}


//===========================================
// Activation functions
//

//Hyperbolic tangent
void hyperTan(Vector& vec)
{
    for(int i = 0; i < vec.rows(); ++i)
        vec(i) = tanh(vec(i));
}

void hyperTanPrime(Vector& vec)
{
    for(int i = 0; i < vec.rows(); ++i)
        vec(i) = 1 - pow(tanh(vec(i)), 2);
}


//===========================================
// Layer functions
//

// Dense layer
Dense::Dense(int inputSize, int outputSize)
{
    weights = Matrix::Random(outputSize, inputSize);
    biases  = Vector::Random(outputSize);
}

Vector Dense::forward(Vector in)
{
    input = in;
    return (weights * input) + biases;
}

Vector Dense::backward(Vector outputGrad, double learningRate)
{
    Matrix weightGrad = outputGrad * input.transpose();         // Calculate new weights              (dE/dW = dE/dY * X^t)
    Vector inputGrad  = weights.transpose() * outputGrad;       // Calculate input for previous layer (dE/dX = W^t * dE/dY) 

    weights          -= learningRate * weightGrad;              // Update weights
    biases           -= learningRate * outputGrad;              // Update biases                      (dE/dB = dE/dY)

    return inputGrad;
}


//===========================================
// Utility functions
//

Vector train(std::vector<Layer*> network, std::vector<Vector> X, std::vector<Vector> Y, int epochs, double learningRate)
{
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

    return output;
}