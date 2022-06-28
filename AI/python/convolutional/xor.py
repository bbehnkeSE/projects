from activations import Tanh
from layer       import Dense
from loss        import meanSquaredError, meanSquaredErrorPrime

import numpy as np

def main():
    X = np.reshape([[0, 0], [0, 1], [1, 0], [1, 1]], (4, 2, 1))
    Y = np.reshape([[0], [1], [1], [0]], (4, 1, 1))

    network = [
        Dense(2, 3),
        Tanh(),
        Dense(3, 1),
        Tanh()
    ]

    epochs       = 10000
    learningRate = .1

    for i in range(epochs):
        #error = 0
        for x, y in zip(X, Y):
            output = x
            for layer in network:
                output = layer.forward(output)
            
            #error += meanSquaredError(y, output)

            grad   = meanSquaredErrorPrime(y, output)
            for layer in reversed(network):
                grad = layer.backward(grad, learningRate)

        #error /= len(X)
        #print('%d/%d, error = %f' % (i + 1, epochs, error))

    print("\nFinal output:")
    for x in X:
        result = x
        for layer in network:
            result = layer.forward(result)

        print(result)


if __name__ == "__main__":
    main()