#include "layers.hpp"

Dense::Dense(int inputSize, int outputSize)
{
    weights = Eigen::MatrixXd::Random(inputSize, outputSize);
    bias    = Eigen::MatrixXd::Random(outputSize, 1);
}

Eigen::MatrixXd Dense::forward(Eigen::MatrixXd input)
{
    return (weights * input) + bias;
}