#ifndef _LAYERS_HPP
#define _LAYERS_HPP

#define ARMA_DONT_USE_STD_MUTEX
#include <Armadillo/armadillo>
#include <iostream>
#include <vector>

class Layer
{
public:
    Layer() {}
    virtual std::vector<arma::mat*> forward (std::vector<arma::mat*>)         = 0;
    virtual std::vector<arma::mat*> backward(std::vector<arma::mat*>, double) = 0;
};


class Convolutional : public Layer
{
public:
    // kernelSize: Number denoting the size of each matrix in each kernel
    // depth:      Number of kernels (also the depth of the output)
    Convolutional(size_t inputDepth_, size_t inputHeight_, size_t inputWidth_, size_t kernelSize_, size_t depth_):
        inputDepth(inputDepth_), inputHeight(inputHeight_), inputWidth(inputWidth_), kernelSize(kernelSize_), depth(depth_) 
    {
        // Initializes a vector of vectors of matrices with random values
        // Outer vector contains the kernels, inner vector contains matrices in each kernel
        // The depth of the output determines the number of kernels, while the input depth determines
        // the number of matrices in the kernels
        while(kernels.size() < depth)
        {
            kernels.push_back(new std::vector<arma::mat*>);
            while(kernels.back()->size() < inputDepth)
                kernels.back()->push_back(new arma::mat(kernelSize, kernelSize, arma::fill::randu));
        }
        // Initializes vector of bias matrices
        while(biases.size() < depth)
            biases.push_back(new arma::mat((inputHeight - kernelSize + 1), (inputWidth - kernelSize + 1), arma::fill::randu));
    }
    ~Convolutional()
    {
        for(auto it: kernels)
        {
            for(auto itt: *it)
                delete itt;
            it->clear();
            delete it;
        }
        kernels.clear();

        for(auto it: biases)
            delete it;
        biases.clear();
    }

    std::vector<arma::mat*> forward (std::vector<arma::mat*> input) override 
    {
        std::vector<arma::mat*> output = biases;
        for(int i = 0; i < depth; ++i)
            for(int j = 0; j < inputDepth; ++j)
                output[i] += arma::conv2(*input[j], arma::reverse(kernels[i][j]));
        //std::vector<arma::mat*> asdf; return asdf;
    }
    std::vector<arma::mat*> backward(std::vector<arma::mat*> input, double learningRate) override 
    {
        std::vector<arma::mat*> asdf; return asdf;
    }

    void debugPrint()
    {
        for(auto it: kernels)
        {
            std::cout << "Kernel\n";
            for(auto itt: *it)
                std::cout << "Matrix\n" << *itt << std::endl << std::endl;
        }

        std::cout << "Biases\n";
        for(auto it: biases)
            std::cout << *it << std::endl << std::endl;
    }

private:
    size_t  kernelSize,      // Size of each matrix in each kernel
            depth,           // Number of kernels and depth of the output
            inputDepth,
            inputHeight,
            inputWidth;

    std::vector<std::vector<arma::mat*>*> kernels;
    std::vector<arma::mat*>               biases;
};

#endif // _TRAIN_NETWORK_HPP