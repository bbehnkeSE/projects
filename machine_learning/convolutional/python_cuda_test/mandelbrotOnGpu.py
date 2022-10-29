from __future__       import print_function, division, absolute_import

from numba            import cuda
from matplotlib.pylab import imshow, show 
from timeit           import default_timer as timer

import numpy as np


@cuda.jit(device=True)
def mandelbrot(x, y, max_iterations):
    c = complex(x, y)
    z = 0.0j
    i = 0

    for i in range(max_iterations):
        z = z * z + c
        if(z.real * z.real + z.imag * z.imag) >= 4:
            return i

    return 255



@cuda.jit
def create_fractal(min_x, max_x, min_y, max_y, img, iters):
    width  = img.shape[1]
    height = img.shape[0]

    pixel_size_x = (max_x - min_x)/width
    pixel_size_y = (max_y - min_y)/height

    x, y = cuda.grid(2)

    if x < width and y < height:
        real = min_x + x * pixel_size_x
        imag = min_y + y * pixel_size_y
        color = mandelbrot(real, imag, iters)
        img[y, x] = color


def main():
    image = np.zeros((500*20, 750*20), dtype=np.uint8)

    pixels = 500*20 * 750*20
    nthreads = 32
    nblocksy = ((500 * 20)//nthreads) + 1
    nblocksx = ((750 * 20)//nthreads) + 1

    start = timer()
    create_fractal[(nblocksx, nblocksy), (nthreads, nthreads)](
        -2.0, 1.0, -1.0, 1.0, image, 20
    )
    end = timer()

    print("Mandelbrot on GPU: %fs" %(end - start))

    imshow(image)
    show()


if __name__ == "__main__":
    main()
