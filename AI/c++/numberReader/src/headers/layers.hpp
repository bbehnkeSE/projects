#ifndef _LAYERS_HPP
#define _LAYERS_HPP

#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>        // tanh()

typedef Eigen::MatrixXd EigenMatrix;
typedef Eigen::VectorXd EigenVector;


//===========================================
// Error function prototypes
//

// Mean squared error
double mse     (EigenVector, EigenVector);
EigenVector msePrime(EigenVector, EigenVector);


//===========================================
// Activation function prototypes
//

// Hyperbolic tangent
void hyperTan     (EigenVector&);
void hyperTanPrime(EigenVector&);

// Rectified Linear Unit
void relu     (EigenVector&);
void reluPrime(EigenVector&);


//===========================================
// Layer classes
//

class Layer
{
public:
    Layer() {}
    virtual EigenVector forward (EigenVector)         = 0;
    virtual EigenVector backward(EigenVector, double) = 0;
};


class Dense : public Layer
{
public:
    Dense(int, int);

    EigenVector forward (EigenVector)         override;
    EigenVector backward(EigenVector, double) override;

    // Debug prints
    void   printWeights() { std::cout << weights << std::endl; }
    void   printBiases()  { std::cout << biases  << std::endl; }
    void   printInput()   { std::cout << input   << std::endl; }

private:
    EigenMatrix weights;
    EigenVector biases,
           input;
};


// Activation layer class and definitions

template<typename Function>
class Activation : public Layer
{
public:
    Activation(Function activation_, Function activationPrime_): 
        activation(activation_), activationPrime(activationPrime_) {}

    EigenVector forward (EigenVector)         override;
    EigenVector backward(EigenVector, double) override;

private:
    Function activation,
             activationPrime;
    EigenVector   input;
};

template<typename Function>
EigenVector Activation<Function>::forward(EigenVector in)
{
    input = in;
    activation(input);
    return input;
}

template<typename Function>
EigenVector Activation<Function>::backward(EigenVector outputGrad, double learningRate)
{
    activationPrime(input);
    for(int i = 0; i < outputGrad.rows(); ++i)
        outputGrad(i) *= input(i);

    return outputGrad;
}

#endif      // _LAYERS_HPP