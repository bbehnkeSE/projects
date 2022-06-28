from   layer import Layer
import numpy as np

class Activation(Layer):
    def __init__(self, activation, activationPrime):
        self.activation      = activation
        self.activationPrime = activationPrime

    def forward(self, input):
        self.input = input
        return self.activation(self.input)

    def backward(self, outGrad, learningRate):
        return np.multiply(outGrad, self.activationPrime(self.input))


class Sigmoid(Activation):
    def __init__(self):
        def sigmoid(x):
            return 1 / (1 + np.exp(-x))

        def sigmoidPrime(x):
            s = sigmoid(x)
            return s * (1 - s)

        super().__init__(sigmoid, sigmoidPrime)