#include "headers/layers.hpp"


//===========================================
// Error functions
//

// Mean squared error
double mse(EigenVector correct, EigenVector pred)
{
    return (correct - pred).array().square().mean();
}

EigenVector msePrime(EigenVector correct, EigenVector pred)
{
    return 2 * (pred - correct) / correct.rows();
}


//===========================================
// Activation functions
//

//Hyperbolic tangent
void hyperTan(EigenVector& vec)
{
    for(int i = 0; i < vec.rows(); ++i)
        vec(i) = tanh(vec(i));
}

void hyperTanPrime(EigenVector& vec)
{
    for(int i = 0; i < vec.rows(); ++i)
        vec(i) = 1 - pow(tanh(vec(i)), 2);
}


// Rectified Linear Unit
void relu(EigenVector& vec)
{
    for(int i = 0; i < vec.rows(); ++i)
        if(vec(i) <= 0)
            vec(i) = 0;
}

void reluPrime(EigenVector& vec)
{
    for(int i = 0; i < vec.rows(); ++i)
        if(vec(i) > 0)
            vec(i) = 1;
        else
            vec(i) = 0;
}


//===========================================
// Layer functions
//

// Dense layer
Dense::Dense(int inputSize, int outputSize)
{
    weights = EigenMatrix::Random(outputSize, inputSize);
    biases  = EigenVector::Random(outputSize);
}

EigenVector Dense::forward(EigenVector in)
{
    input = in;
    return (weights * input) + biases;
}

EigenVector Dense::backward(EigenVector outputGrad, double learningRate)
{
    EigenMatrix weightGrad = outputGrad * input.transpose();         // Calculate new weights              (dE/dW = dE/dY * X^t)
    EigenVector inputGrad  = weights.transpose() * outputGrad;       // Calculate input for previous layer (dE/dX = W^t * dE/dY) 

    weights               -= learningRate * weightGrad;              // Update weights
    biases                -= learningRate * outputGrad;              // Update biases                      (dE/dB = dE/dY)

    return inputGrad;
}