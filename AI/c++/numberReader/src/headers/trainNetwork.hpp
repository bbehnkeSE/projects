#ifndef _TRAIN_NETWORK_HPP
#define _TRAIN_NETWORK_HPPEVe

#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <tuple>

typedef std::tuple<size_t, size_t, size_t, size_t> tuple4D;
typedef std::tuple<size_t, size_t, size_t>         tuple3D;
typedef Eigen::MatrixXd                            eMatrix;
typedef Eigen::VectorXd                            eVector;


class Layer
{
public:
    Layer() {}
    virtual eVector forward (eVector)         = 0;
    virtual eVector backward(eVector, double) = 0;
};


class Convolutional : public Layer
{
public:
    // inputShape: Tuple containing depth, height, and width of the input
    // kernelSize: Number denoting the size of each matrix in each kernel
    // depth:      Number of kernels (also the depth of the output)
    Convolutional(tuple3D inputShape_, size_t kernelSize_, size_t depth_):
        inputShape(inputShape_), kernelSize(kernelSize_), depth(depth_) 
    {
        // Break up inputShape tuple
        inputDepth  = std::get<0>(inputShape);
        inputHeight = std::get<1>(inputShape);
        inputWidth  = std::get<2>(inputShape);

        // Initializes a vector of vectors of matrices with random values
        // Outer vector contains the kernels, inner vector contains matrices in each kernel
        // The depth of the output determines the number of kernels, while the input depth determines
        // the number of matrices in the kernels
        while(kernels.size() < depth)
        {
            kernels.push_back(new std::vector<eMatrix*>);
            while(kernels.back()->size() < inputDepth)
            {
                kernels.back()->push_back(new eMatrix(kernelSize, kernelSize));
                kernels.back()->back()->setRandom();
            }
        }
        // Initializes vector of bias matrices
        while(biases.size() < depth)
        {
            biases.push_back(new eMatrix((inputHeight - kernelSize + 1), (inputWidth - kernelSize + 1)));
            biases.back()->setRandom();
        }
    }

    eVector forward (eVector)         override { eVector asdf; return asdf; }
    eVector backward(eVector, double) override { eVector asdf; return asdf; }

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
    tuple3D               inputShape;      // Depth, height, and width of the input 
    size_t                kernelSize,      // Size of each matrix in each kernel
                          depth,           // Number of kernels and depth of the output

                          // Individual values of inputShape tuple
                          inputDepth,
                          inputHeight,
                          inputWidth;

    std::vector<std::vector<eMatrix*>*> kernels;
    std::vector<eMatrix*>               biases;
};

#endif // _TRAIN_NETWORK_HPP