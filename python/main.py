import pbase as p

import ctypes as ct
import numpy as np


if __name__ == '__main__':
    print('start')

    points, indices = p.meshprimitives.arrow([0, 0, 0], [100, 0, 0], 10)

    p.io.save_mesh_stl(points, indices, 'test.stl', False)

    print('fin')
