#ifndef _LAYERS_HPP
#define _LAYERS_HPP

#include <iostream>
#include <Eigen/Dense>

class Layer
{
public:
    Layer() {}
    virtual Eigen::MatrixXd forward(Eigen::MatrixXd) = 0;
    virtual Eigen::MatrixXd backward(float, float)   = 0;
};


class Dense: public Layer
{
public:
    Dense(int, int);

    Eigen::MatrixXd forward(Eigen::MatrixXd) override;
    Eigen::MatrixXd backward(float, float) override;

private:
    Eigen::MatrixXd weights,
                    input,
                    bias;
};

#endif