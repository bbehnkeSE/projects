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


class Tanh(Activation):
    def __init__(self):
        def tanh(x):
            return np.tanh(x)

        def tanhPrime(x):
            return 1 - np.tanh(x) ** 2

        super().__init__(tanh, tanhPrime)


class Softmax(Layer):
    def forward(self, input):
        tmp         = np.exp(input)
        self.output = tmp / np.sum(tmp)
        return self.output

    def backward(self, outGrad, learningRate):
        n = np.size(self.output)
        return np.dot((np.identity(n) - self.output.T) * self.output, outGrad)