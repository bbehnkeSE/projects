import numpy as np

def binaryCrossEntropy(yTrue, yPred):
    return -np.mean(yTrue * np.log(yPred) + (1 - yTrue) * np.log(1 - yPred))


def binaryCrossEntropyPrime(yTrue, yPred):
    return ((1 - yTrue) / (1 - yPred) - yTrue / yPred) / np.size(yTrue)