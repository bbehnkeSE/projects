import numpy as np
from timeit import default_timer as timer
from numba  import vectorize


@vectorize(["float32(float32, float32)"], target='cuda')
def multiplyVectors(a, b):
    return a * b


def main():
    N = 64000000        # Size per declared array
    A = np.ones(N, dtype=np.float32)
    B = np.ones(N, dtype=np.float32)
    C = np.ones(N, dtype=np.float32)

    start = timer()
    C = multiplyVectors(A, B)
    vecMultTime = timer() - start

    print("C[:6] = " + str(C[:6]))
    print("C[-6:] = " + str(C[-6:]))

    print("This multiplication took %f seconds." %vecMultTime)
    

if __name__ == "__main__":
    main()