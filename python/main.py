import pbase as p

import ctypes as ct
import numpy as np





if __name__ == '__main__':
    print('start')

    vec = np.arange(100, dtype=np.float32)

    p.io.save_vector_csv(vec, 'test.csv')

    p.types.vector_print(vec)

    print('fin')
