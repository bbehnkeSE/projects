from layer          import Dense, Convolutional, Reshape
from loss           import binaryCrossEntropy, binaryCrossEntropyPrime
from activations    import Sigmoid

from keras.datasets import mnist
from keras.utils    import np_utils

import numpy as np


def preprocessData(x, y, limit):
    # Get indices of images representing a 1 or 0
    zeroIndex  = np.where(y == 0)[0][:limit]
    oneIndex   = np.where(y == 1)[0][:limit]

    # Stack arrays together and shuffle them
    allIndices = np.hstack((zeroIndex, oneIndex))
    allIndices = np.random.permutation(allIndices)

    # Extract images at those indices
    x, y       = x[allIndices], y[allIndices]

    # Reshape images
    x          = x.reshape(len(x), 1, 28, 28)
    x          = x.astype("float32") / 255

    # Create one-hot encoded vector from a number (0 -> [1,0], 1 -> [0,1])
    y          = np_utils.to_categorical(y)
    y          = y.reshape(len(y), 2, 1)      # Reshape to be a column vector

    return x, y

def main():
    # Load data from mnist server, limited to 100 images
    (xTrain, yTrain), (xTest, yTest) = mnist.load_data()
    xTrain, yTrain                   = preprocessData(xTrain, yTrain, 100)
    xTest,  yTest                    = preprocessData(xTest, yTest, 100)

    network = [
        Convolutional((1, 28, 28), 3, 5),
        Sigmoid(),
        Reshape((5, 26, 26), (5 * 26 * 26, 1)),
        Dense(5 * 26 * 26, 100),
        Sigmoid(),
        Dense(100, 2),
        Sigmoid()
    ]

    epochs       = 25
    learningRate = .1

    for i in range(epochs):
        error = 0
        for x, y in zip(xTrain, yTrain):
            output = x
            for layer in network:
                output = layer.forward(output)

            error += binaryCrossEntropy(y, output)

            grad   = binaryCrossEntropyPrime(y, output)
            for layer in reversed(network):
                grad = layer.backward(grad, learningRate)

        error /= len(xTrain)
        print(f"{i + 1}/{epochs}, error = {error}")

    for x, y in zip(xTest, yTest):
        output = x
        for layer in network:
            output = layer.forward(output)

        print(f"{np.argmax(output)}, {np.argmax(y)}")


if __name__=="__main__":
    main()