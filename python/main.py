import doctest
import os
import pbase as p

import numpy as np


if __name__ == '__main__':

    cloud = np.arange(3*4, dtype=np.float32).reshape(-1, 4)
    indices = np.array([-1, 0, 1], dtype=np.int32)

    print(p.cloud_apply_indices(cloud, indices))

