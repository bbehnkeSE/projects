#ifndef _LAYERS_HPP
#define _LAYERS_HPP

#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>        // tanh()

typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;


//===========================================
// Error function prototypes
//

// Mean squared error
double mse     (Vector, Vector);
Vector msePrime(Vector, Vector);


//===========================================
// Activation function prototypes
//

// Hyperbolic tangent
void hyperTan     (Vector&);
void hyperTanPrime(Vector&);


//===========================================
// Layer classes
//

class Layer
{
public:
    Layer() {}
    virtual Vector forward (Vector)         = 0;
    virtual Vector backward(Vector, double) = 0;
};


class Dense : public Layer
{
public:
    Dense(int, int);

    Vector forward (Vector)         override;
    Vector backward(Vector, double) override;

    // Debug prints
    void   printWeights() { std::cout << weights << std::endl; }
    void   printBiases()  { std::cout << biases  << std::endl; }
    void   printInput()   { std::cout << input   << std::endl; }

private:
    Matrix weights;
    Vector biases,
           input;
};


// Activation layer class and definitions

template<typename Function>
class Activation : public Layer
{
public:
    Activation(Function activation_, Function activationPrime_): 
        activation(activation_), activationPrime(activationPrime_) {}

    Vector forward (Vector)         override;
    Vector backward(Vector, double) override;

private:
    Function activation,
             activationPrime;
    Vector   input;
};

template<typename Function>
Vector Activation<Function>::forward(Vector in)
{
    input = in;
    activation(input);
    return input;
}

template<typename Function>
Vector Activation<Function>::backward(Vector outputGrad, double learningRate)
{
    activationPrime(input);
    for(int i = 0; i < outputGrad.rows(); ++i)
        outputGrad(i) *= input(i);

    return outputGrad;
}

#endif