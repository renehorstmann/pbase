import doctest
import os
import pbase as p

import numpy as np


if __name__ == '__main__':

    data = np.arange(4*2, dtype=np.float32).reshape(-1, 4)

    data2 = np.arange(4, dtype=np.float32).reshape(-1, 4)
    data3 = np.arange(4, dtype=np.float32).reshape(-1, 4) + 10

    cat = p.cloud_concatenate_v([data, data2, data3])
    print(cat)


    ind = np.array([1, 3, 3, 0, 2], dtype=np.int32)
    app = p.cloud_apply_indices(cat, ind)
    print(app)

    ind2 = np.array([1, 1, 1, 0], dtype=np.int32)

    cat = p.indices_concatenate_v([ind, ind2, ind2])
    print(cat)
    app = p.indices_apply_indices(cat, ind2)
    print(app)

