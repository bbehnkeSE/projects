import numpy as np
from   scipy import signal

class Layer:
    def __init__(self):
        self.input  = None
        self.output = None

    def forward(self, input):
        pass

    def backward(self, outGrad, learningRate):
        pass


class Dense(Layer):
    def __init__(self, inputSize, outputSize):
        self.weights = np.random.randn(outputSize, inputSize)
        self.biases  = np.random.randn(outputSize, 1)

    def forward(self, input):
        self.input = input
        return np.dot(self.weights, self.input) + self.biases

    def backward(self, outGrad, learningRate):
        weightsGrad   = np.dot(outGrad, self.input.T)
        inputGrad     = np.dot(self.weights.T, outGrad)

        self.weights -= learningRate * weightsGrad
        self.biases  -= learningRate * outGrad

        return inputGrad


class Convolutional(Layer):
    def __init__(self, inputShape, kernelSize, depth):
        inputDepth, inputHeight, inputWidth = inputShape

        # Unpack input shape
        self.depth                          = depth
        self.inputShape                     = inputShape
        self.inputDepth                     = inputDepth

        # Calculate output shape
        self.outputShape                    = (depth, (inputHeight - kernelSize + 1), (inputWidth - kernelSize + 1))

        # Calculate kernel shape
        self.kernelShape                    = (depth, inputDepth, kernelSize, kernelSize)

        # Initialize kernels and biases
        self.kernels                        = np.random.randn(*self.kernelShape)
        self.biases                         = np.random.randn(*self.outputShape)

    def forward(self, input):
        self.input  = input
        self.output = np.copy(self.biases)

        # Y_i = B_i + sum(X_j CC K_ij)
        for i in range(self.depth):
            for j in range(self.inputDepth):
                self.output[i] += signal.correlate2d(self.input[j], self.kernels[i, j], "valid")
        
        return self.output

    def backward(self, outGrad, learningRate):
        # Initialize empty empty arrays for kernel & input gradients
        kernelGrad = np.zeros(self.kernelShape)
        inputGrad  = np.zeros(self.inputShape)

        for i in range(self.depth):
            for j in range(self.inputDepth):
                # dE/dK_ij = X_j CC dE/dY_i
                kernelGrad[i, j] = signal.correlate2d(self.input[j], outGrad[i], "valid")
                # dE/dX_j = sum(dE/dY_i FullCon K_ij)
                inputGrad[j]    += signal.convolve2d(outGrad[i], self.kernels[i, j], "full")

        self.kernels -= learningRate * kernelGrad
        self.biases  -= learningRate * outGrad

        return inputGrad


class Reshape(Layer):
    def __init__(self, inputShape, outputShape):
        self.inputShape  = inputShape
        self.outputShape = outputShape

    def forward(self, input):
        return np.reshape(input, self.outputShape)

    def backward(self, outGrad, learningRate):
        return np.reshape(outGrad, self.inputShape)