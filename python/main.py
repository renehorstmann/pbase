import pbase as p

import ctypes as ct
import numpy as np


if __name__ == '__main__':
    print('start')

    plane_points, plane_indices = p.meshprimitives.plane(np.eye(4), 10, 20)

    print('fin')
