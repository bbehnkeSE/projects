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